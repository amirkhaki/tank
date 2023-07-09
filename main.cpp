#include "MapCreator.h"
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <vector>


int main(int argc, char *argv[]) {
	QApplication a(argc, argv);
	auto *scene = new QGraphicsScene();
	std::vector<std::vector<Object::Type>> mapVector = {{Object::Type::BOX, Object::Type::FOREST, Object::Type::WALL},
	                                                    {Object::Type::BOX, Object::Type::WALL,   Object::Type::FOREST}};
	MapCreator map(mapVector, scene);
	auto *view = new QGraphicsView(scene);
	view->setFixedSize(map.getMapSize().first, map.getMapSize().second);
	view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	view->show();
	return QApplication::exec();
}
