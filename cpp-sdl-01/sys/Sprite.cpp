#include "./headers/Sprite.h"


Sprite::Sprite(SDL_Renderer* r, bool EnableCK){
	Renderer = r;
	ColorKeyEnabled = EnableCK;
}


Sprite::Sprite(SDL_Renderer* r, Texture* tex, SpriteGrid grid) {
	Renderer = r;
	ColorKeyEnabled = tex->ColorKeyEnabled;
	if (ColorKeyEnabled)
		ColorKey = tex->ColorKey;
	LoadFromTex(tex, grid);
}

Sprite::~Sprite()
{
	Free();
}

void Sprite::Free() {
	w = 0;
	h = 0;

	ImgCount = 0;
	Frame = 0;

	delete[] ImgArr;
	ImgArr = nullptr;

	delete Sheet;
	Sheet = nullptr;
}

void Sprite::LoadFromTex(Texture* tex, SpriteGrid grid, bool free) {
	if (free)
		Free();

	//Set members.
	ImgPath = tex->path;
	ImgGrid = grid;
	w = grid.w;
	h = grid.h;
	Sheet = tex;

	//Get rows, cols if not passed
	if (grid.cols == -1)
		grid.cols = (Sheet->w - grid.x_off) / (grid.w + grid.x_sep);
	if (grid.rows == -1)
		grid.rows = (Sheet->h - grid.y_off) / (grid.h + grid.y_sep);

	//Make sure dunkasses don't screw themselves over with a bad call
	if (grid.cols < 1) grid.cols = 1;
	if (grid.rows < 1) grid.rows = 1;

	//Iterate over texture.
	ImgCount = grid.cols * grid.rows;
	ImgArr = new SDL_Rect* [ImgCount];
	for (int i = 0; i < grid.rows; i++) {
		for (int j = 0; j < grid.cols; j++) {
			int temp_x = grid.x_off + (grid.w + grid.x_sep) * j;
			int temp_y = grid.y_off + (grid.h + grid.y_sep) * i;

			SDL_Rect* temp = new SDL_Rect { temp_x, temp_y, grid.h, grid.w }; 
			ImgArr[i * grid.cols + j] = temp;
		}
	}
}

void Sprite::Render(int x, int y) {
	//Render TexArr[Frame] at pos (x,y)
	Frame+=ImgSpd;
	if (Frame >= ImgCount) Frame = 0;
	Sheet->RenderPart(x, y, *(ImgArr[(int)(Frame)]),w,h);

	/* Render all frames - for debug *
	for (int i = 0; i < ImgCount; i++) {
		Sheet->RenderPart(x+(i+1)*(w+2), y, *(ImgArr[i]), w, h);
	}
	/**/
}

void Sprite::SetColorKey(SDL_Color k) {
	ColorKey = k;
	LoadFromTex(Sheet, ImgGrid, false);
}