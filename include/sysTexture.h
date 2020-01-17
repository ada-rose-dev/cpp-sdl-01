/*
*** sysTexture.h
*** header file for Texture class.
*** Includes: sysCommon.h (< sysSDLRunner)
*** Included by: sysSprite.h -> sysAnimator.h     -> sysGameObj.h -> sysScene.h -> sysGameRunner.h
***              sysText.h   -> sysTextMachine.h -/
***              sysSound.h  -> sysMixer.h      -/
*** Parents: none
*** Children: none
*** Author: Phoenix Mandala
*** Last edited: 6-27-19
*/

#pragma once
#include "sysCommon.h"
using namespace std;
class Texture
{
public:
	//Members
	int w, h;
	int x = -1, y = -1;
	string path = "";
	string dir = "";

	//Color Key
	bool ColorKeyEnabled = false;
	void SetColorKey(SDL_Color k);
	SDL_Color GetColorKey();

	//Constructor, Deconstructor
	Texture(SDL_Renderer* Renderer, string path = "", bool ColorKeyEnabled = false, SDL_Color ColorKey = { 0,0xff,0xff,0xff }, int w = 0, int h = 0);
	~Texture();

	//Loading, Freeing
	bool Load(string path);
	bool LoadMessage(string message, TTF_Font* font, SDL_Color color = { 0,0,0 });
	void Free();

	//Rendering
	void Render(int x, int y);
	void RenderPart(int x, int y, SDL_Rect section, int w =-1, int h =-1);
	void RenderTransform(int x, int y, int w = -1, int h = -1, double rotation = 0., SDL_RendererFlip flip = SDL_FLIP_NONE, SDL_Point origin = { 0,0 });
	void RenderPartTransform(int x, int y, SDL_Rect section, int w = -1, int h = -1, double rotation = 0., SDL_RendererFlip flip = SDL_FLIP_NONE, SDL_Point origin = { 0,0 });
	void RenderAsBackground(); //Stretches texture to entire screen. Should be called *before* any other render calls.
	void RenderPartAsBackground(SDL_Rect section);

private:
	SDL_Texture* Tex;
	SDL_Renderer* Renderer;
	SDL_Color ColorKey = { 0,0xff,0xff,0xff };

};

