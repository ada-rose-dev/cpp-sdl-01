#pragma once
#include "Sprite.h"
class GameObj
{
private:
	Sprite* SprIndex = nullptr;
public:
	GameObj();
	~GameObj();

	bool SetSprite(Sprite* s) { SprIndex = s; }
	Sprite* GetSprite(Sprite* s) { return SprIndex; }

	int x = 0;
	int y = 0;
};

