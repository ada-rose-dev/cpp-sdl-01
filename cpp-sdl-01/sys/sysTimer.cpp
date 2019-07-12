#include "headers/sysTimer.h"

Timer::Timer(Uint32 resetTime, Uint32 currentTime) {
	this->resetTime = resetTime;
	this->currentTime = currentTime;
}

double Timer::tick() {

	//Reset trigger.
	trigger = false;

	//Get delta.
	double delta = (SDL_GetTicks() - lastTime);
	lastTime = SDL_GetTicks();
	
	//Increment timer.
	currentTime += delta;

	//Reset timer.
	if (currentTime > resetTime)
	{
		currentTime = 0;
		trigger = true;
	}

	//Return.
	return currentTime/1000.;

}