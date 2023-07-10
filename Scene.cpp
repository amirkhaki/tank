//
// Created by amir on 7/9/23.
//

#include "Scene.h"
#include <QEvent>
#include <QObject>
#include <QKeyEvent>


void Scene::addPlayer(Player *p) {
	players.append(p);
}

void Scene::keyPressEvent(QKeyEvent *event) {
	for (auto &player: players)
		player->keyPressEvent(event);
}
