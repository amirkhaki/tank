//
// Created by amir on 7/4/23.
//

#include "Bullet.h"
#include <QTimer>
#include <QGraphicsScene>

void Bullet::move() {
	if (y() + rect().height() < 0) {
		scene()->removeItem(this);
		delete this;
	}
	setPos(x() + xSpeed, y() + ySpeed);
}

auto Bullet::startTimer() -> void {
	auto *timer = new QTimer();
	connect(timer, SIGNAL(timeout()), this, SLOT(move()));
	timer->start(msec);
}

auto Bullet::Builder::setXSpeed(qreal x) -> Bullet::Builder & {
	bullet->xSpeed = x;
	return *this;
}

auto Bullet::Builder::setYSpeed(qreal y) -> Bullet::Builder & {
	bullet->ySpeed = y;
	return *this;
}

Bullet::Builder::Builder() {
	bullet = new Bullet();
}

auto Bullet::Builder::setWidth(qreal w) -> Bullet::Builder & {
	bullet->setRect(bullet->x(), bullet->y(), w, bullet->rect().height());
	return *this;
}

auto Bullet::Builder::setHeight(qreal h) -> Bullet::Builder & {
	bullet->setRect(bullet->x(), bullet->y(), bullet->rect().width(), h);
	return *this;
}

auto Bullet::Builder::build() -> Bullet * {
	bullet->startTimer();
	return bullet;
}

auto Bullet::Builder::setPos(qreal x, qreal y) -> Bullet::Builder & {
	bullet->setPos(x, y);
	return *this;
}
