#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <list>
#include <string>
using namespace std;

class SDLRunner
{
private:
	SDL_Window* Window = nullptr;
	SDL_Renderer* Renderer = nullptr;
	SDL_Surface* ScreenSurf = nullptr;
	list<SDL_Texture>* TexList = {};
	list<SDL_Surface>* SurfList = {};

	bool printErr();
	bool printErr(string message, string path);
	bool printErrIMG();

public:
	SDLRunner();
	~SDLRunner();

	SDL_Texture* loadTex(string path);
	SDL_Surface* loadSurf(string path);

	int ScrWidth = 640;
	int ScrHeight = 480;
};

