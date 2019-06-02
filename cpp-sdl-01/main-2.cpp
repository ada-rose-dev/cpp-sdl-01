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
	
	/* Baba for rendering still image test */
	GameObj* baba = new GameObj();
	blankScene->AddObj(baba);
	baba->SetSprite(new Sprite(Renderer, "./img/baba.png", { 19,18 }));
	baba->x = 128;
	baba->y = 128;

	/* Link for 4-dir playable character test */
	GameObj* link = new GameObj();
	blankScene->AddObj(link);
	link->SetSprite(new Sprite(Renderer, "./img/link.png", { 16,16,2,0,1,1 }, true));
	link->x = 32;
	link->y = 32;
	link->GetSprite()->SetColorKey({ 0x30,0x30,0x30,0xff });

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