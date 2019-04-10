#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
using namespace std;

#pragma region Initalize SDL

//enums
enum KeySurf {
	KS_NONE,
	KS_UP,
	KS_DOWN,
	KS_LEFT,
	KS_RIGHT,
	KS_COUNT
};

//globals - to be removed later on
SDL_Window* gWin = nullptr;
SDL_Surface* gScrSurf = nullptr; //Note: Surfaces use the CPU to render. Future tutorials will cover GPU rendering.
SDL_Surface* gKeySurfs[KS_COUNT];

//declare functions
bool init();
void close();
bool loadMedia();
SDL_Surface* loadSurf(string path);

#pragma region Functions
bool init() {
	//const
	const int SCR_WIDTH = 640;
	const int SCR_HEIGHT = 480;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL Err: %s\n", SDL_GetError());
		return false;
	}
	else {
		//Populate window
		gWin = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCR_WIDTH, SCR_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWin == nullptr) {
			printf("Window could not be created! SDL Err %s\n", SDL_GetError());
			return false;
		}
		else
		{
			//Init SDL_image
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) & imgFlags)) //This line ensures we're initializing the flags we want to, and only those flags. Bitwise-AND.
				printf("SDL_image Err: %s\n", IMG_GetError());
			else //Set up window surface
				gScrSurf = SDL_GetWindowSurface(gWin);
		}
	}
	return true;
}
void close() {
	for (int i = 0; i < KS_COUNT; i++){
		SDL_FreeSurface(gKeySurfs[i]);
		gKeySurfs[i] = nullptr;
	}

	//Destroy window
	SDL_DestroyWindow( gWin );
	gWin = nullptr;

	//Quit SDL
	SDL_Quit();
}
bool loadMedia() {
	//Load keypress images
	gKeySurfs[KS_NONE] = loadSurf("./img/press.bmp");
	gKeySurfs[KS_UP] = loadSurf("./img/up.bmp");
	gKeySurfs[KS_DOWN] = loadSurf("./img/down.bmp");
	gKeySurfs[KS_LEFT] = loadSurf("./img/left.bmp");
	gKeySurfs[KS_RIGHT] = loadSurf("./img/right.bmp");



	return true;
}

SDL_Surface* loadSurf(string path) {

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
	SDL_Surface* out = SDL_ConvertSurface(loaded, gScrSurf->format, NULL);
	//handle error
	if (out == nullptr)
		printf("SDL Err: %s\n Path: %s\n", SDL_GetError(), path.c_str());
	//free loaded, return
	SDL_FreeSurface(loaded);
	return out;
}

void render(SDL_Surface* surf) {
	SDL_BlitSurface(surf, nullptr, gScrSurf, nullptr);
	SDL_UpdateWindowSurface(gWin);
}
void render(SDL_Surface* surf, SDL_Rect* stretch) {
	SDL_BlitScaled(surf, NULL, gScrSurf, stretch);
	SDL_UpdateWindowSurface(gWin);
}
/*
bool eventHandler(SDL_Event &e) { //Returns run state.
	while (SDL_PollEvent(&e) != 0) {
		switch (e.type) {
		case SDL_QUIT:
			return false;
		}
	}
	return true;
}
*/
#pragma endregion
#pragma endregion

int main(int argc, char* argv[]) {
	if (!init()) {
		printf("Failed to init!\n");
	}
	else {
		if (!loadMedia()) {
			printf("Media load failed!\n");
		}
		//Main loop
		else {
			bool run = true;
			SDL_Event e;

			//Set default surface
			SDL_Surface* gCurrentSurf = loadSurf("./img/baba.png"); //gKeySurfs[KS_NONE];

			while (run) {
				//SDL_Event handler
				//run = eventHandler(e);
				while (SDL_PollEvent(&e) != 0) {
					switch (e.type) {
					case SDL_QUIT:
						run = false;
						break;
						
					case SDL_KEYDOWN:
						switch (e.key.keysym.sym)
						{
						//esc
						case SDLK_ESCAPE:
							run = false;
							break;
							/**
						//arrow keys
						case SDLK_UP:
							gCurrentSurf = gKeySurfs[KS_UP];
							break;
						case SDLK_DOWN:
							gCurrentSurf = gKeySurfs[KS_DOWN];
							break;
						case SDLK_LEFT:
							gCurrentSurf = gKeySurfs[KS_LEFT];
							break;
						case SDLK_RIGHT:
							gCurrentSurf = gKeySurfs[KS_RIGHT];
							break;
							/**/
						}
						break;
						/**
					case SDL_KEYUP: //Not the best way to achieve this effect. Use key states (lesson 18)
						gCurrentSurf = gKeySurfs[KS_NONE];
						break;
						/**/
					}
				}

				//Stretch surface to 1/2 surf size (for practice!)
				/*
				SDL_Rect stretch;
				stretch.x = gCurrentSurf->w / 4.0;
				stretch.y = gCurrentSurf->h / 4.0;
				stretch.w = gCurrentSurf->w / 2.0;
				stretch.h = gCurrentSurf->h / 2.0;
				*/
				//Render
				render(gCurrentSurf);
				//render(gCurrentSurf,&stretch);
			}
		}
	}
	close();
	return 0;
}