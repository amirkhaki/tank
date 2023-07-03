#include "Player.h"
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>


int main(int argc, char *argv[]) {
	QApplication a(argc, argv);
	// create scene
	auto *scene = new QGraphicsScene();

	// create player to be added to scene
	auto *player = new Player();
	player->setSpeed(100, 100);
	player->setRect(0, 0, 100, 99);
	// add player to scene
	scene->addItem(player);
	scene->setSceneRect(0, 0, 500, 500);
	// focus on player
	player->setFlag(QGraphicsItem::ItemIsFocusable);
	player->setFocus();
	auto *view = new QGraphicsView(scene);
	view->setFixedSize(500, 500);
	// disable scroll bar
	view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	// place player at the bottom of the screen
	player->setPos(view->width() / 2.0, view->height() - player->rect().height());
	view->show();
	return QApplication::exec();
}
