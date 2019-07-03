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

	//Object
	goPlayer* ObjPlayer = new goPlayer();
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