//
// Created by amir on 7/3/23.
//

#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include "Living.h"
#include <QGraphicsPixmapItem>
#include <qgraphicsitem.h>
#include <qpoint.h>

class Player : public QGraphicsPixmapItem, public Living {
	using MethodType = std::function<void(Player *)>;
	std::map<int, MethodType> keyMap;
	qreal rotationSpeed{};
	qreal movementSpeed{};
	QGraphicsTextItem *healthText;

	[[nodiscard]] QPointF moveAmount(qreal amount) const;

protected:
	void onDestruct() override;

public:
	struct Controls {
		int up;
		int down;
		int left;
		int right;
		int shoot;
	};


	void decreaseHealth(int a) override;

	Player(int h, const Player::Controls &controls);

	void keyPressEvent(QKeyEvent *event) override;

	void setSpeed(qreal rSpeed, qreal mSpeed);

	void right();

	void left();

	void up();

	void down();

	void shoot();

	void addHealthText(const QPointF &healthPos);

	~Player() override;
};


#endif //GAME_PLAYER_H
