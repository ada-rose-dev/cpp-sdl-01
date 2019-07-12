/*
*** sysGameRunner.h
*** Header file for GameRunner class.
*** Includes: sysScene.h (< sysGameObject.h < sysAnimator < sysSprite < sysTexture < sysCommon < sysSDLRunner)
***                                         < sysText < sysFont < sysTexture < sysCommon < sysSDLRunner)
*** 										< sysMixer < sysSound < sysCommon < sysSDLRunner)
*** Included by: main.cpp
*** Parents: none
*** Children: none
*** Author: Phoenix Mandala
*** Last edited: 6-27-19
*/
#include "sysScene.h"

#pragma once
#ifndef SYS_GAMERUNNER
#define SYS_GAMERUNNER
class GameRunner
{
private:
	//Members
	SDL_Event Event;
	//Lists
	list<GameObj*>* ObjList; //Contains global (persistent) objects, e.g. GUI, menus, and scene-dependent objects.
	list<Scene*>* SceneList; //Contains all the scenes in the game.
		//Currents
	Scene* CurrentScene = nullptr;

public:
	//Constructor, deconstructor
	GameRunner();
	~GameRunner();

	//Adding, removing
	void AddScene(Scene* s);
	void FreeScene(Scene* s);
	void SetScene(Scene* s);

	//run methods
	bool HandleEvents(); //Returns run value.
	void Render();

	void GameStart();
	void GameEnd();

	list<Texture>* TexList = {};
	list<SDL_Surface>* SurfList = {};
};
#endif

