#pragma once
#include "../../../sys/headers/sysGameObj.h"
#include "../../../sys/headers/sysTimer.h"
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
	int SPR_W = 16;
	int SPR_H = 16;
	int SPR_XSEP = 0;
	int SPR_YSEP = 0;

	Sprite* sprLink_S = new Sprite(Renderer, texLink, { SPR_W,SPR_H,SPR_XSEP,SPR_YSEP,0,0,1,2 });
	Sprite* sprLink_N = new Sprite(Renderer, texLink, { SPR_W,SPR_H,SPR_XSEP,SPR_YSEP,32,0,1,1 });
	Sprite* sprLink_E = new Sprite(Renderer, texLink, { SPR_W,SPR_H,SPR_XSEP,SPR_YSEP,48,0,1,2 });

	Sprite* sprLink_atkS = new Sprite(Renderer, texLink, {SPR_W,SPR_H,SPR_XSEP,SPR_YSEP,144,0,1,1});
	Sprite* sprLink_atkN = new Sprite(Renderer, texLink, { SPR_W,SPR_H,SPR_XSEP,SPR_YSEP,160,0,1,1 });
	Sprite* sprLink_atkE = new Sprite(Renderer, texLink, { SPR_W,SPR_H,SPR_XSEP,SPR_YSEP,176,0,1,1 });

	//MOVEMENT
	void move();
	//members
	double movespd = 4.;
	double xspd = 0.;
	double yspd = 0.;

	//ATTACK
	void attack();
	bool attacking = false;
	Uint32 atkTime = 200; //ms
	Timer* atkTimer = new Timer(atkTime);


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
