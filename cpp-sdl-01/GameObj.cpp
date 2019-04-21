#include "GameObj.h"

GameObj::GameObj()
{
}


GameObj::~GameObj()
{
}

void GameObj::Render() {
	SprIndex->Render(x,y);
}
