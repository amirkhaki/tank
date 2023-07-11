//
// Created by amir on 7/11/23.
//

#include "Living.h"

Living::Living(int h, bool m) : health(h), mortal(m) {}

void Living::decreaseHealth(int a) {
	if (!mortal) return;
	health -= a;
	if (health <= 0) {
		mortal = false;
		onDestruct();
		return;
	}
}

