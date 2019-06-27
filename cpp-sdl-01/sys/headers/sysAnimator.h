/*
*** sysAnimator.h
*** Header file for Animator class.
*** Includes: sysSprite.h (< sysTexture < sysCommon < sysSDLRunner)
*** Included by: sysCommon.h -> sysTexture.h -> sysSprite.h -> sysAnimator.h     -> sysGameObj.h -> sysScene.h -> sysGameRunner.h
***                                         \-> sysText.h   -> sysTextMachine.h -/
***                                          \-> sysSound.h -> sysMixer.h      -/
*** Parents: none
*** Children: none
*** Author: Phoenix Mandala
*** Last edited: 6-27-19
*/
#pragma once
#include "sysSprite.h"

#ifndef SYS_ANIMATOR
#define SYS_ANIMATOR

typedef struct AnimVec {
	Sprite* spr;
	string name;
	TransformVec* transVec; //Initialized to default values.
} AnimVec;

class Animator {
private:
	Texture* SpriteSheet;
	list<AnimVec*> PairList;
	double Frame = 0.;
	double Framerate = 10.;
	Sprite* SprIndex = nullptr;

public:

	/*** Constructor, Deconstructor ***/
	Animator();
	~Animator();

	/*** Pairs ***/
	void addPair(AnimVec* p);
	void removePair(AnimVec* p);
	void removePair(string name);
	void freePair(AnimVec* p);
	void freePair(string name);
	AnimVec* getPair(string name);

	/*** Sprite Index ***/
	Sprite* getSprite(string name);
	string getSpriteName(Sprite* spr);

	/*** Render ***/
	void Render(int x, int y);

	/*** Frame, Framerate ***/
	void setFrame(int f) {
		this->Frame = f;
	}
	double getFrame() {
		return this->Frame;
	}
	void setFramerate(double f) {
		this->Framerate = f;
	}
	double getFramerate() {
		return this->Framerate;
	}



};


#endif