/*
*** sysCommon.cpp
*** Description: Contains all globally declared variables and functions for the system classes.
*** Last modified: 6-25-19
*/

#include "sysCommon.h"

  /***************************/
 /*** Runner and Renderer ***/
/***************************/
SDLRunner* RunnerSDL = new SDLRunner();
SDL_Renderer* Renderer = RunnerSDL->Renderer;

