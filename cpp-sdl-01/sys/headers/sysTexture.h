#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <string>
using namespace std;
class Texture
{
public:
	//Members
	int w, h;
	int x = -1, y = -1;
	string path = "";
	string dir = "";

	bool ColorKeyEnabled = false;
	SDL_Color ColorKey = { 0,0xff,0xff,0xff };

	//Constructor, Deconstructor
	Texture(SDL_Renderer* Renderer, string path = "", bool ColorKeyEnabled = false, SDL_Color ColorKey = { 0,0xff,0xff,0xff }, int w = 0, int h = 0);
	~Texture();

	//Loading, Freeing
	bool Load(string path);
	void Free();

	//Rendering
	void Render(int x, int y);
	void RenderPart(int x, int y, SDL_Rect section, int w =-1, int h =-1);
	void RenderAsBackground(); //Stretches texture to entire screen. Should be called *before* any other render calls.
	void RenderPartAsBackground(SDL_Rect section);

private:
	SDL_Texture* Tex;
	SDL_Renderer* Renderer;

};

