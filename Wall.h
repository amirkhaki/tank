//
// Created by amir on 7/9/23.
//

#ifndef GAME_WALL_H
#define GAME_WALL_H


#include "Object.h"
class Wall : public Object{
protected:
	QString getImage() override;
};


#endif //GAME_WALL_H
