/*** Includes ***/
#pragma once
#include "goPlayer.h"
using namespace go;

  /**********************************/
 /*** Constructor, Deconstructor ***/
/**********************************/
goPlayer::goPlayer() {

	//Texture
	texLink->SetColorKey({ 48, 48, 48, 255 });

	//Animator
	this->AnimMachine = new Animator();
	AnimMachine->addPair(new AnimVec({ sprLink_S,"down" }));
	AnimMachine->addPair(new AnimVec({ sprLink_N,"up" }));
	AnimMachine->addPair(new AnimVec({ sprLink_E,"right" }));
	AnimMachine->addPair(new AnimVec({ sprLink_E,"left", new TransformVec({0, SDL_FLIP_HORIZONTAL, {0,0} }) }));

	this->AnimState = "down";
}
goPlayer::~goPlayer() {

}

  /********************/
 /*** Step, Render ***/
/********************/
void goPlayer::Step() {
	preStep();

	move();

	postStep();
}

void goPlayer::Render() {
	/*** Load behaviors - TODO ***/
	if (xspd > 0)
		AnimState = "right";
	if (xspd < 0)
		AnimState = "left";
	if (yspd > 0)
		AnimState = "down";
	if (yspd < 0)
		AnimState = "up";

	AnimMachine->setState(AnimState);

	Sprite* SprIndex = AnimMachine->SprIndex;

	if (SprIndex != nullptr) {
		double spd = 0;
		if (abs(xspd) != 0 || abs(yspd) != 0) spd = 5;
		if (spd == 0)
			AnimMachine->setFrame(0);
		AnimMachine->setFramerate(10.);
	}
	
	AnimMachine->Render(x,y);
}

  /*****************/
 /*** Behaviors ***/
/*****************/
void goPlayer::move() {

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

