//
// Created by amir on 7/11/23.
//

#ifndef GAME_LIVING_H
#define GAME_LIVING_H


class Living {
protected:
	virtual void onDestruct() = 0;

	int health;
	int maxHealth;
	bool mortal;
public:
	Living(int h, bool m);

	virtual void decreaseHealth(int a);
};


#endif //GAME_LIVING_H
