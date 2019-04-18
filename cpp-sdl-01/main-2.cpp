#include <iostream>
#include "SDLRunner.h"
using namespace std;

int main(int argc, char* argv[]) {
	//Define runner
	SDLRunner* Runner = new SDLRunner();
	Runner->init();
	SDL_Renderer* Renderer = Runner->Renderer;

	//Main loop
	bool run = true;
	int lastTime = 0, currentTime;
	while (run) {
		currentTime = SDL_GetTicks();

		run = Runner->handleEvents();

		/* Render */
		SDL_SetRenderDrawColor(Renderer, 0xff, 0xff, 0xff, 0xff);
		SDL_RenderClear(Renderer);

		//Print current time in seconds.
		if (currentTime > lastTime + 1000) {
			printf("currentTime = %d\n", currentTime);
			lastTime = currentTime;
		}

		if (currentTime % 1000 <= 500) {
			SDL_Rect rect = { 32, 32, 64, 64 };
			SDL_SetRenderDrawColor(Renderer, 0x00, 0x00, 0x00, 0xff);
			SDL_RenderDrawRect(Renderer, &rect);
		}

		SDL_RenderPresent(Renderer);

	}

	delete Runner;
	return 0;
}