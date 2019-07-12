#include "headers/sysGameRunner.h"

GameRunner::GameRunner() {
	ObjList = new list<GameObj*>;
	SceneList = new list<Scene*>;

	GameStart();
}

GameRunner::~GameRunner() {
	GameEnd();

	ObjList->clear();
	SceneList->clear();
	delete ObjList;
	delete SceneList;
}

//run
bool GameRunner::HandleEvents() {
	bool run = true;
	//Handle system events.

	while (SDL_PollEvent(&Event) != 0) {
		if (Event.key.repeat == 0) //Don't handle key repeats
		switch (Event.type) {
			//Hit "X" on window
		case SDL_QUIT:
			run = false;
			break;
			//Exit with ESC
		case SDL_KEYDOWN:
			switch (Event.key.keysym.sym)
			{
				//esc
			case SDLK_ESCAPE:
				run = false;
				break;
			}
			break;
		}

		//Handle current scene's events (preferably only keystates)
		if (CurrentScene != nullptr)
			CurrentScene->handleEvents(Event);
	}

	//Step event
	CurrentScene->step();


	return run;
}
void GameRunner::Render() {
	//Clear screen.
	SDL_RenderClear(Renderer);

	//Render scene.
	if (CurrentScene == nullptr)
	{
		CurrentScene = SceneList->back();
		if (CurrentScene == nullptr)
			throw exception("FATAL ERROR: CurrentScene not set!");
	}
	CurrentScene->render();

	SDL_RenderPresent(Renderer);
}

//Adding, Removing
void GameRunner::AddScene(Scene* s) {
	SceneList->push_back(s);
}
void GameRunner::FreeScene(Scene* s) {
	SceneList->remove(s);
}
void GameRunner::SetScene(Scene* s) {
	CurrentScene = s;
}


//Game Start, End
void GameRunner::GameStart() {
}

void GameRunner::GameEnd() {

}