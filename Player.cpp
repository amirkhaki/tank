//
// Created by amir on 7/3/23.
//

#include "Player.h"
#include "Bullet.h"

#include <QKeyEvent>
#include <QGraphicsScene>
#include <qbrush.h>
#include <QtMath>
#include <qmath.h>

void Player::keyPressEvent(QKeyEvent *event) {
	if (keyMap.count(event->key()) > 0)
		keyMap[event->key()](this);
}

void Player::shoot() {
	auto *bullet = Bullet::Builder().setWidth(12).setHeight(10).setSpeed(1).setPos(x(), y()).build();
	bullet->setRotation(rotation());
	this->scene()->addItem(bullet);
}

void Player::down() {
	auto angle = qDegreesToRadians(rotation());
	auto xSpeed = qSin(angle) * movementSpeed;
	auto ySpeed = qCos(angle) * movementSpeed;
	this->setPos(this->x() + xSpeed, this->y() - ySpeed);
}

void Player::up() {
	auto angle = qDegreesToRadians(rotation());
	auto xSpeed = qSin(angle) * movementSpeed;
	auto ySpeed = qCos(angle) * movementSpeed;
	this->setPos(this->x() - xSpeed, this->y() + ySpeed);
}

void Player::left() {
	setRotation(rotation() - rotationSpeed);
}

void Player::right() {
	setRotation(rotation() + rotationSpeed);
}

void Player::setSpeed(qreal rSpeed, qreal mSpeed) {
	rotationSpeed = rSpeed;
	movementSpeed = mSpeed;
}

Player::Player(Player::Controls controls) {
	setRect(0, 0, 50, 50);
	setTransformOriginPoint(rect().width() / 2, rect().height() / 2);
	setBrush(QBrush(Qt::red));
	setZValue(1);
	keyMap[controls.right] = [this](Player *player) { player->right(); };
	keyMap[controls.left] = [this](Player *player) { player->left(); };
	keyMap[controls.up] = [this](Player *player) { player->up(); };
	keyMap[controls.down] = [this](Player *player) { player->down(); };
	keyMap[controls.shoot] = [this](Player *player) { player->shoot(); };
}
