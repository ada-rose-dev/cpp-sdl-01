/*** includes ***/
#include "../include/sysGameObj.h"


go::GameObj::~GameObj() {}

bool* go::keyR;
bool* go::keyH;
bool* go::keyP;
bool* go::keyE;
int* go::key;

void go::ConfigureKeys(int* arr) {

	//Reset keys
	delete[] keyE;
	delete[] keyR;
	delete[] keyH;
	delete[] keyP;

	keyE = new bool[k_END]; //key event
	keyP = new bool[k_END]; //key pressed
	keyH = new bool[k_END]; //key held
	keyR = new bool[k_END]; //key released
	for (int i = 0; i < k_END; i++) {
		keyE[i] = false;
		keyP[i] = false;
		keyH[i] = false;
		keyR[i] = false;
	}

	delete[] key;
	key  = new int[k_END];

	if (arr == nullptr) { //Default config
		key[k_up] = SDLK_UP;
		key[k_down] = SDLK_DOWN;
		key[k_left] = SDLK_LEFT;
		key[k_right] = SDLK_RIGHT;
		key[k_btn1] = SDLK_SPACE;
		key[k_btn2] = SDLK_z;
		key[k_btn3] = SDLK_x;
		key[k_btn4] = SDLK_c;
		key[k_btn5] = SDLK_LSHIFT;
		key[k_btn6] = SDLK_RSHIFT;
		key[k_trig_l] = SDLK_a;
		key[k_trig_r] = SDLK_s;
		key[k_bump_l] = SDLK_q;
		key[k_bump_r] = SDLK_w;
	}
	else {
		for (int i = 0; i < k_END; i++) {
			key[i] = arr[i];
		}
	}

}
void go::HandleEvents(SDL_Event Event) {

	/*** Configure Keys ***/
	int KeySymbol = Event.key.keysym.sym;

	for (int i = 0; i < k_END; i++) {
		keyE[i] = ( KeySymbol == key[i] );
	}

	//Events
	if (Event.key.repeat == 0)
	switch (Event.type) {
	case (SDL_KEYDOWN):
		for (int i = 0; i < k_END; i++) {
			if (keyE[i]) {
				keyP[i] = true;
				keyH[i] = true;
				keyR[i] = false;
			}
		}
		break;
	
	case (SDL_KEYUP):
		for (int i = 0; i < k_END; i++) {
			if (keyE[i]) {
				keyP[i] = false;
				keyH[i] = false;
				keyR[i] = true;
			}
		}
		break;
	}
}
/********************/

/*** STEP ***/
//The Step() method itself is only a part of the process. There are functions that must be called before and after the GO's behaviors.
void go::preStep() {
	//Empty
}
void go::postStep() {
}
/***********/

/*** RENDER ***/
//The Render() method must be preceded and followed by the preRender() and postRender() methods.
void go::preRender() {

}
void go::postRender() {
	//This is the last step before the game loop repeats. Reset things here.
	for (int i = 0; i < k_END; i++) {
		keyP[i] = false;
		keyR[i] = false;
	}
}