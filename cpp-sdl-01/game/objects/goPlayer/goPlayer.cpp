#include "goPlayer.h"

//Create - Add textures, etc
goPlayer::goPlayer() {
}
goPlayer::~goPlayer() {

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