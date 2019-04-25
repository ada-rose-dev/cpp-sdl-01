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
	Scene* blankScene = new Scene(Renderer);
	Runner->AddScene(blankScene);
	GameObj* baba = new GameObj();
	blankScene->AddObj(baba);
	baba->SetSprite(new Sprite(Renderer, "./img/baba.png", { 19,18 }));
	baba->x = 128;
	baba->y = 128;

	int lastTime = 0, currentTime;
	while (run) {
		currentTime = SDL_GetTicks();

		//Load up current room.
		run = Runner->HandleEvents();
		Runner->Render();
	}

	delete Runner;
	return 0;
}