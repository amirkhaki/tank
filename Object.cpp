//
// Created by amir on 7/9/23.
//

#include "Object.h"
#include <QPixmap>
#include <sstream>

void Object::init() {
	auto qPixmap = QPixmap(getImage());
	setPixmap(qPixmap);
}

std::stringstream & operator>>(std::stringstream &in, Object::Type &t) {
	std::map<int, Object::Type> m;
	m[0] = Object::Type::EMPTY;
	m[1] = Object::Type::WALL;
	m[2] = Object::Type::BOX;
	m[3] = Object::Type::FOREST;
	int r;
	in >> r;
	if (r > 3 || r < 0) {
		throw std::out_of_range("each part of map must be >=0 and <=3");
	}
	t = m[r];
	return in;
}
