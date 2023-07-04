//
// Created by amir on 7/3/23.
//

#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include <QGraphicsRectItem>
#include <qgraphicsitem.h>

class Player : public QGraphicsRectItem {
public:
	void keyPressEvent(QKeyEvent *event) override;

	void setSpeed(qreal vSpeed, qreal hSpeed);

	qreal verticalSpeed{};
	qreal horizontalSpeed{};

	void right();

	void left();

	void up();

	void down();


	void shoot();
};


#endif //GAME_PLAYER_H
