//
// Created by amir on 7/9/23.
//

#include "MapCreator.h"
#include "Box.h"
#include "Empty.h"
#include "Forest.h"
#include "Object.h"
#include "Wall.h"

#include <QGraphicsScene>
#include <utility>

MapCreator::MapCreator(std::vector<std::vector<Object::Type>> m, QGraphicsScene *s) : map(std::move(m)),
                                                                                      scene(s) { create(); }

void MapCreator::create() {
	auto height = map.size();
	// map is supposed to have at least a row
	auto width = map[0].size();
	scene->setSceneRect(0, 0, qreal(width) * OBJECT_PIXEL_WIDTH, qreal(height) * OBJECT_PIXEL_HEIGHT);
	for (int i = 0; i < map.size(); ++i) {
		for (int j = 0; j < map[i].size(); ++j) {
			Object *item;
			switch (map[i][j]) {
				case Object::Type::WALL:
					item = new Wall();
					break;
				case Object::Type::BOX:
					item = new Box();
					break;
				case Object::Type::FOREST:
					item = new Forest();
					break;
				case Object::Type::EMPTY:
					item = new Empty();
					break;
			}
			item->init();
			item->setPos(j * OBJECT_PIXEL_WIDTH, i * OBJECT_PIXEL_HEIGHT);
			item->setZValue(0);
			scene->addItem(item);
		}
	}
}
