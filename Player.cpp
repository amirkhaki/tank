//
// Created by amir on 7/3/23.
//

#include "Player.h"
#include "Bullet.h"

#include <QKeyEvent>
#include <QGraphicsScene>
#include <qbrush.h>
#include <QtMath>
#include <qpoint.h>

void Player::keyPressEvent(QKeyEvent *event) {
	if (keyMap.count(event->key()) > 0)
		keyMap[event->key()](this);
}

void Player::shoot() {
	auto *bullet = new Bullet(1);
	bullet->setPos(mapToScene(boundingRect().center().x(), boundingRect().top()));
	bullet->setRotation(rotation());
	this->scene()->addItem(bullet);
}

void Player::down() {
	auto amount = moveAmount(movementSpeed);
	moveBy(-amount.x(), amount.y());
}

QPointF Player::moveAmount(qreal amount) const {
	auto angle = qDegreesToRadians(this->rotation());
	auto xSpeed = qCos(angle) * amount;
	auto ySpeed = qSin(angle) * amount;
	return {xSpeed, ySpeed};
}

void Player::up() {
	auto amount = moveAmount(movementSpeed);
	moveBy(amount.x(), -amount.y());
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
	auto p = QPixmap(":/images/tank.png");
	auto scaleFactor = 50.0 / 250.0;
	p = p.scaled(p.width() * scaleFactor, p.height() * scaleFactor);
	setPixmap(p);
	auto rect = QRectF(QPointF(0, 0), pixmap().rect().size());
	setTransformOriginPoint(rect.center());
	setZValue(1);
	keyMap[controls.right] = [this](Player *player) { player->right(); };
	keyMap[controls.left] = [this](Player *player) { player->left(); };
	keyMap[controls.up] = [this](Player *player) { player->up(); };
	keyMap[controls.down] = [this](Player *player) { player->down(); };
	keyMap[controls.shoot] = [this](Player *player) { player->shoot(); };
}

