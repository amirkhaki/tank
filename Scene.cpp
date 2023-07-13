//
// Created by amir on 7/9/23.
//

#include "Scene.h"
#include "Player.h"
#include <QKeyEvent>
#include <qapplication.h>
#include <qnamespace.h>


void Scene::addPlayer(Player *p) {
	players.append(p);
}

void Scene::keyPressEvent(QKeyEvent *event) {
	if (event->key() == Qt::Key_Q && event->modifiers() == Qt::ControlModifier) {
		QApplication::exit(1);
	}
	for (auto &player: players)
		player->keyPressEvent(event);
}

void Scene::removePlayer(Player *p) {
	players.removeOne(p);
}
