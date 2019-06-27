/*
*** sysSDLRunner.h
*** Implementation file for SDLRunner class.
*** Includes: none
*** Included by: sysCommon.h -> sysTexture.h -> sysSprite.h -> sysAnimator.h     -> sysGameObj.h -> sysScene.h -> sysGameRunner.h
***                                         \-> sysText.h   -> sysTextMachine.h -/
***                                          \-> sysSound.h -> sysMixer.h      -/  
*** Parents: none
*** Children: none
*** Author: Phoenix Mandala
*** Last edited: 6-27-19
*/

#ifndef SDL_RUNNER
#define SDL_RUNNER

#include "./SDL/SDL.h"
#include "./SDL/SDL_image.h"
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
	int ScrWidth = 640;
	int ScrHeight = 480;

public:
	//Methods
	SDLRunner();
	~SDLRunner();
	bool init();

		//loading methods
	SDL_Surface* loadSurf(string path);

	SDL_Window* Window = nullptr;
	SDL_Renderer* Renderer = nullptr;
	SDL_Surface* ScreenSurf = nullptr;

};

#endif