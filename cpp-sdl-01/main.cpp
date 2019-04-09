#include <iostream>
#include <SDL.h>
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
SDL_Surface* gMedia = nullptr;

//declare functions
bool init();
void close();
bool loadMedia();

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
			//Get window surface
			gScrSurf = SDL_GetWindowSurface(gWin);
		}
	}
	return true;
}
void close() {
	//Free surfaces
	SDL_FreeSurface( gMedia );
	gMedia = nullptr;

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
	//Load splash image
	gMedia = SDL_LoadBMP("./img/hello-world.bmp");
	if (gMedia == nullptr) {
		printf("SDL Err: %s\n", SDL_GetError());
		return false;
	}

	//Load keypress images
	gKeySurfs[KS_NONE] = SDL_LoadBMP("./img/press.bmp");
	gKeySurfs[KS_UP] = SDL_LoadBMP("./img/up.bmp");
	gKeySurfs[KS_DOWN] = SDL_LoadBMP("./img/down.bmp");
	gKeySurfs[KS_LEFT] = SDL_LoadBMP("./img/left.bmp");
	gKeySurfs[KS_RIGHT] = SDL_LoadBMP("./img/right.bmp");
	//this isn't ideal. will alert the last loaded error. so if there are multiple you won't be able to tell.
	for (int i = 0; i < KS_COUNT; i++) {
		if (gKeySurfs[i] == nullptr) {
			printf("SDL Err: %s\n", SDL_GetError());
			return false;
		}
	}


	return true;
}

void render(SDL_Surface* surf) {
	SDL_BlitSurface(surf, nullptr, gScrSurf, nullptr);
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
			SDL_Surface* gCurrentSurf = gKeySurfs[KS_NONE];

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
						}
						break;

					case SDL_KEYUP: //Not the best way to achieve this effect. Use key states (lesson 18)
						gCurrentSurf = gKeySurfs[KS_NONE];
						break;
					}
				}

				//Render
				render(gCurrentSurf);
			}
		}
	}
	close();
	return 0;
}