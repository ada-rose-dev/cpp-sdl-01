/*** includes ***/
#include "./headers/sysGameObj.h"


go::GameObj::~GameObj() {}

bool go::kUpP, go::kUp, go::kUpR;
bool go::kDownP, go::kDown, go::kDownR;
bool go::kLeftP, go::kLeft, go::kLeftR;
bool go::kRightP, go::kRight, go::kRightR;

void go::HandleEvents(SDL_Event Event) {

	/*** Configure Keys ***/
	int KeySymbol = Event.key.keysym.sym;
	bool keyUp = (KeySymbol == SDLK_UP) || (KeySymbol == SDLK_w);
	bool keyDown = (KeySymbol == SDLK_DOWN) || (KeySymbol == SDLK_s);
	bool keyLeft = (KeySymbol == SDLK_LEFT) || (KeySymbol == SDLK_a);
	bool keyRight = (KeySymbol == SDLK_RIGHT) || (KeySymbol == SDLK_d);


	//Events
	switch (Event.type) {
	case (SDL_KEYDOWN): {
		/* Metaprogramming to abstract this into a loop would be great. */
		if (keyUp) {
			if (!kUp)
				kUpP = true;
			else kUpP = false;
			kUp = true;
		}

		if (keyDown) {
			if (!kDown)
				kDownP = true;
			else kDownP = false;
			kDown = true;
		}

		if (keyLeft) {
			if (!kLeft)
				kLeftP = true;
			else kLeftP = false;
			kLeft = true;
		}

		if (keyRight) {
			if (!kRight)
				kRightP = true;
			else kRightP = false;
			kRight = true;
		}

		break;
	}
	case (SDL_KEYUP): {

		if (keyUp) {
			kUp = false;
			kUpP = false;
			kUpR = true;
		}

		if (keyDown) {
			kDown = false;
			kDownP = false;
			kDownR = true;
		}

		if (keyLeft) {
			kLeft = false;
			kLeftP = false;
			kLeftR = true;
		}

		if (keyRight) {
			kRight = false;
			kRightP = false;
			kRightR = true;
		}

		break;
	}
	}
}
/********************/

/*** STEP ***/
//The Step() method itself is only a part of the process. There are functions that must be called before and after the GO's behaviors.
void go::preStep() {
	//Empty
}
void go::postStep() {
	//Reset key/button release events
	kUpR = false;
	kDownR = false;
	kLeftR = false;
	kRightR = false;
}
/***********/

/*** RENDER ***/
//The Render() method must be preceded and followed by the preRender() and postRender() methods.
void go::preRender() {

}
void go::postRender() {
}