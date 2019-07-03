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
//#include "sysText.h"  //TODO
//#include "sysMixer.h" //TODO

namespace go {

	class GameObj
	{
	protected:

		/* Members *
		string AnimState;
		Animator* AnimMachine;
		int x, y;
		/**/

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

	extern bool kUpP, kUp, kUpR;
	extern bool kDownP, kDown, kDownR;
	extern bool kLeftP, kLeft, kLeftR;
	extern bool kRightP, kRight, kRightR;

	void HandleEvents(SDL_Event Event);

	/*** STEP ***/
	void preStep();
	void postStep();

	/*** RENDER ***/
	void preRender();
	void postRender();

}