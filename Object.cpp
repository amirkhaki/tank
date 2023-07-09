//
// Created by amir on 7/9/23.
//

#include "Object.h"
#include <QPixmap>

void Object::init() {
	auto qPixmap = QPixmap(getImage());
	setPixmap(qPixmap);
}
