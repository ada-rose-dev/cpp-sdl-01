#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
using namespace std;

//Overall, this would be easier with an SDL handler class. This way we can avoid global variables but still have the scope we need.


#pragma region Initalize SDL
//globals - to be removed later on
SDL_Window* gWin = nullptr;
SDL_Texture* gTex = nullptr;
SDL_Renderer* gRenderer = nullptr;
SDL_Surface* gScrSurf = nullptr;

//declare functions
bool init();
void close();
bool loadMedia();
void render();
SDL_Surface* loadSurf(string path);
SDL_Texture* loadTex(string path);

bool printErr();
bool printErr(string message, string path);
bool printErrIMG();

#pragma region Functions

#pragma region helpers
bool printErr() {
	printf("SDL ERR: %s\n", SDL_GetError());
	return false;
}
bool printErr(string message, string path) {
	printf((message + "\n").c_str());
	if (path == "")
		printf("SDL ERR: %s\n", SDL_GetError());
	else printf("SDL ERR: %s\n PATH: %s\n", SDL_GetError(), path.c_str());
	return false;
}

bool printErrIMG() {
	printf("SDL_Image ERR: %s\n", IMG_GetError());
	return false;
}

#pragma endregion

#pragma region loading funcs
bool init() {
	//const
	const int SCR_WIDTH = 640;
	const int SCR_HEIGHT = 480;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		return printErr();

	//Populate window
	gWin = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCR_WIDTH, SCR_HEIGHT, SDL_WINDOW_SHOWN);
	if (gWin == nullptr)
		return printErr();

	//Create renderer for texture
	gRenderer = SDL_CreateRenderer(gWin, -1, SDL_RENDERER_ACCELERATED);
	if (gRenderer == nullptr)
		return printErr();

	//Init renderer
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF); //Takes hex values for RGBA.

	//Init SDL_image
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags)) //This line ensures we're initializing the flags we want to, and only those flags. Bitwise-AND.
		return printErrIMG();
	return true;
}
bool loadMedia() {
	//Not loading anything this time - just doing geometry!
	return true;
}
void close() {

	//Destroy texture
	SDL_DestroyTexture(gTex);
	gTex = nullptr;

	//Destroy renderer
	SDL_DestroyRenderer(gRenderer);
	gRenderer = nullptr;

	//Destroy window
	SDL_DestroyWindow( gWin );
	gWin = nullptr;

	//Quit SDL
	IMG_Quit();
	SDL_Quit();
}

SDL_Texture* loadTex(string path) {
	SDL_Texture* newTex = nullptr;

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == nullptr)
		printErrIMG();
	else {
		newTex = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTex == nullptr)
			printErr("Error creating texture!",path);
		SDL_FreeSurface(loadedSurface);
	}

	return newTex;
}
SDL_Surface* loadSurf(string path) {

	//load
	SDL_Surface* loaded = IMG_Load(path.c_str());
	//handle error
	if (loaded == nullptr){
		printf("SDL Err: %s\n Path: %s\n", SDL_GetError(), path.c_str());
		printf("SDL_image Err: %s\n", IMG_GetError());
		SDL_FreeSurface(loaded);
		return nullptr;
	}

	//optimize - BMPs are 24 bit, so need to be converted to be displayed. here we set the images to the correct format for the main surface.
	//if we don't convert the format here, it will be converted every time an image is blit onto the screen.
	SDL_Surface* out = SDL_ConvertSurface(loaded, gScrSurf->format, NULL);
	//handle error
	if (out == nullptr)
		printf("SDL Err: %s\n Path: %s\n", SDL_GetError(), path.c_str());
	//free loaded, return
	SDL_FreeSurface(loaded);
	return out;
}

void render() {
	SDL_SetRenderDrawColor(gRenderer, 0x11, 0x11, 0x11, 0xff);
	SDL_RenderClear(gRenderer);

	//Draw some geometry. This is where the lesson is!
	//Note: SDL does coordinates like GML - Y is inverted.
	SDL_Rect fillRect = { 16,16,32,32 };
	SDL_Rect outlineRect = { 32,32,48,48 };
	SDL_SetRenderDrawColor(gRenderer, 0xff, 0x00, 0x00, 0xff);
	SDL_RenderFillRect(gRenderer, &fillRect);
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0xff, 0x00, 0xff);
	SDL_RenderDrawRect(gRenderer, &outlineRect);
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0xff, 0xff);
	SDL_RenderDrawLine(gRenderer, 128, 64, 64, 128);

	SDL_RenderCopy(gRenderer, gTex, NULL, NULL);
	SDL_RenderPresent(gRenderer);
}

#pragma endregion
#pragma endregion
#pragma endregion

int main(int argc, char* argv[]) {
	if (!init()) {
		printf("Failed to init!\n");
	}
	else {
		if (!loadMedia()) {
			printf("Media load failed!\n");
		}
		//Main loop
		else {
			bool run = true;
			SDL_Event e;

			int tick = 0;
			while (run) {
				//clock
				tick++;

				//SDL_Event handler
				//run = eventHandler(e);
				while (SDL_PollEvent(&e) != 0) {
					switch (e.type) {
					case SDL_QUIT:
						run = false;
						break;
						
					case SDL_KEYDOWN:
						switch (e.key.keysym.sym)
						{
						//esc
						case SDLK_ESCAPE:
							run = false;
							break;
						}
						break;
					}
				}
				//Render
				//render();

				SDL_SetRenderDrawColor(gRenderer, 0x11, 0x11, 0x11, 0xff);
				SDL_RenderClear(gRenderer);
				SDL_SetRenderDrawColor(gRenderer, 0xff, 0x00, 0xff, 0xff);
				for (double i = 0; i < 32; i++) {
					int r = 16 + 32*sin(tick/1000.);
					double rot = tick / 1000.0;
					SDL_RenderDrawPoint(gRenderer, 128 + r * sin(rot + 6.28 * i / 16.0), 128 + r * cos(rot +6.28 * i / 16.0));
				}

				SDL_RenderPresent(gRenderer);
			}
		}
	}
	close();
	return 0;
}