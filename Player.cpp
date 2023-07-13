//
// Created by amir on 7/3/23.
//

#include "Player.h"
#include "Bullet.h"
#include "Empty.h"
#include "Scene.h"

#include <QKeyEvent>
#include <qbrush.h>
#include <QtMath>
#include <utility>
#include <qdatetime.h>
#include <qpoint.h>
#include <qtransform.h>

void Player::keyPressEvent(QKeyEvent *event) {
	if (keyMap.count(event->key()) > 0)
		keyMap[event->key()](this);
}

void Player::shoot() {
	if (QDateTime::currentMSecsSinceEpoch() - lastShootTime < tankInfo.shootCooldown) return;
	auto *bullet = new Bullet(this, tankInfo.bulletSpeed, tankInfo.bulletPower);
	bullet->setPos(mapToScene(boundingRect().center().x(), boundingRect().top()));
	bullet->setRotation(rotation());
	this->scene()->addItem(bullet);
	lastShootTime = QDateTime::currentMSecsSinceEpoch();
}

void Player::down() {
	auto amount = moveAmount(-tankInfo.movementSpeed);
	setPos(pos() + amount);
	for (const auto &i: collidingItems()) {
		if (typeid(*i) != typeid(Empty)) {
			// undo the movement
			setPos(pos() - amount);
		}
	}
}

QPointF Player::moveAmount(qreal amount) const {
	auto transform = QTransform();
	transform.rotate(rotation());
	return transform.map(QPointF(amount, 0));

}

void Player::up() {
	auto amount = moveAmount(tankInfo.movementSpeed);
	setPos(pos() + amount);
	for (const auto &i: collidingItems()) {
		if (typeid(*i) != typeid(Empty)) {
			// undo the movement
			setPos(pos() - amount);
		}
	}
}

void Player::left() {
	setRotation(rotation() - tankInfo.rotationSpeed);
}

void Player::right() {
	setRotation(rotation() + tankInfo.rotationSpeed);
}


Player::Player(QString pName, const TankInfo &t, const Player::Controls &controls)
		: tankInfo(t), Living(static_cast<int>(t.health), true), playerName(std::move(pName)) {
	this->healthText = new std::remove_reference_t<decltype(*this->healthText)>(this);
	this->healthText->setDefaultTextColor(Qt::blue);
	this->healthText->setPos(0, -50);
	this->healthText->setZValue(2);
	this->healthText->setPlainText(playerName + ": " + QString::number(this->health));
	this->healthText->setFont(QFont("times", 11));
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


void Player::onDestruct() {
	dynamic_cast<Scene *>(scene())->removePlayer(this);
	scene()->removeItem(healthText);
	scene()->removeItem(this);
	delete this;
}

void Player::decreaseHealth(int a) {
	if (!mortal) return;
	health -= a;
	if (health <= 0) {
		mortal = false;
		onDestruct();
		return;
	}
	healthText->setPlainText(playerName + ": " + QString::number(health));
}

Player::~Player() {
	delete healthText;
}