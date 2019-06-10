#pragma once
#include "../../../sys/headers/sysGameObj.h"

#ifndef GO_PLAYER
#define GO_PLAYER
class goPlayer : public GameObj {
private:
	//Inhereted
	Sprite* SprIndex = nullptr;

	//Behavior members
		//Key states
	bool up		= false;
	bool down	= false;
	bool left	= false;
	bool right	= false;

		//Movement
	double movespd = 1;


public:
	goPlayer();
	~goPlayer();

	//Inhereted
	void HandleEvents(Uint8* KeyState);
	void Render();

	//Behavior methods
	void move();
};

#endif // !GO_PLAYER
