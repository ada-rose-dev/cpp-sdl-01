#include "./headers/GameObj.h"

GameObj::GameObj()
{
}


GameObj::~GameObj()
{
}

void GameObj::Render() {
	if (SprIndex != nullptr)
		SprIndex->Render(x,y);
}

void GameObj::HandleEvents(const Uint8* keyState) {

}