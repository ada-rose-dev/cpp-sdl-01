/*
*** GameObject.h
*** Header file for GameObject template.
*** Includes: sysAnimator.h (< sysSprite < sysTexture < sysCommon < sysSDLRunner)
***           sysText.h     (< sysFont < sysTexture < sysCommon < sysSDLRunner)
***           sysMixer.h    (< sysSound < sysCommon < sysSDLRunner)
*** Included by: sysScene.h -> sysGameRunner.h
*** Parents: none
*** Children: All GameObject classes. 
*** Author: Phoenix Mandala
*** Last edited: 6-27-19
*/

#pragma once
#include "sysAnimator.h"
//#include "sysText.h"  //TODO
//#include "sysMixer.h" //TODO

class GameObj
{
private:
	//Image members
	Sprite* SprIndex = nullptr;
	Animator* AnimMachine = nullptr;

public:
	/* Methods */
	GameObj();
	~GameObj();

	void SetSprite(Sprite* s) { SprIndex = s; }
	Sprite* GetSprite() { return SprIndex; }

	void HandleEvents(SDL_Event Event); //To be abstracted
	void Step();
	void Render();

	/* General Members */
	double x = 0;
	double y = 0;

	/* Event Members */
	bool kUpP, kUp, kUpR;
	bool kDownP, kDown, kDownR;
	bool kLeftP, kLeft, kLeftR;
	bool kRightP, kRight, kRightR;

	/* Animation */
	void setAnimator(Animator* AnimMachine, bool free = true);
	void freeAnimator();
	Animator* getAnimator();

	string animState = "";


	/* Behaviors - TO BE REMOVED! */
		//MOVEMENT
	void move();
		//members
	double movespd = 4.;
	double xspd = 0.;
	double yspd = 0.;

};

