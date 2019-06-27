/*
*** sysCommon.cpp
*** Description: Contains all globally declared variables and functions for the system classes.
*** Last modified: 6-25-19
*/

#include "headers/sysCommon.h"

  /***************************/
 /*** Runner and Renderer ***/
/***************************/
SDLRunner* Runner = new SDLRunner();
SDL_Renderer* Renderer = Runner->Renderer;

