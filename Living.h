//
// Created by amir on 7/11/23.
//

#ifndef GAME_LIVING_H
#define GAME_LIVING_H


class Living {
	int health;
	bool mortal;
protected:
	virtual void onDestruct() = 0;
public:
	Living(int h, bool m);

	Living();

	void decreaseHealth(int a);
};


#endif //GAME_LIVING_H
