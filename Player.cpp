//
// Created by amir on 7/3/23.
//

#include "Player.h"
#include "Bullet.h"

#include <QKeyEvent>
#include <QGraphicsScene>

void Player::keyPressEvent(QKeyEvent *event) {
	switch (event->key()) {
		case Qt::Key_Right:
			right();
			break;
		case Qt::Key_Left:
			left();
			break;
		case Qt::Key_Up:
			up();
			break;
		case Qt::Key_Down:
			down();
			break;
		case Qt::Key_Space:
			shoot();
			break;
	}
}

void Player::shoot() {
	auto *bullet = Bullet::Builder().setWidth(12).setHeight(10).setXSpeed(0).setYSpeed(-2).setPos(x(), y()).build();
	this->scene()->addItem(bullet);
}

void Player::down() { this->setPos(this->x(), this->y() + this->horizontalSpeed); }

void Player::up() { this->setPos(this->x(), this->y() - this->horizontalSpeed); }

void Player::left() { this->setPos(this->x() - this->verticalSpeed, this->y()); }

void Player::right() { this->setPos(this->x() + this->verticalSpeed, this->y()); }

void Player::setSpeed(qreal vSpeed, qreal hSpeed) {
	verticalSpeed = vSpeed;
	horizontalSpeed = hSpeed;
}
