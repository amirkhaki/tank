//
// Created by amir on 7/9/23.
//

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H


#include "Living.h"
#include <QString>
#include <QGraphicsPixmapItem>

class Object : public QGraphicsPixmapItem {
protected:
	virtual QString getImage() = 0;

public:
	void init();
	enum class Type {
		WALL,
		BOX,
		FOREST,
		EMPTY
	};
};


#endif //GAME_OBJECT_H
