//
// Created by amir on 7/9/23.
//

#ifndef GAME_BOX_H
#define GAME_BOX_H


#include "Living.h"
#include "Object.h"
class Box : public Object, public Living {
protected:
	QString getImage() override;
	void onDestruct() override;
public:
	explicit Box(int h) : Living(h, true) {}
};


#endif //GAME_BOX_H
