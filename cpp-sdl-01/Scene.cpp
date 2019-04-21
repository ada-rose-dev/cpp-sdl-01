#include "Scene.h"



Scene::Scene()
{
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
	for (list<GameObj*>::iterator it = ObjList->begin(); it != ObjList->end(); it++) {
		(*it)->Render(); //Dereference iterator so it can access GameObj methods.
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