#ifndef SDL_RUNNER
#define SDL_RUNNER

#include "./SDL/SDL.h"
#include "./SDL/SDL_image.h"
#include "Texture.h"
#include <list>
#include <string>
#include "GameObj.h"
#include "Scene.h"
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
	//Lists
	list<GameObj*>* ObjList; //Contains global (persistent) objects, e.g. GUI, menus, and scene-dependent objects.
	list<Scene*>* SceneList; //Contains all the scenes in the game.
	//Currents
	Scene* CurrentScene = nullptr;


public:
	//Methods
	SDLRunner();
	~SDLRunner();
	bool init();

		//loading methods
	Texture* loadTex(string path);
	SDL_Surface* loadSurf(string path);
	void loadTutorial(Scene t);

		//Adding, removing
	void AddScene(Scene* s);
	void FreeScene(Scene* s);
	void SetScene(Scene* s);

		//run methods
	bool HandleEvents(); //Returns run value.
	void Render();

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