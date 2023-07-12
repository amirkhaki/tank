//
// Created by amir on 7/3/23.
//

#include "Player.h"
#include "Bullet.h"
#include "Empty.h"

#include <QKeyEvent>
#include <QGraphicsScene>
#include <qbrush.h>
#include <QtMath>
#include <qpoint.h>
#include <qtransform.h>

void Player::keyPressEvent(QKeyEvent *event) {
	if (keyMap.count(event->key()) > 0)
		keyMap[event->key()](this);
}

void Player::shoot() {
	auto *bullet = new Bullet(this, 1, 10);
	bullet->setPos(mapToScene(boundingRect().center().x(), boundingRect().top()));
	bullet->setRotation(rotation());
	this->scene()->addItem(bullet);
}

void Player::down() {
	auto amount = moveAmount(-movementSpeed);
	setPos(pos()+amount);
	for (const auto &i: collidingItems()) {
		if (typeid(*i) != typeid(Empty)) {
			// undo the movement
			setPos(pos()-amount);
		}
	}
}

QPointF Player::moveAmount(qreal amount) const {
	auto transform = QTransform();
	transform.rotate(rotation());
	return transform.map(QPointF(amount, 0));

}

void Player::up() {
	auto amount = moveAmount(movementSpeed);
	setPos(pos()+amount);
	for (const auto &i: collidingItems()) {
		if (typeid(*i) != typeid(Empty)) {
			// undo the movement
			setPos(pos()-amount);
		}
	}
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

Player::Player(int h, const Player::Controls &controls) : Living(h, true) {
	this->healthText = new std::remove_reference_t<decltype(*this->healthText)>();
	auto p = QPixmap(":/images/tank.png");
	auto scaleFactor = 50.0 / 250.0;
	p = p.scaled(static_cast<int>(p.width() * scaleFactor), static_cast<int>( p.height() * scaleFactor));
	setPixmap(p);
	auto rect = QRectF(QPointF(0, 0), pixmap().rect().size());
	setTransformOriginPoint(rect.center());
	setZValue(1);
	keyMap[controls.right] = [](Player *player) { player->right(); };
	keyMap[controls.left] = [](Player *player) { player->left(); };
	keyMap[controls.up] = [](Player *player) { player->up(); };
	keyMap[controls.down] = [](Player *player) { player->down(); };
	keyMap[controls.shoot] = [](Player *player) { player->shoot(); };
}

void Player::addHealthText(const QPointF &healthPos) {
	healthText->setPos(healthPos);
	healthText->setPlainText(QString("health: ") + QString::number(this->health));
	scene()->addItem(healthText);
}

void Player::onDestruct() {
	scene()->removeItem(healthText);
	scene()->removeItem(this);
	delete this;
}

void Player::decreaseHealth(int a) {
	healthText->setPlainText(QString("health: ") + QString::number(health));
	Living::decreaseHealth(a);
}

Player::~Player() {
	delete healthText;
}