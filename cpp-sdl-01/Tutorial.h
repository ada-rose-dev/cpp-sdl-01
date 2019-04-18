#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <string>
#include "Texture.h"
#include "Object.h"
#include <list>
using namespace std;

class Tutorial
{
public:
	//Constructor, Destructor
	Tutorial();
	~Tutorial();

	//Members
	list<Texture>* TexList;
	list<Object>* ObjList;
	//Add "Sprite" class with texture and position.

	//Methods (virtual)
	bool render();
	bool handleEvents();
	bool loadTex();


};

