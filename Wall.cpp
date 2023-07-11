//
// Created by amir on 7/9/23.
//

#include "Wall.h"
#include "Empty.h"
#include <qgraphicsscene.h>

QString Wall::getImage() {
	return ":/images/bricks.png";
}

void Wall::onDestruct() {
	auto item = new Empty();
	item->setPos(pos());
	scene()->addItem(item);
	scene()->removeItem(this);
	delete this;
}
