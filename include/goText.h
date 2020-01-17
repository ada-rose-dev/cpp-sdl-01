#pragma once
#include "sysGameObj.h"
#include "sysTextWrapper.h"
using namespace go;

#ifndef GO_TEXT
#define GO_TEXT

class goText : public GameObj {

private:
	TextWrapper* wrapper = new TextWrapper();

public:
	/* Methods */
	goText();
	~goText();

	/* Behaviors */
	void Render();
	void Step();
};

#endif