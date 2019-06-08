#pragma once
#include "Sprite.h"
class GameObj
{
private:
	Sprite* SprIndex = nullptr;
public:
	GameObj();
	~GameObj();

	void SetSprite(Sprite* s) { SprIndex = s; }
	Sprite* GetSprite() { return SprIndex; }

	void Render();
	void HandleEvents(const Uint8* KeyState);

	int x = 0;
	int y = 0;
};

