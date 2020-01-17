#include "sysTexture.h"

//Constructor, Deconstructor
Texture::Texture(SDL_Renderer* Renderer, string path, bool ColorKeyEnabled, SDL_Color ColorKey, int w, int h)
{
	Tex = nullptr;
	this->Renderer = Renderer;
	this->ColorKeyEnabled = ColorKeyEnabled;
	this->ColorKey = ColorKey;
	this->w = w;
	this->h = h;
	this->path = path;
	if (path != "")
		Load(path);
}

Texture::~Texture()
{
	Free();
}


//Methods

	//Color Key
void Texture::SetColorKey(SDL_Color k) {
	this->ColorKey = k;
	Load(path);
}
SDL_Color Texture::GetColorKey() {
	return ColorKey;
}


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
		SDL_SetColorKey(loadedSurface, ColorKeyEnabled, SDL_MapRGB(loadedSurface->format, ColorKey.r, ColorKey.g, ColorKey.b));
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

	return Tex != nullptr;
}
bool Texture::LoadMessage(string message, TTF_Font* font, SDL_Color color) {
	Free();
	//Create texture and surface
	SDL_Texture* newTex = nullptr;
	SDL_Surface* loadedSurface = TTF_RenderText_Solid(font, message.c_str(), color);
	//catch errors
	if (loadedSurface == nullptr)
		printf("SDL_TTF ERR: %s", TTF_GetError());
	else {
		newTex = SDL_CreateTextureFromSurface(Renderer, loadedSurface);
		if (newTex == nullptr)
			printf("SDL ERR: %s", SDL_GetError());
		else {
			this->Tex = newTex;
			this->w = loadedSurface->w;
			this->h = loadedSurface->h;
		}
		SDL_FreeSurface(loadedSurface);
	}

	return Tex != nullptr;
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

void Texture::RenderPart(int x, int y, SDL_Rect section, int w, int h) {
	if (w == -1)
		w = this->w;
	if (h == -1)
		h = this->h;
	SDL_Rect quad = { x, y, w, h };
	if (SDL_RenderCopy(Renderer, Tex, &section, &quad) < 0)
		printf("SDL ERR: %s", SDL_GetError());
	/*
	else
		printf("SDL_RenderCopy success at Texture::RenderPart(%i,%i,{%i,%i,%i,%i})", x, y, section.x, section.y, section.w, section.h );
	*/
}

void Texture::RenderAsBackground() {
	if (SDL_RenderCopy(Renderer, Tex, nullptr, nullptr) < 0)
		printf("SDL ERR: %s", SDL_GetError());
}

void Texture::RenderPartAsBackground(SDL_Rect section) {
	if (SDL_RenderCopy(Renderer, Tex, &section, nullptr) < 0)
		printf("SDL ERR: %s", SDL_GetError());
}




void Texture::RenderTransform(int x, int y, int w, int h, double rotation, SDL_RendererFlip flip, SDL_Point origin) {
	SDL_Rect quad = { x, y, w, h };
	if (SDL_RenderCopyEx(Renderer, Tex, nullptr, &quad, rotation, &origin, flip) < 0)
		printf("SDL ERR: %s", SDL_GetError());
}
void Texture::RenderPartTransform(int x, int y, SDL_Rect section, int w, int h, double rotation, SDL_RendererFlip flip, SDL_Point origin) {
	SDL_Rect quad = { x, y, w, h };
	if (SDL_RenderCopyEx(Renderer, Tex, &section, &quad, rotation, &origin, flip) < 0)
		printf("SDL ERR: %s", SDL_GetError());
}