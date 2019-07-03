/*
*** sysScene.h
*** Header file for Scene class.
*** Includes: sysGameObject.h (< sysAnimator < sysSprite < sysTexture < sysCommon < sysSDLRunner)
***                           (< sysMixer < sysSound < sysCommon < sysSDLRunner)
***                           (< sysText < sysFont < sysTexture < sysCommong < sysSDLRunner)
*** Included by: sysGameRunner.h
*** Parents: none
*** Children: none
*** Author: Phoenix Mandala
*** Last edited: 6-27-19
*/
#pragma once
#include "sysGameObj.h"
using namespace std;
using namespace go;

class Scene
{
public:
	//Constructor, Destructor
	Scene(SDL_Renderer* Renderer);
	~Scene();
	void free(); //Removes all componenets from memory.

	//Members
	list<Texture*>* TexList;
	list<Sprite*>* SprList;
	list<GameObj*>* ObjList;

	//Methods
	void handleEvents(SDL_Event Event);
	void step();
	void render();

	//Adders, Removers
	void AddObj(GameObj* obj);
	void RmvObj(GameObj* obj);
	void FreeObj(GameObj* obj);

	void AddTex(Texture* tex, int x, int y);
	void RmvTex(Texture* tex);
	void FreeTex(Texture* tex);

	void AddSpr(Sprite* spr, int x, int y);
	void RmvSpr(Sprite* spr);
	void FreeSpr(Sprite* spr);

private:
	SDL_Renderer* Renderer = nullptr;
};

