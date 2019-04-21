#include "SDLRunner.h"

SDLRunner::SDLRunner()
{
	ObjList = new list<GameObj*>;
	SceneList = new list<Scene*>;
}
SDLRunner::~SDLRunner()
{
	//Clear texture and surface lists.
	//TexList->clear();
	//SurfList->clear();

	//Destroy renderer
	SDL_DestroyRenderer(Renderer);
	Renderer = nullptr;

	//Destroy window
	SDL_DestroyWindow(Window);
	Window = nullptr;

	//Quit SDL
	IMG_Quit();
	SDL_Quit();
}

//init
bool SDLRunner::init() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		return printErr();

	//Populate window
	Window = SDL_CreateWindow("SDL Scene", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ScrWidth, ScrHeight, SDL_WINDOW_SHOWN);
	if (Window == nullptr)
		return printErr();

	//Create renderer for texture
	Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);
	if (Renderer == nullptr)
		return printErr();

	//Init renderer
	SDL_SetRenderDrawColor(Renderer, 0xFF, 0xFF, 0xFF, 0xFF); //Takes hex values for RGBA.

	//Init SDL_image
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags)) //This line ensures we're initializing the flags we want to, and only those flags. Bitwise-AND.
		return printErrIMG();

	return true;
}

//run
bool SDLRunner::HandleEvents() {
	bool run = true;
	//SDL_Event handler
	while (SDL_PollEvent(&Event) != 0) {
		switch (Event.type) {
		//Hit "X" on window
		case SDL_QUIT:
			run = false;
			break;

		case SDL_KEYDOWN:
			switch (Event.key.keysym.sym)
			{
			//esc
			case SDLK_ESCAPE:
				run = false;
				break;
			}
			break;
		}
	}
	return run;
}
void SDLRunner::Render() {
	CurrentScene->render();
}

//Adding, Removing
void SDLRunner::AddScene(Scene* s) {
	SceneList->push_back(s);
}
void SDLRunner::FreeScene(Scene* s) {
	SceneList->remove(s);
}

//Loading and Unloading
/** This is really fucky.
Texture* SDLRunner::loadTex(string path) {
	Texture* newTex = new Texture(Renderer,path);
	return newTex;
}
/**/
SDL_Surface* SDLRunner::loadSurf(string path) {

	//load
	SDL_Surface* loaded = IMG_Load(path.c_str());
	//handle error
	if (loaded == nullptr){
		printf("SDL Err: %s\n Path: %s\n", SDL_GetError(), path.c_str());
		printf("SDL_image Err: %s\n", IMG_GetError());
		SDL_FreeSurface(loaded);
		return nullptr;
	}

	//optimize - BMPs are 24 bit, so need to be converted to be displayed. here we set the images to the correct format for the main surface.
	//if we don't convert the format here, it will be converted every time an image is blit onto the screen.
	SDL_Surface* out = SDL_ConvertSurface(loaded, ScreenSurf->format, NULL);
	//handle error
	if (out == nullptr)
		printf("SDL Err: %s\n Path: %s\n", SDL_GetError(), path.c_str());
	//free loaded, return
	SDL_FreeSurface(loaded);
	return out;
}
void SDLRunner::loadTutorial(Scene t) {

}

//Helpers - Error
bool SDLRunner::printErr() {
	printf("SDL ERR: %s\n", SDL_GetError());
	return false;
}
bool SDLRunner::printErr(string message, string path) {
	printf((message + "\n").c_str());
	if (path == "")
		printf("SDL ERR: %s\n", SDL_GetError());
	else printf("SDL ERR: %s\n PATH: %s\n", SDL_GetError(), path.c_str());
	return false;
}
bool SDLRunner::printErrIMG() {
	printf("SDL_Image ERR: %s\n", IMG_GetError());
	return false;
}