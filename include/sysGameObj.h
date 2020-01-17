/*
*** GameObject.h
*** Header file for GameObject template.
*** Includes: sysAnimator.h (< sysSprite < sysTexture < sysCommon < sysSDLRunner)
***           sysText.h     (< sysFont < sysTexture < sysCommon < sysSDLRunner)
***           sysMixer.h    (< sysSound < sysCommon < sysSDLRunner)
*** Included by: sysScene.h -> sysGameRunner.h
*** Parents: none
*** Children: All GameObject classes. 
*** Author: Phoenix Mandala
*** Last edited: 6-27-19
*/

#pragma once
#include "sysAnimator.h"
#include "sysTextWrapper.h"
//#include "sysMixer.h" //TODO

namespace go {

	class GameObj
	{
	public:
		/* Methods */
		virtual ~GameObj() = 0;

		virtual void Step() = 0;
		virtual void Render() = 0;
	};



	  /**********************************************/
	 /*** Namespace Specific Methods and Members ***/
	/**********************************************/

	/*** HANDLE EVENTS ***/
	//This method handles all keyboard and joypad inputs.
	//We can keep the input bools within the scope of the namespace because they are namespace-global.

	extern bool* keyP; //keyPressed
	extern bool* keyH; //keyHeld
	extern bool* keyR; //keyReleased
	extern bool* keyE; //keyEvent
	extern int* key; //keyCode

	enum KEY {
		k_up,
		k_down,
		k_left,
		k_right,
		k_btn1, //A
		k_btn2, //B
		k_btn3, //X
		k_btn4, //Y
		k_btn5, //L3
		k_btn6, //R3
		k_trig_l, //L1
		k_trig_r, //R1
		k_bump_l, //L2
		k_bump_r, //R2
		k_start,
		k_select,
		k_END
	};

	void ConfigureKeys(int* arr = nullptr);
	void HandleEvents(SDL_Event Event);

	/*** STEP ***/
	void preStep();
	void postStep();

	/*** RENDER ***/
	void preRender();
	void postRender();

}