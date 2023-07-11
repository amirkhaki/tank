//
// Created by amir on 7/4/23.
//

#ifndef GAME_BULLET_H
#define GAME_BULLET_H


#include <qgraphicsitem.h>
#include <qobject.h>
#include <qtypes.h>
#include "Player.h"

static const int msec = 50;

class Bullet : public QObject, public QGraphicsPixmapItem {
Q_OBJECT

	Player *shooter;
	qreal speed;
	int power;

	auto startTimer() -> void;

public:
	Bullet(Player *shooter, qreal s, int p);

public slots:

	void move();
};


#endif //GAME_BULLET_H
