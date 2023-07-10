//
// Created by amir on 7/4/23.
//

#include "Bullet.h"
#include <QTimer>
#include <QGraphicsScene>

void Bullet::move() {
	auto angle = qDegreesToRadians(rotation());
	auto xSpeed = qSin(angle) * speed;
	auto ySpeed = qCos(angle) * speed;
	this->setPos(this->x() + xSpeed, this->y() - ySpeed);
}

auto Bullet::startTimer() -> void {
	auto *timer = new QTimer();
	connect(timer, SIGNAL(timeout()), this, SLOT(move()));
	timer->start(msec);
}

Bullet::Bullet(qreal s) : speed(s) {
	setPixmap(QPixmap(":/images/bullet.png"));
	// the original image is 128x128, rescaling it as 32x32
	setScale(32.0/128.0);
	startTimer();
}

