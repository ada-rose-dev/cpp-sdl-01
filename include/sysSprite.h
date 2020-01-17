/*!
*** sysSprite.h
*** header file for sysSprite class.
*** Includes: sysTexture.h (< sysCommon < sysSDLRunner)
*** Included by: sysAnimator.h -> sysGameObj.h -> sysScene.h -> sysGameRunner.h
*** Parents: none
*** Children: none
*** Author: Phoenix Mandala
*** Last edited: 6-27-19
*/

#pragma once
#include "sysTexture.h"
#include "sysTimer.h"

  /******************************************/
 /*** SpriteGrid, SPEED_TYPE, TRANS_TYPE ***/
/******************************************/

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
	tpf  //Sets speed based on ticks per frame - varies with game FPS
};

  /******************************/
 /*** Sprite class           ***/
/******************************/

#ifndef SPRITE_H
#define SPRITE_H

class Sprite //A Sprite is basically an animated texture.
{
public:
	SDL_Rect** ImgArr;
	int ImgCount = 0;		//Size of img array
	int Frame = 0;			//Index of text array
	float ImgSpd = 24;       //ImgSpd stored in FPS
	string Directory = "";	//Directory where images are stored. Will be prepended to sprite loading paths.
	SDL_Renderer* Renderer;
	Texture* Sheet = nullptr;

	bool ColorKeyEnabled = false;
	SDL_Color ColorKey = { 0x00,0xff,0xff,0xff };

	string ImgPath = "";
	SpriteGrid ImgGrid = {0,0,0,0,0,0,-1,-1};

	Timer* timer = nullptr;

	/*** Constructors, Deconstructor ***/
	Sprite(SDL_Renderer* r, bool EnableCK = false); //Loads up an empty sprite.
	Sprite(SDL_Renderer* r, Texture* texture, SpriteGrid grid); //Creates a sprite based on a pre-loaded texture sheet.
	~Sprite();

	/*** Getters, Setters ***/
	//Frame
	int GetFrame() { 
		return Frame;
	}
	void SetFrame(int f) { 
		Frame = f % ImgCount;
	}
	//ImgCount
	int GetImgCount() {
		return ImgCount; 
	}
	//Spd
	int GetSpd(SPEED_TYPE t = fps) {
		return ImgSpd;
	}
	void SetSpd(float spd, SPEED_TYPE t = fps) {
		ImgSpd = spd;
	}
	//Image directory -- to be removed?
	void SetImgDir(string path) {
		Directory = path;
	}

	/*** Color Key -- To be removed? ***/
	//Color Key Enabled
	bool GetColorKeyEnabled() { return ColorKeyEnabled; }
	void SetColorKeyEnabled(bool b) { ColorKeyEnabled = b; }
	//Color Key Value
	void SetColorKey(SDL_Color k);
	SDL_Color GetColorKey() { return ColorKey; }

	/*** Primary Methods ***/
	//Loading
	void LoadFromTex(Texture* tex, SpriteGrid grid, bool free = true);
	//Rendering
	void Render(int x, int y); //Renders Sprite to screen. (Using int params for pixel-precise rendering.)
	//Freeing
	void Free(); //Empty stored textures.


	/*** Public Members ***/
	int w = 0, h = 0;
	int x = -1, y = -1; //For scene sprites.
	TransformVec* transVec = nullptr;
};

#endif