//
// Created by amir on 7/4/23.
//

#ifndef GAME_BULLET_H
#define GAME_BULLET_H


#include <qgraphicsitem.h>
#include <qobject.h>
#include <qtypes.h>

static const int msec = 50;

class Bullet : public QObject, public QGraphicsRectItem {
Q_OBJECT

	qreal speed;

	auto startTimer() -> void;

public:
	class Builder {
		Bullet *bullet;
	public:
		Builder();

		auto setSpeed(qreal s) -> Builder &;

		auto setWidth(qreal w) -> Builder &;

		auto setHeight(qreal h) -> Builder &;

		auto setPos(qreal x, qreal y) -> Builder &;

		auto build() -> Bullet *;

	};

public slots:

	void move();
};


#endif //GAME_BULLET_H
