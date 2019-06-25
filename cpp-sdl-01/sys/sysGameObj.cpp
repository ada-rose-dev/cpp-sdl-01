#include "./headers/sysGameObj.h"

  /************************************************************************************/
 /*** CONSTRUCTOR, DECONSTRUCTOR -- Load in behavior scripts                       ***/
/************************************************************************************/

GameObj::GameObj() 
{
	//Load in behaviors - TODO
}


GameObj::~GameObj()
{
}


  /************************************************************************************/
 /*** EXECUTION EVENTS - HandleEvents(), Step(), Render()                          ***/
/************************************************************************************/

  /***************************************************************/
 /*** HandleEvents() -- Handles keyboard and joystick events. ***/
/***************************************************************/
void GameObj::HandleEvents(SDL_Event Event) {
	
	/*** Configure Keys ***/
	int KeySymbol	= Event.key.keysym.sym;
	bool keyUp		= (KeySymbol == SDLK_UP) || (KeySymbol == SDLK_w);
	bool keyDown	= (KeySymbol == SDLK_DOWN) || (KeySymbol == SDLK_s);
	bool keyLeft	= (KeySymbol == SDLK_LEFT) || (KeySymbol == SDLK_a);
	bool keyRight	= (KeySymbol == SDLK_RIGHT) || (KeySymbol == SDLK_d);


	//Events
	switch (Event.type) {
		case (SDL_KEYDOWN): {
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
 /*** Step() - Calls all behavior scripts ***/
/*******************************************/

void GameObj::Step() {

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


  /****************************************************************************/
 /*** Render(), Animation methods - Renders sprite and textures to screen. ***/
/****************************************************************************/

void GameObj::setAnimator(Animator* AnimMachine, bool free) {
	if (free)
		freeAnimator();
	this->AnimMachine = AnimMachine;
}
Animator* GameObj::getAnimator() {
	return AnimMachine;
}
void GameObj::freeAnimator() {
	delete this->AnimMachine;
}


void GameObj::Render() {

	/* This to be set in a behavior! */

	if (xspd > 0)
		animState = "right";
	if (xspd < 0)
		animState = "left";
	if (yspd > 0)
		animState = "down";
	if (yspd < 0)
		animState = "up";
	/**/

	SprIndex = AnimMachine->getSprite(animState);
	AnimVec* pair = AnimMachine->getPair(animState);
	if (pair != nullptr) {
		SprIndex->transVec = pair->transVec;
	}

	if (SprIndex != nullptr) {
		SprIndex->SetSpd(1);
		SprIndex->Render(x, y);
	}
}



  /************************************************************************************/
 /*** BEHAVIORS - To be loaded in from an external file.                           ***/
/************************************************************************************/

void GameObj::move() {

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
