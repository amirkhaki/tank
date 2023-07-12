//
// Created by amir on 7/9/23.
//

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H


#include "Living.h"
#include <QString>
#include <QGraphicsPixmapItem>
#include <ostream>
#include <qgraphicsitem.h>
#include <sstream>

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

std::stringstream &operator>>(std::stringstream &in, Object::Type &);


#endif //GAME_OBJECT_H
