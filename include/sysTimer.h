/*
*** sysTimer.h
*** Description: Header file for timer class, to make managing time easier.
*** Last modified: 7-12-19
*/

#include "sysCommon.h"
#pragma once

class Timer
{
public:
	Uint32 lastTime = 0;
	Uint32 resetTime = 0;
	Uint32 currentTime = 0;

	bool trigger = false;			//Trigger is true when reset condition is met.

	double tick();					//Increments timer and returns current time.

	Timer(Uint32 resetTime = 0, Uint32 currentTime = 0); //If resetTime == 0 then timer will not reset.

};