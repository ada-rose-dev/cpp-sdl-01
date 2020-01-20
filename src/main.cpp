/*!
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
#include "../include/GAMEOBJS.h"
#include "../include/sysGameRunner.h"
#undef main
using namespace std;

int main(int argc, char* argv[]) {
	//Main loop
 	bool run = true;
 	GameRunner* Runner = new GameRunner();

	go::ConfigureKeys();

	  /************************************************************************/
	 /*** NOTE: This should all be removed and placed in an included file! ***/
	/************************************************************************/
	Scene* scnTest = new Scene(Renderer);
	Runner->AddScene(scnTest);
	Runner->SetScene(scnTest);

	//Player
	//scnTest->AddObj(new goPlayer);
	//scnTest->AddObj(new goText);

	 /************************************************************************/
	/************************************************************************/
	while (run) {
		//Load current scene
		run = Runner->HandleEvents();
		Runner->Render();
	}

	delete Runner;
	return 0;
}