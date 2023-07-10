//
// Created by amir on 7/9/23.
//

#ifndef GAME_SCENE_H
#define GAME_SCENE_H


#include "Player.h"
#include <QGraphicsScene>

class Scene : public QGraphicsScene {
	QVector<Player *> players;
public:
	void keyPressEvent(QKeyEvent *event) override;
	void addPlayer(Player *p);
};


#endif //GAME_SCENE_H
