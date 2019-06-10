#include "./headers/sysGameObj.h"

GameObj::GameObj()
{
}


GameObj::~GameObj()
{
}

void GameObj::Render() {
	if (SprIndex != nullptr)
		SprIndex->Render(x,y);
}


void GameObj::HandleEvents(SDL_Event Event) {

	  /************************************************************************************/
	 /* Eventually this will be a virtual method. Implementing it now to abstract later. */
	/************************************************************************************/


	  /**********************************************************************************/
	 /** Handle Key Events                                                            **/
	/**********************************************************************************/
	int KeySymbol = Event.key.keysym.sym;

	//Reset release bools
	kUpR = false;
	kDownR = false;
	kLeftR = false;
	kRightR = false;

	switch (Event.type) {
	case (SDL_KEYDOWN): {
		
		switch (KeySymbol) {
		
			case(SDLK_UP):
			case(SDLK_w): 
				if (!kUp)
					kUpP = true;
				else kUpP = false;
				kUp = true;
				break;
		
			case(SDLK_DOWN):
			case(SDLK_s):
				if (!kDown)
					kDownP = true;
				else kDownP = false;
				kDown = true;
				break;
		}
		
		
		break;
		}
	case (SDL_KEYUP): {

		switch (KeySymbol) {
			case(SDLK_UP):
			case(SDLK_w):
				kUp = false;
				kUpP = false;
				kUpR = true;
				break;

			case(SDLK_DOWN):
			case(SDLK_s):
				kDown = false;
				kDownP = false;
				kDownR = true;
				break;
		}


		break;
		}
	}


	  /************************************************************************************/
	 /*** Behaviors                                                                    ***/
	/************************************************************************************/
	move();

}


//Behavior scripts -- to be removed!

void GameObj::move() {
	int yspd = 0, xspd = 0; //Make these member variables.

	if (kUp)
		yspd = movespd;
	if (kDown)
		yspd = -movespd;
	if (kLeft)
		xspd = -movespd;
	if (kRight)
		xspd = movespd;


	x += xspd;
	y += yspd;
}