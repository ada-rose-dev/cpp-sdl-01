#include <iostream>
#include "sys/headers/sysSDLRunner.h"
#include "game/GAMEOBJS.h"
using namespace std;

int main(int argc, char* argv[]) {
	//Define runner
	SDLRunner* Runner = new SDLRunner();
	Runner->init();
	SDL_Renderer* Renderer = Runner->Renderer;

	//Main loop
 	bool run = true;
	Scene* scnTest = new Scene(Renderer);
	Runner->AddScene(scnTest);
	Runner->SetScene(scnTest);

	/*** Create Player Object ***/
	//Sheet
	Texture* texLink = new Texture(Renderer, "game/textures/link.png", true);
	//Sprites
	Sprite* sprLink_S = new Sprite(Renderer, texLink, { 16,16,2,0,1,1,1,2 });
	Sprite* sprLink_N = new Sprite(Renderer, texLink, { 16,16,2,0,36,1,1,1 });
	Sprite* sprLink_E = new Sprite(Renderer, texLink, { 16,16,2,0,54,1,1,2 });


	//Object
	GameObj* ObjPlayer = new GameObj();
	//Animator
	Animator* animLink = new Animator();
	animLink->addPair(new AnimVec({ sprLink_S,"down" }));
	animLink->addPair(new AnimVec({ sprLink_N,"up" }));
	animLink->addPair(new AnimVec({ sprLink_E,"right" }));
	animLink->addPair(new AnimVec({ sprLink_E,"left", new TransformVec({0, SDL_FLIP_HORIZONTAL, {0,0} }) }));

	ObjPlayer->setAnimator(animLink);

	//Add to Scene
	scnTest->AddObj(ObjPlayer);
	/***************************/

	int lastTime = 0, currentTime;
	while (run) {
		//Get time
		currentTime = SDL_GetTicks();


		//Load current scene

		run = Runner->HandleEvents();

		Runner->Render();

	}

	delete Runner;
	return 0;
}