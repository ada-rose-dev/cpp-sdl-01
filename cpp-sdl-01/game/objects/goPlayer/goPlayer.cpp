#include "goPlayer.h"

//Create - Add textures, etc
goPlayer::goPlayer() {
}
goPlayer::~goPlayer() {

}


//Inhereted
void goPlayer::HandleEvents(Uint8* KeyState){

	//Handle Keystates
	up = KeyState[SDL_SCANCODE_UP];
	down = KeyState[SDL_SCANCODE_DOWN];
	left = KeyState[SDL_SCANCODE_LEFT];
	right = KeyState[SDL_SCANCODE_RIGHT];

	//Movement
	move();

}

//Behavior
void goPlayer::move() {
	//Change x,y position depending on keystate.
	if (up)
		y -= movespd;
	if (down)
		y += movespd;
	if (left)
		x -= movespd;
	if (right)
		x += movespd;
}