//
// Created by amir on 7/3/23.
//

#include "Player.h"
#include "Bullet.h"

#include <QKeyEvent>
#include <QDebug>
#include <QGraphicsScene>
#include <iostream>

void Player::keyPressEvent(QKeyEvent *event) {
	switch (event->key()) {
		case Qt::Key_Right:
			setPos(x() + verticalSpeed, y());
			break;
		case Qt::Key_Left:
			setPos(x() - verticalSpeed, y());
			break;
		case Qt::Key_Up:
			setPos(x(), y() - horizontalSpeed);
			break;
		case Qt::Key_Down:
			setPos(x(), y() + horizontalSpeed);
			break;
		case Qt::Key_Space:
			auto *bullet = new Bullet();
			bullet->setPos(x(), y());
			scene()->addItem(bullet);
			break;
	}
}

void Player::setSpeed(qreal vSpeed, qreal hSpeed) {
	verticalSpeed = vSpeed;
	horizontalSpeed = hSpeed;
}
