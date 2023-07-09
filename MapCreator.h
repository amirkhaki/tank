//
// Created by amir on 7/9/23.
//

#ifndef GAME_MAPCREATOR_H
#define GAME_MAPCREATOR_H


#include "Object.h"
#include <qgraphicsitem.h>
#include <utility>
#include <vector>

const int OBJECT_PIXEL_WIDTH = 50;
const int OBJECT_PIXEL_HEIGHT = 50;

class MapCreator {

	std::vector<std::vector<Object::Type>> map;
	QGraphicsScene *scene;
public:
	MapCreator(std::vector<std::vector<Object::Type>> m, QGraphicsScene *s);

	void create();

	std::pair<int, int> getMapSize() const {
		return {map[0].size() * OBJECT_PIXEL_WIDTH, map.size() * OBJECT_PIXEL_HEIGHT};
	}
};


#endif //GAME_MAPCREATOR_H
