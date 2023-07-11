//
// Created by amir on 7/9/23.
//

#include "Box.h"
#include "Empty.h"
#include <qgraphicsscene.h>

QString Box::getImage() {
	return ":/images/box.png";
}

void Box::onDestruct() {
	auto item = new Empty();
	item->setPos(pos());
	scene()->addItem(item);
	scene()->removeItem(this);
	delete this;
}
