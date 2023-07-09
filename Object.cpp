//
// Created by amir on 7/9/23.
//

#include "Object.h"
#include <QPixmap>
#include <qpixmap.h>

void Object::init() {
	auto qPixmap = QPixmap(getImage());
	qDebug() << qPixmap.width() << qPixmap.height();
	qDebug() << qPixmap.isNull();
	setPixmap(qPixmap);
}
