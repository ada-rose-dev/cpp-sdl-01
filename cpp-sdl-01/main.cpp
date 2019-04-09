#include <iostream>
#include <SDL.h>
using namespace std;

#pragma region Initalize SDL
//const
const int SCR_WIDTH = 640;
const int SCR_HEIGHT = 480;

//globals - to be removed later on
SDL_Window* gWin = nullptr;
SDL_Surface* gScrSurf = nullptr; //Note: Surfaces use the CPU to render. Future tutorials will cover GPU rendering.
SDL_Surface* gMedia = nullptr;

//declare functions
bool init();
void close();
bool loadMedia();

#pragma region Functions
bool init() {
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
	//End the program
	SDL_FreeSurface( gMedia );
	gMedia = NULL;

	SDL_DestroyWindow( gWin );
	gWin = NULL;

	SDL_Quit();
}
bool loadMedia() {
	//Load splash image
	gMedia = SDL_LoadBMP("./img/hello-world.bmp");
	if (gMedia == nullptr) {
		printf("SDL Err: %s\n", SDL_GetError());
		return false;
	}
	return true;
}

void render() {
	SDL_BlitSurface(gMedia, nullptr, gScrSurf, nullptr);
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

			while (run) {
				//SDL_Event handler
				//run = eventHandler(e);
				while (SDL_PollEvent(&e) != 0) {
					switch (e.type) {
					case SDL_QUIT:
						run = false;
						break;
					}
				}

				//Render
				render();
			}
		}
	}
	close();
	return 0;
}