/*
*** main.cpp
*** Main file. Includes main()
*** Includes: sysGameRunner (all game dependencies)
***           GAMEOBJS.h (all game objects)
*** Included by: none
*** Parents: none
*** Children: none
*** Author: Phoenix Mandala
*** Last edited: 6-27-19
*/

#include <iostream>
#include "game/GAMEOBJS.h"
#include "sys/headers/sysGameRunner.h"
using namespace std;

int main(int argc, char* argv[]) {
	//Main loop
 	bool run = true;

	GameRunner* Runner = new GameRunner();
	Scene* scnTest = new Scene(Renderer);
	Runner->AddScene(scnTest);
	Runner->SetScene(scnTest);

	/*** Create Player Object ***/
	/*** NOTE: This should all be removed and placed in an included file! ***/
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