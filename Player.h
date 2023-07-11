//
// Created by amir on 7/3/23.
//

#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include "Living.h"
#include <QGraphicsPixmapItem>

class Player : public QGraphicsPixmapItem, public Living {
	typedef std::function<void(Player *)> MethodType;
	std::map<int, MethodType> keyMap;
	qreal rotationSpeed{};
	qreal movementSpeed{};

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

	explicit Player(int h, bool m, Player::Controls controls);

	void keyPressEvent(QKeyEvent *event) override;

	void setSpeed(qreal rSpeed, qreal mSpeed);

	void right();

	void left();

	void up();

	void down();

	void shoot();
};


#endif //GAME_PLAYER_H
