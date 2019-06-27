/*
*** sysCommon.h
*** Global includes, members, and functions.
*** Includes: sysSDLRunner.h
*** Included by: sysTexture.h -> sysSprite.h -> sysAnimator.h     -> sysGameObj.h -> sysScene.h -> sysGameRunner.h
***                              \-> sysText.h   -> sysTextMachine.h -/
***                               \-> sysSound.h -> sysMixer.h      -/
*** Parents: none
*** Children: none
*** Author: Phoenix Mandala
*** Last edited: 6-27-19
*/

#pragma once;
#include "sysSDLRunner.h"


extern SDL_Renderer* Renderer;



  /******************************************/
 /*** SpriteGrid, SPEED_TYPE, TRANS_TYPE ***/
/******************************************

typedef struct SpriteGrid {
	int w;						//Sprite width
	int h;						//Sprite height
	int x_sep = 0, y_sep = 0;	//Separation
	int x_off = 0, y_off = 0;	//Offset
	int rows = -1, cols = -1;	//Rows/Cols
} SpriteGrid;

typedef struct TransformVec {
	double rotation = 0;
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	SDL_Point origin = { 0,0 };
} TransformVec;

enum SPEED_TYPE {
	fps, //Sets speed based on frames per second - does not vary with game FPS
	tpf //Sets speed based on ticks per frame - varies with game FPS
};

/**/