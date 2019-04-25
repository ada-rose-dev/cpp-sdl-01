#include "Texture.h"

//Constructor, Deconstructor
Texture::Texture(SDL_Renderer* Renderer, string path, bool ColorKeyEnabled, SDL_Color ColorKey)
{
	Tex = nullptr;
	this->Renderer = Renderer;
	this->ColorKeyEnabled = ColorKeyEnabled;
	this->ColorKey = ColorKey;
	w = 0;
	h = 0;
	if (path != "")
		Load(path);
}

Texture::~Texture()
{
	Free();
}


//Methods
	//Load
bool Texture::Load(string path) {
	//Remove previous texture.
	Free();

	//Load texture.
	SDL_Texture* newTex = nullptr;

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == nullptr) {
		printf("SDL_IMG ERR: %s", IMG_GetError());
	}
	else {
		newTex = SDL_CreateTextureFromSurface(Renderer, loadedSurface);
		if (newTex == nullptr){
			printf("SDL ERR: %s", SDL_GetError());
		}
		else {
			//Only replace texture if load is successful.
			Tex = newTex;
			w = loadedSurface->w;
			h = loadedSurface->h;
		}
		SDL_FreeSurface(loadedSurface);
	}

	return newTex != nullptr;
}

	//Free
void Texture::Free() {
	if (Tex != nullptr) {
		SDL_DestroyTexture(Tex);
		Tex = nullptr;
		w = 0;
		h = 0;
	}
}
	//Render
void Texture::Render(int x, int y) {
	SDL_Rect quad = { x, y, w, h };
	if (SDL_RenderCopy(Renderer, Tex, nullptr, &quad) < 0)
		printf("SDL ERR: %s", SDL_GetError());
}

void Texture::RenderPart(int x, int y, SDL_Rect section) {
	SDL_Rect quad = { x, y, w, h };
	if (SDL_RenderCopy(Renderer, Tex, &section, &quad) < 0)
		printf("SDL ERR: %s", SDL_GetError());
}

void Texture::RenderAsBackground() {
	if (SDL_RenderCopy(Renderer, Tex, nullptr, nullptr) < 0)
		printf("SDL ERR: %s", SDL_GetError());
}

void Texture::RenderPartAsBackground(SDL_Rect section) {
	if (SDL_RenderCopy(Renderer, Tex, &section, nullptr) < 0)
		printf("SDL ERR: %s", SDL_GetError());
}