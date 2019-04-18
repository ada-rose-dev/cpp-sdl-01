#ifndef SDL_RUNNER
#define SDL_RUNNER

#include "SDL.h"
#include "SDL_image.h"
#include "Texture.h"
#include <list>
#include <string>
#include "Tutorial.h"
using namespace std;

class SDLRunner
{
private:
	//Methods
	bool printErr();
	bool printErr(string message, string path);
	bool printErrIMG();

	//Members
	SDL_Event Event;

public:
	//Methods
	SDLRunner();
	~SDLRunner();
	bool init();

		//loading methods
	Texture* loadTex(string path);
	SDL_Surface* loadSurf(string path);
	bool loadTutorial(Tutorial t);

		//run methods
	bool handleEvents();

	//Members
	int ScrWidth = 640;
	int ScrHeight = 480;

	SDL_Window* Window = nullptr;
	SDL_Renderer* Renderer = nullptr;
	SDL_Surface* ScreenSurf = nullptr;
	list<Texture>* TexList = {};
	list<SDL_Surface>* SurfList = {};

};

#endif