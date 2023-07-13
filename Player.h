//
// Created by amir on 7/3/23.
//

#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include "Living.h"
#include <QGraphicsPixmapItem>
#include <qgraphicsitem.h>
#include <qpoint.h>

struct TankInfo {
	qreal movementSpeed;
	qreal rotationSpeed;
	qint64 shootCooldown;
	qint64 health;
	int bulletPower;
	int bulletSpeed;
	QString name;
};

class Player : public QGraphicsPixmapItem, public Living {
	using MethodType = std::function<void(Player *)>;
	std::map<int, MethodType> keyMap;
	QGraphicsTextItem *healthText;
	qint64 lastShootTime{};
	QString playerName;

	[[nodiscard]] QPointF moveAmount(qreal amount) const;

protected:
	void onDestruct() override;

public:
	QString name;
	int winCount{};
	struct Controls {
		int up;
		int down;
		int left;
		int right;
		int shoot;
	};


	void decreaseHealth(int a) override;

	Player(QString pName, const TankInfo &t, const Player::Controls &controls);

	void keyPressEvent(QKeyEvent *event) override;

	void right();

	void left();

	void up();

	void down();

	void shoot();


	~Player() override;

private:
	TankInfo tankInfo;

};


#endif //GAME_PLAYER_H
