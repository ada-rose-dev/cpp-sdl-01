#ifndef SDL_RUNNER
#define SDL_RUNNER

#include "SDL.h"
#include "SDL_image.h"
#include <list>
#include <string>
using namespace std;

class SDLRunner
{
private:
	//Methods
	bool printErr();
	bool printErr(string message, string path);
	bool printErrIMG();

	//Members

public:
	//Methods
	SDLRunner();
	~SDLRunner();
	bool init();

	SDL_Texture* loadTex(string path);
	SDL_Surface* loadSurf(string path);

	//Members
	int ScrWidth = 640;
	int ScrHeight = 480;

	SDL_Window* Window = nullptr;
	SDL_Renderer* Renderer = nullptr;
	SDL_Surface* ScreenSurf = nullptr;
	//list<SDL_Texture>* TexList = {};
	//list<SDL_Surface>* SurfList = {};

};

#endif