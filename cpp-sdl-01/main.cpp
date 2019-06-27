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

	  /************************************************************************/
	 /*** NOTE: This should all be removed and placed in an included file! ***/
	/************************************************************************/
	Scene* scnTest = new Scene(Renderer);
	Runner->AddScene(scnTest);
	Runner->SetScene(scnTest);

	/*** Create Player Object ***/
	//Sheet
	Texture* texLink = new Texture(Renderer, "game/textures/link.png", true);
	texLink->SetColorKey({ 48, 48, 48, 255 });

	//Sprites
	Sprite* sprLink_S = new Sprite(Renderer, texLink, { 16,16,0,0,0,0,0,2 });
	sprLink_S->w = 32;
	sprLink_S->h = 32;
	Sprite* sprLink_N = new Sprite(Renderer, texLink, { 16,16,0,0,32,0,0,1 });
	sprLink_N->w = 32;
	sprLink_N->h = 32;
	Sprite* sprLink_E = new Sprite(Renderer, texLink, { 16,16,0,0,48,0,0,2 });
	sprLink_E->w = 32;
	sprLink_E->h = 32;

	//Object
	GameObj* ObjPlayer = new GameObj();
	ObjPlayer->animState = "down";

	//Animator
	Animator* animLink = new Animator();
	animLink->addPair(new AnimVec({ sprLink_S,"down" }));
	animLink->addPair(new AnimVec({ sprLink_N,"up" }));
	animLink->addPair(new AnimVec({ sprLink_E,"right" }));
	animLink->addPair(new AnimVec({ sprLink_E,"left", new TransformVec({0, SDL_FLIP_HORIZONTAL, {0,0} }) }));

	ObjPlayer->setAnimator(animLink);

	//Add to Scene
	scnTest->AddObj(ObjPlayer);
	 /************************************************************************/
	/************************************************************************/

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