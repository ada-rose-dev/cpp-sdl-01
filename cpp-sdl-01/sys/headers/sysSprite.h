#pragma once
#include "sysTexture.h"

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
	tpf //Sets speed based on ticks per frame - varies with game FPS
};

  /******************************/
 /*** Sprite class           ***/
/******************************/

#ifndef SPRITE_H
#define SPRITE_H

class Sprite //A Sprite is basically an animated texture.
{
private:
	SDL_Rect** ImgArr;
	int ImgCount = 0; //Size of img array
	float Frame = 0; //Index of text array
	float ImgSpd = 1./180.; //ImgSpd stored in FPS
	string Directory = ""; //Directory where images are stored. Will be prepended to sprite loading paths.
	SDL_Renderer* Renderer;
	Texture* Sheet = nullptr;

	bool ColorKeyEnabled = false;
	SDL_Color ColorKey = { 0x00,0xff,0xff,0xff };

	string ImgPath = "";
	SpriteGrid ImgGrid = {0,0,0,0,0,0,-1,-1};

public:
	  /***********************************/
	 /*** Constructors, Deconstructor ***/
	/***********************************/
	Sprite(SDL_Renderer* r, bool EnableCK = false); //Loads up an empty sprite.
	Sprite(SDL_Renderer* r, Texture* texture, SpriteGrid grid); //Creates a sprite based on a pre-loaded texture sheet.
	~Sprite();

	  /************************/
	 /*** Getters, Setters ***/
	/************************/
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
	/* WIP */
	int GetSpd(SPEED_TYPE t = fps) {
		return ImgSpd;
	}
	void SetSpd(float spd, SPEED_TYPE t = fps) {
		ImgSpd = spd;
	}
	/**/

		//Image directory
	void SetImgDir(string path) {
		Directory = path;
	}

		//Color Key Enabled
	bool GetColorKeyEnabled() {
		return ColorKeyEnabled;
	}
	void SetColorKeyEnabled(bool b) { ColorKeyEnabled = b; }
		
		//Color Key Value
	void SetColorKey(SDL_Color k);
	SDL_Color GetColorKey() {
		return ColorKey;
	}

	  /***********************/
	 /*** Primary Methods ***/
	/***********************/
		//Loading
	void LoadFromTex(Texture* tex, SpriteGrid grid, bool free = true);

		//Rendering
	void Render(int x, int y); //Renders Sprite to screen. (Using int params for pixel-precise rendering.)

		//Freeing
	void Free(); //Empty stored textures.


	//Members
	int w = 0;
	int h = 0;
	int x = -1, y = -1; //For scene sprites.
	TransformVec* transVec = nullptr;
};

//Example sprite:
/*
int main() {
	Sprite* spr = new Sprite();
	spr->SetImgDir("./images/");
	spr->SetBySheet("baba.png", { 16, 16, 0, 0 });
	spr->Render(64,64);
	GameObj* baba = new GameObj();
	baba->SetSprite(spr);
	baba->Render();
}*/

#endif