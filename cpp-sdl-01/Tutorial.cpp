#include "Tutorial.h"



Tutorial::Tutorial()
{
}


Tutorial::~Tutorial()
{
}

bool Tutorial::render() {
	for (iterator it = ObjList->begin(); it++; it < ObjList->end()) {
		it->render();
	}
}
bool Tutorial::handleEvents() {}
bool Tutorial::loadTex() {}