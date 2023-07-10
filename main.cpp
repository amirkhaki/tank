#include "MapCreator.h"
#include "Scene.h"
#include <QApplication>
#include <QGraphicsView>
#include <algorithm>
#include <vector>
#include <random>


int main(int argc, char *argv[]) {
	QApplication a(argc, argv);
	auto *scene = new Scene();
	std::vector<std::vector<Object::Type>> mapVector = {{Object::Type::BOX, Object::Type::FOREST, Object::Type::WALL,   Object::Type::FOREST, Object::Type::FOREST, Object::Type::FOREST},
	                                                    {Object::Type::BOX, Object::Type::FOREST, Object::Type::EMPTY,  Object::Type::FOREST, Object::Type::FOREST, Object::Type::FOREST},
	                                                    {Object::Type::BOX, Object::Type::EMPTY,  Object::Type::WALL,   Object::Type::FOREST, Object::Type::EMPTY,  Object::Type::FOREST},
	                                                    {Object::Type::BOX, Object::Type::FOREST, Object::Type::WALL,   Object::Type::FOREST, Object::Type::FOREST, Object::Type::FOREST},
	                                                    {Object::Type::BOX, Object::Type::FOREST, Object::Type::WALL,   Object::Type::EMPTY,  Object::Type::FOREST, Object::Type::FOREST},
	                                                    {Object::Type::BOX, Object::Type::FOREST, Object::Type::WALL,   Object::Type::FOREST, Object::Type::FOREST, Object::Type::FOREST},
	                                                    {Object::Type::BOX, Object::Type::WALL,   Object::Type::FOREST, Object::Type::FOREST, Object::Type::FOREST, Object::Type::FOREST}};
	MapCreator map(mapVector, scene);
	std::vector<std::pair<int, int>> positions;
	auto emptyPositions = map.getEmptyIndexes();
	std::sample(emptyPositions.begin(), emptyPositions.end(), std::back_inserter(positions), 2,
	            std::mt19937{std::random_device{}()});
	auto *player1 = new Player({Qt::Key_W, Qt::Key_S, Qt::Key_A, Qt::Key_D, Qt::Key_Space});
	player1->setSpeed(1, -1);
	player1->setPos(positions[0].second * OBJECT_PIXEL_WIDTH, positions[0].first * OBJECT_PIXEL_HEIGHT);
	auto *player2 = new Player({Qt::Key_Up, Qt::Key_Down, Qt::Key_Left, Qt::Key_Right, Qt::Key_K});
	player2->setSpeed(1, -1);
	player2->setPos(positions[1].second * OBJECT_PIXEL_WIDTH, positions[1].first * OBJECT_PIXEL_HEIGHT);
	scene->addItem(player1);
	scene->addPlayer(player1);
	scene->addItem(player2);
	scene->addPlayer(player2);
	auto *view = new QGraphicsView(scene);
	view->setFixedSize(map.getMapSize().first, map.getMapSize().second);
	view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	view->show();
	return QApplication::exec();
}
