//
// Created by amir on 7/4/23.
//

#include "Bullet.h"
#include "Living.h"
#include "Player.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QDateTime>

void Bullet::move() {
	auto angle = qDegreesToRadians(rotation());
	auto xSpeed = qSin(angle) * speed;
	auto ySpeed = qCos(angle) * speed;
	this->setPos(this->x() + xSpeed, this->y() - ySpeed);
	for (const auto &item: collidingItems()) {
		Living *i;
		if (item != shooter && (i = dynamic_cast<Living *>(item)) != nullptr) {
			i->decreaseHealth(power);
			scene()->removeItem(this);
			delete this;
			return;
		}
	}
}

auto Bullet::startTimer() -> void {
	auto *timer = new QTimer();
	connect(timer, SIGNAL(timeout()), this, SLOT(move()));
	timer->start(msec);
}

Bullet::Bullet(Player *shooter, qreal s, int p) : speed(s), shooter(shooter), power(p) {
	setPixmap(QPixmap(":/images/bullet.png"));
	// the original image is 128x128, rescaling it as 32x32
	setScale(32.0 / 128.0);
	startTimer();
}

