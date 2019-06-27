/*** includes ***/
#include "./headers/sysGameObj.h"

  /**********************************/
 /*** Constructor, Deconstructor ***/
/**********************************/

template <class T>
GameObj<T>::GameObj() 
{
}

template <class T>
GameObj<T>::~GameObj()
{
}


  /************************/
 /*** Animator methods ***/
/************************/

template <class T>
void GameObj<T>::setAnimator(Animator* AnimMachine, bool free) {
	if (free)
		freeAnimator();
	this->AnimMachine = AnimMachine;
}
template <class T>
Animator* GameObj<T>::getAnimator() {
	return AnimMachine;
}
template <class T>
void GameObj<T>::freeAnimator() {
	delete this->AnimMachine;
}


  /***************************************************************/
 /*** HandleEvents() -- Handles keyboard and joystick events. ***/
/***************************************************************/
template <class T>
void GameObj<T>::HandleEvents(SDL_Event Event) {
	
	/*** Configure Keys ***/
	int KeySymbol	= Event.key.keysym.sym;
	bool keyUp		= (KeySymbol == SDLK_UP) || (KeySymbol == SDLK_w);
	bool keyDown	= (KeySymbol == SDLK_DOWN) || (KeySymbol == SDLK_s);
	bool keyLeft	= (KeySymbol == SDLK_LEFT) || (KeySymbol == SDLK_a);
	bool keyRight	= (KeySymbol == SDLK_RIGHT) || (KeySymbol == SDLK_d);


	//Events
	switch (Event.type) {
		case (SDL_KEYDOWN): {
			/* Metaprogramming to abstract this into a loop would be great. */
			if (keyUp) {
				if (!kUp)
					kUpP = true;
				else kUpP = false;
				kUp = true;
			}
		
			if (keyDown) {
				if (!kDown)
					kDownP = true;
				else kDownP = false;
				kDown = true;
			}

			if (keyLeft) {
				if (!kLeft)
					kLeftP = true;
				else kLeftP = false;
				kLeft = true;
			}

			if (keyRight) {
				if (!kRight)
					kRightP = true;
				else kRightP = false;
				kRight = true;
			}
		
			break;
		}
		case (SDL_KEYUP): {

			if (keyUp) {
				kUp = false;
				kUpP = false;
				kUpR = true;
			}

			if (keyDown) {
				kDown = false;
				kDownP = false;
				kDownR = true;
			}

			if (keyLeft) {
				kLeft = false;
				kLeftP = false;
				kLeftR = true;
			}

			if (keyRight) {
				kRight = false;
				kRightP = false;
				kRightR = true;
			}

			break;
		}
	}
}

  /*******************************************/
 /*** Behavior Methods - Step(), Render() ***/
/*******************************************/
template <class T>
void GameObj<T>::Step() {

	/*** Load behaviors - TODO ***/
	move();

	//Reset Release/Press bools
	kUpR = false;
	kDownR = false;
	kLeftR = false;
	kRightR = false;
	kUpP = false;
	kDownP = false;
	kLeftP = false;
	kRightP = false;
}

template <class T>
void GameObj<T>::Render() {

	//Pre-load methods
	SprIndex = AnimMachine->getSprite(animState);
	AnimVec* pair = AnimMachine->getPair(animState);
	if (pair != nullptr) {
		SprIndex->transVec = pair->transVec;
	}

	/*** Load behaviors - TODO ***/
	if (xspd > 0)
		animState = "right";
	if (xspd < 0)
		animState = "left";
	if (yspd > 0)
		animState = "down";
	if (yspd < 0)
		animState = "up";

	if (SprIndex != nullptr) {
		double spd = 0;
		if (abs(xspd) != 0 || abs(yspd) != 0) spd = 5;
		if (spd == 0)
			SprIndex->SetFrame(0);
		SprIndex->SetSpd(spd);
		SprIndex->Render(x, y);
	}
}

  /*********************************************/
 /*** !!! - TO BE DELETED - BEHAVIORS - !!! ***/
/*********************************************/
template <class T>
void GameObj<T>::move() {

	//Local vars
	double fric = movespd / 4.;

	//No perpetual movement
	if (abs(yspd) <= fric)
		yspd = 0.;
	if (abs(xspd) <= fric)
		xspd = 0.;

	//Release
	if (yspd != 0)
		yspd -= (yspd / yspd) * fric;
	if (xspd != 0)
		xspd -= (xspd / xspd) * fric;

	//Press
	if (kUp)
		yspd -= fric;
	if (kDown)
		yspd += fric;
	if (kLeft)
		xspd -= fric;
	if (kRight)
		xspd += fric;

	//Clamp speed
	if (abs(xspd) > movespd)
		xspd = (xspd / xspd) * movespd; //  x/x == sign(x)
	if (abs(yspd) > movespd)
		yspd = (yspd / yspd) * movespd;

	//Affect position
	x += xspd;
	y += yspd;
}
