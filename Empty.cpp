//
// Created by amir on 7/9/23.
//

#include "Empty.h"
#include <exception>

QString Empty::getImage() {
	// as it is not implemented
	qDebug() << "not implemented";
	throw std::exception();
}
