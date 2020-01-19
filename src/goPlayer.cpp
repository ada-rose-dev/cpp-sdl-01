/*** Includes ***/
#include "../include/goPlayer.h"
using namespace go;

  /**********************************/
 /*** Constructor, Deconstructor ***/
/**********************************/
goPlayer::goPlayer() {

	//Texture
	texLink->SetColorKey({ 48, 48, 48, 255 });

	//Animator
	this->AnimMachine = new Animator();
	
	//Walk
	AnimMachine->addPair(new AnimVec({ sprLink_S,"down" }));
	AnimMachine->addPair(new AnimVec({ sprLink_N,"up" }));
	AnimMachine->addPair(new AnimVec({ sprLink_E,"right" }));
	AnimMachine->addPair(new AnimVec({ sprLink_E,"left", new TransformVec({0, SDL_FLIP_HORIZONTAL, {0,0} }) }));

	//Attack
	AnimMachine->addPair(new AnimVec({ sprLink_atkS,"atkDown" }));
	AnimMachine->addPair(new AnimVec({ sprLink_atkN,"atkUp" }));
	AnimMachine->addPair(new AnimVec({ sprLink_atkE,"atkRight" }));
	AnimMachine->addPair(new AnimVec({ sprLink_atkE,"atkLeft", new TransformVec({0, SDL_FLIP_HORIZONTAL, {0,0}}) }));


	this->AnimState = "down";
}
goPlayer::~goPlayer() {

}

  /********************/
 /*** Step, Render ***/
/********************/
void goPlayer::Step() {
	preStep();

	attack();
	move();

	postStep();
}

void goPlayer::Render() {
	preRender();

	if (!attacking) {

		if (AnimState == "atkRight")
			AnimState = "right";
		if (AnimState == "atkLeft")
			AnimState = "left";
		if (AnimState == "atkUp")
			AnimState = "up";
		if (AnimState == "atkDown")
			AnimState = "down";

		if (xspd > 0)
			AnimState = "right";
		if (xspd < 0)
			AnimState = "left";
		if (yspd > 0)
			AnimState = "down";
		if (yspd < 0)
			AnimState = "up";
	}
	else {
		if (AnimState == "right")
			AnimState = "atkRight";
		if (AnimState == "left")
			AnimState = "atkLeft";
		if (AnimState == "up")
			AnimState = "atkUp";
		if (AnimState == "down")
			AnimState = "atkDown";
	}

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

	if (keyP[k_btn1]) {
		sprLink_atkE->Render(0, 0);
	}
	if (keyH[k_btn1]) {
		sprLink_atkE->Render(16, 0);
	}
	if (keyR[k_btn1]) {
		sprLink_atkE->Render(32, 0);
	}

	if (attacking) {
		sprLink_atkS->Render(0, 16);
	}

	postRender();
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
	if (keyH[k_up])
		yspd -= fric;
	if (keyH[k_down])
		yspd += fric;
	if (keyH[k_left])
		xspd -= fric;
	if (keyH[k_right])
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

void goPlayer::attack() {
	if (keyP[k_btn1])
		attacking = true;
	if (attacking) {
       		movespd = 0;
		atkTimer->tick();
		if (atkTimer->trigger) {
			attacking = false;
			movespd = 4.;
		}
	}
}