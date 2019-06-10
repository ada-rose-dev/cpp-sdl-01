#pragma once
#include "sysSprite.h"
class GameObj
{
private:
	//Image members
	Sprite* SprIndex = nullptr;

	//Event members
		//Key events
	bool kUpP, kUp, kUpR;
	bool kDownP, kDown, kDownR;
	bool kLeftP, kLeft, kLeftR;
	bool kRightP, kRight, kRightR;
		//Movement variables
	double movespd = 1.;

public:
	/* Methods */
	GameObj();
	~GameObj();

	void SetSprite(Sprite* s) { SprIndex = s; }
	Sprite* GetSprite() { return SprIndex; }

	void Render();
	void HandleEvents(SDL_Event Event); //To be abstracted

	/* Behaviors - TO BE REMOVED! */
	void move();


	/* Members */
	int x = 0;
	int y = 0;
};

