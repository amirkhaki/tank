//
// Created by amir on 7/9/23.
//

#ifndef GAME_WALL_H
#define GAME_WALL_H


#include "Living.h"
#include "Object.h"

class Wall : public Object, public Living {
protected:
	QString getImage() override;
	void onDestruct() override;

public:
	Wall() : Living(1, false) {}
};


#endif //GAME_WALL_H
