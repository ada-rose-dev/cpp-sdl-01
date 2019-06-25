#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <string>
#include "sysTexture.h"
#include "sysGameObj.h"
#include <list>
using namespace std;

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

