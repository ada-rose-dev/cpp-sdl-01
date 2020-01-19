#include "../include/sysScene.h"


  /************************************************************************************/
 /* Constructor, Deconstructor, free()                                               */
/************************************************************************************/

Scene::Scene(SDL_Renderer* Renderer)
{
	this->Renderer = Renderer;
	TexList = new list<Texture*>;
	SprList = new list<Sprite*>;
	ObjList = new list<GameObj*>;
}

Scene::~Scene()
{
	free();
}

void Scene::free() {
	ObjList->empty();
	SprList->empty();
	TexList->empty();
}


  /************************************************************************************/
 /* MAIN GAME LOOP -- handleEvents(), step(), render()                               */
/************************************************************************************/


void Scene::handleEvents(SDL_Event Event) {
	//Handle every object's events (preferably only keystates)
	go::HandleEvents(Event);

}

void Scene::step() {
	//Handle every object's events (preferably only keystates)
	for (list<GameObj*>::iterator it = ObjList->begin(); it != ObjList->end(); it++) {
		(*it)->Step();
	}
}

void Scene::render() {

	//Will need to find a way to save texture and sprite coordinates.
	for (list<Texture*>::iterator it = TexList->begin(); it != TexList->end(); it++) {
		(*it)->Render((*it)->x, (*it)->y); //Render global texture at it's internal coordinates.
	}

	for (list<Sprite*>::iterator it = SprList->begin(); it != SprList->end(); it++) {
		(*it)->Render((*it)->x, (*it)->y);
	}

	for (list<GameObj*>::iterator it = ObjList->begin(); it != ObjList->end(); it++) {
		(*it)->Render();
	}
}


  /************************************************************************************/
 /* ADDERS/REMOVERS - Objects, Sprites, Textures, Sounds                             */
/************************************************************************************/

/* Objects */

void Scene::AddObj(GameObj* obj) {
	ObjList->push_back(obj);
}
void Scene::RmvObj(GameObj* obj) {
	ObjList->remove(obj);
}
void Scene::FreeObj(GameObj* obj) {
	RmvObj(obj);
	delete obj;
}

/* Sprites */

void Scene::AddSpr(Sprite* spr, int x, int y) {
	spr->x = x;
	spr->y = y;
	SprList->push_back(spr);
}
void Scene::RmvSpr(Sprite* spr) {
	SprList->remove(spr);
}
void Scene::FreeSpr(Sprite* spr) {
	RmvSpr(spr);
	delete spr;
}

/* Textures */

void Scene::AddTex(Texture* tex, int x, int y) {
	tex->x = x;
	tex->y = y;
	TexList->push_back(tex);
}
void Scene::RmvTex(Texture* tex) {
	TexList->remove(tex);
}
void Scene::FreeTex(Texture* tex) {
	RmvTex(tex);
	delete tex;
}

