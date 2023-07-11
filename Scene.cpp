//
// Created by amir on 7/9/23.
//

#include "Scene.h"
#include "Player.h"
#include <QKeyEvent>


void Scene::addPlayer(Player *p) {
	players.insert(players.end(), p);
}

void Scene::keyPressEvent(QKeyEvent *event) {
	for (auto &player: players)
		if (items().contains(player)) player->keyPressEvent(event);
}