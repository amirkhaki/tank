//
// Created by amir on 7/9/23.
//

#include "MapCreator.h"
#include "Box.h"
#include "Empty.h"
#include "Forest.h"
#include "Object.h"
#include "Wall.h"
#include <fstream>
#include <qevent.h>
#include <sstream>
#include <string>
#include <vector>

#include <QGraphicsScene>
#include <utility>
#include <iostream>

[[maybe_unused]] MapCreator::MapCreator(std::vector<std::vector<Object::Type>> m, QGraphicsScene *s, double p) : map(
		std::move(m)),
                                                                                                                 topPadding(
		                                                                                                                 p),
                                                                                                                 scene(s) {}

void MapCreator::create() {
	auto height = map.size();
	// maps are supposed to have at least a row
	auto width = map[0].size();
	scene->setSceneRect(0, 0, qreal(width) * OBJECT_PIXEL_WIDTH, qreal(height) * OBJECT_PIXEL_HEIGHT + topPadding);
	for (int i = 0; i < map.size(); ++i) {
		for (int j = 0; j < map[i].size(); ++j) {
			Object *item;
			switch (map[i][j]) {
				case Object::Type::WALL:
					item = new Wall();
					break;
				case Object::Type::BOX:
					item = new Box(20);
					break;
				case Object::Type::FOREST:
					item = new Forest();
					break;
				case Object::Type::EMPTY:
					item = new Empty();
					break;
			}
			item->init();
			item->setPos(j * OBJECT_PIXEL_WIDTH, i * OBJECT_PIXEL_HEIGHT + topPadding);
			item->setZValue(0);
			scene->addItem(item);
		}
	}
}

void readLine(std::fstream &f, char *buffer, int n) {
	int c;
	for (int i = 0; (c = f.get()) != EOF && c != '\n' && i < n; ++i) {
		buffer[i] = static_cast<char>(c);
	}
}

MapCreator::MapCreator(const std::string &fileName, QGraphicsScene *s, double p, int maxLine) : scene(s),
                                                                                                topPadding(p) {
	std::fstream file(fileName);
	if (!file.is_open()) {
		qDebug() << "can't open file" << fileName;
		throw std::exception();
	}
	while (!file.eof()) {
		std::string line;
		std::getline(file, line);
		std::vector<Object::Type> row;
		std::stringstream l(line);
		Object::Type item;
		while (l >> item) {
			row.insert(row.cend(), item);
		}
		map.insert(map.cend(), row);
	}
}
