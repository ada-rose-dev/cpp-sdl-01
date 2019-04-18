#include "Sprite.h"


Sprite::Sprite(SDL_Renderer* r){
	Renderer = r;
}

Sprite::Sprite(SDL_Renderer* r, string path, SpriteGrid grid) {
	Renderer = r;
	LoadFromPath(path, grid);
}

Sprite::Sprite(SDL_Renderer* r, string* paths, SpriteGrid* grids) {
	Renderer = r;
	LoadFromPaths(paths, grids);
}



Sprite::~Sprite()
{
	Free();
}


