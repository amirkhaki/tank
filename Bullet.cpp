//
// Created by amir on 7/4/23.
//

#include "Bullet.h"
#include <QTimer>
#include <QGraphicsScene>

Bullet::Bullet() {
	setRect(0,0, 10, 50);
	auto *timer = new QTimer();
	connect(timer, SIGNAL(timeout()), this, SLOT(move()));
	timer->start(50);
}

void Bullet::move() {
	if (y() + rect().height() < 0) {
		scene()->removeItem(this);
		delete this;
	}
	setPos(x(), y()-10);
}
