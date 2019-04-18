#pragma once
#include "Texture.h"
class Sprite //A Sprite is basically an animated texture.
{
private:
	Texture* TexArr = nullptr; //This should be an adaptave array.
	int ImgCount = 0; //Size of tex array
	int Frame = 0; //Index of text array
	string Directory = ""; //Directory where images are stored. Will be prepended to sprite loading paths.
	SDL_Renderer* Renderer;

public:
	/*Constructors, Deconstructor*/
	Sprite(SDL_Renderer* r); //Loads up an empty sprite.
	Sprite(SDL_Renderer* r, string path, SpriteGrid grid); //Loads a sprite sheet. Grid determines width, height, x- and y-offset of subimages.
	Sprite(SDL_Renderer* r, string* paths, SpriteGrid* grids); //Loads multiple sheets. Stores as a single animation. Useful for e.g. trimming textures.
	~Sprite();

	/*Getters, Setters*/
		//Frame
	int GetFrame() { return Frame; }
	void SetFrame(int f) { Frame = f % ImgCount; } //Should use modulo if passed int is out of range. -- Might be able to circumenvent this function by always taking the modulo during render()
		//ImgCount
	int GetImgCount() { return ImgCount; }
		//Spd
	int GetSpd(SPEED_TYPE t);
	void SetSpd(float spd, SPEED_TYPE t);
		//Texture
	Texture GetImage(int frame) { return TexArr[frame]; }
	void LoadFromPath(string path, SpriteGrid grid);
	void LoadFromPaths(string* paths, SpriteGrid* grids);
		//Image directory
	void SetImgDir(string path);
		//Render
	void Render(int x, int y); //Renders Sprite to screen. (Using int params for pixel-precise rendering.
		//Free
	void Free() { w = 0; h = 0; delete[] TexArr; TexArr = nullptr; ImgCount = 0; Frame = 0; } //Empty stored textures.

	//*Members*/
	int w = 0;
	int h = 0;
};

typedef struct SpriteGrid {
	int w;
	int h;
	int x_sep = 0, y_sep = 0;
	int x_off = 0, y_off = 0;
	int rows, cols; //Should be determined by the rest. If needed, can be passed.
} SpriteGrid;

enum SPEED_TYPE {
	fps, //Sets speed based on frames per second - does not vary with game FPS
	tpf //Sets speed based on ticks per frame - varies with game FPS
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