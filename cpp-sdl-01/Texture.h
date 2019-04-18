#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <string>
using namespace std;
class Texture
{
public:
	//Constructor, Deconstructor
	Texture(SDL_Renderer* Renderer);
	~Texture();

	bool Load(string path);
	void Free();
	void Render(int x, int y);

	int w;
	int h;

private:
	SDL_Texture* Tex;
	SDL_Renderer* Renderer;
};

