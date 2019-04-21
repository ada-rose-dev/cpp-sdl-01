#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <string>
using namespace std;
class Texture
{
public:
	//Constructor, Deconstructor
	Texture(SDL_Renderer* Renderer, string path = "", bool ColorKeyEnabled = false, SDL_Color ColorKey = { 0,0xff,0xff,0xff });
	~Texture();

	//Loading, Freeing
	bool Load(string path);
	void Free();

	//Rendering
	void Render(int x, int y);
	void RenderPart(int x, int y, SDL_Rect section);
	void RenderAsBackground(); //Stretches texture to entire screen. Should be called *before* any other render calls.
	void RenderPartAsBackground(SDL_Rect section);

	//Members
	int w;
	int h;

	bool ColorKeyEnabled = false;
	SDL_Color ColorKey = { 0,0xff,0xff,0xff };

private:
	SDL_Texture* Tex;
	SDL_Renderer* Renderer;

};

