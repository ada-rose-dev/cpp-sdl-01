#pragma once
#include "../../../sys/headers/GameObj.h"

#ifndef GO_PLAYER
#define GO_PLAYER
class goPlayer : public GameObj {
private:
	Sprite* SprIndex = nullptr;
public:
	goPlayer();
	~goPlayer();
};

#endif // !OBJPLAYER
