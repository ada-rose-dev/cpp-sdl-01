#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <string>
#include "Texture.h"
#include "GameObj.h"
#include <list>
using namespace std;

class Scene
{
public:
	//Constructor, Destructor
	Scene();
	~Scene();
	void free(); //Removes all componenets from memory.

	//Members
	list<Texture*>* TexList;
	list<Sprite*>* SprList;
	list<GameObj*>* ObjList;

	//Methods (virtual)
	void render();
	void handleEvents();
	void loadTex();

	//Adders, Removers
	void AddObj(GameObj* obj);
	void RmvObj(GameObj* obj);
	void FreeObj(GameObj* obj);

	/** WIP
	void AddTex(Texture* tex);
	void RmvTex(Texture* tex);
	void FreeTex(Texture* tex);
	/**/
};

