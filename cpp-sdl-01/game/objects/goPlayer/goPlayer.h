#pragma once
#include "../../../sys/headers/sysGameObj.h"
using namespace go;

#ifndef GO_PLAYER
#define GO_PLAYER
class goPlayer : public GameObj {
private:

	  /******************************************/
	 /*** CLASS SPECIFIC METHODS AND MEMBERS ***/
	/******************************************/
	//Sheet
	Texture* texLink = new Texture(Renderer, "game/textures/link.png", true);

	//Sprites
	Sprite* sprLink_S = new Sprite(Renderer, texLink, { 16,16,0,0,0,0,0,2 });
	Sprite* sprLink_N = new Sprite(Renderer, texLink, { 16,16,0,0,32,0,0,1 });
	Sprite* sprLink_E = new Sprite(Renderer, texLink, { 16,16,0,0,48,0,0,2 });

	//MOVEMENT
	void move();
	//members
	double movespd = 4.;
	double xspd = 0.;
	double yspd = 0.;

	  /*************************************/
	 /*** INHERITED METHODS AND MEMBERS ***/
	/*************************************/
	//Image members
	Animator* AnimMachine;
	string AnimState = "";
	int x, y;

public:
	/* Methods */
	goPlayer();
	~goPlayer();

	/* Behaviors */
	void Render();
	void Step();
};

#endif // !GO_PLAYER
