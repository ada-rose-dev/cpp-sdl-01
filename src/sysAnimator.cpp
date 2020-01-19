#include "../include/sysAnimator.h"

Animator::Animator() {

}

Animator::~Animator() {

}

void Animator::addPair(AnimVec* p) {
	PairList.push_back(p);
}
void Animator::removePair(AnimVec* p) {
	PairList.remove(p);
}
void Animator::removePair(string name) {
	//iterate through list and find pair with matching name, then remove it.
	for (list<AnimVec*>::iterator it = PairList.begin(); it != PairList.end(); it++) {
		if ((*it)->name == name) {
			PairList.remove((*it));
			return;
		}
	}
}
void Animator::freePair(AnimVec* p) {
	PairList.remove(p);
	delete p;
}
void Animator::freePair(string name) {
	//iterate through list and find pair with matching name, then remove it.
	//Then, delete the pair.
}

Sprite* Animator::getSprite(string name) {
	//Iterate though list and return sprite from pair with associated name.
	list<AnimVec*>::iterator it;
	for (it = PairList.begin(); it != PairList.end(); it++) {
		if ((*it)->name == name)
			return (*it)->spr;
	}
	//Have some sort of indication.
	return nullptr;
}
string Animator::getSpriteName(Sprite* spr) {
	//Iterate though list and return sprite from pair with associated name.
	for (list<AnimVec*>::iterator it = PairList.begin(); it != PairList.end(); it++) {
		if ((*it)->spr == spr)
			return (*it)->name;
	}
	//Have some sort of indication.
	return "NOT FOUND";
}

AnimVec* Animator::getPair(string name) {
	//Iterate though list and return sprite from pair with associated name.
	list<AnimVec*>::iterator it;
	for (it = PairList.begin(); it != PairList.end(); it++) {
		if ((*it)->name == name)
			return (*it);
	}
	//Have some sort of indication.
	return nullptr;
}


void Animator::Render(int x, int y) {
	double delta = (SDL_GetTicks() - lastTime) / 1000.;
	lastTime = SDL_GetTicks();

	Frame += delta * Framerate;
	if (Frame >= SprIndex->ImgCount) Frame = 0;
	SprIndex->SetFrame(Frame);
	SprIndex->Render(x,y);
}


void Animator::setState(string state) {
	AnimState = state;
	SprIndex = getSprite(state);
	SprIndex->transVec = getPair(state)->transVec;
}