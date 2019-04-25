#include "Scene.h"



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

void Scene::render() {

	//Will need to find a way to save texture and sprite coordinates.
	for (list<Texture*>::iterator it = TexList->begin(); it != TexList->end(); it++) {
		(*it)->Render(0,0);
	}

	for (list<Sprite*>::iterator it = SprList->begin(); it != SprList->end(); it++) {
		(*it)->Render(0,0);
	}

	for (list<GameObj*>::iterator it = ObjList->begin(); it != ObjList->end(); it++) {
		(*it)->Render();
	}
}
void Scene::handleEvents() {}
void Scene::loadTex() {}

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