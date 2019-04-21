#include "Sprite.h"


Sprite::Sprite(SDL_Renderer* r, bool EnableCK){
	Renderer = r;
	ColorKeyEnabled = EnableCK;
}

Sprite::Sprite(SDL_Renderer* r, string path, SpriteGrid grid, bool EnableCK) {
	Renderer = r;
	ColorKeyEnabled = EnableCK;
	LoadFromPath(path, grid);
}

Sprite::Sprite(SDL_Renderer* r, string* paths, SpriteGrid* grids, bool EnableCK) {
	Renderer = r;
	ColorKeyEnabled = EnableCK;
	LoadFromPaths(paths, grids);
}

Sprite::~Sprite()
{
	Free();
}

void Sprite::LoadFromPath(string path, SpriteGrid grid) {
	//Free();

}

void Sprite::LoadFromPaths(string* paths, SpriteGrid* grids) {

}

void Sprite::Render(int x, int y) {
	//Render TexArr[Frame] at pos (x,y)
}