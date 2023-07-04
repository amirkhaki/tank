//
// Created by amir on 7/4/23.
//

#ifndef GAME_BULLET_H
#define GAME_BULLET_H


#include <qgraphicsitem.h>
#include <qobject.h>
class Bullet : public QObject, public QGraphicsRectItem {
	Q_OBJECT
public:
	Bullet();
public slots:
	void move();

};


#endif //GAME_BULLET_H
