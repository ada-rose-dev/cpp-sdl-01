#include "Sprite.h"


Sprite::Sprite(SDL_Renderer* r, bool EnableCK){
	Renderer = r;
	ColorKeyEnabled = EnableCK;
}

Sprite::Sprite(SDL_Renderer* r, string path, SpriteGrid grid, bool EnableCK) {
	Renderer = r;
	ColorKeyEnabled = EnableCK;
	LoadFromPath(path, grid);
}

Sprite::Sprite(SDL_Renderer* r, string* paths, SpriteGrid* grids, bool EnableCK) {
	Renderer = r;
	ColorKeyEnabled = EnableCK;
	LoadFromPaths(paths, grids);
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

void Sprite::LoadFromPath(string path, SpriteGrid grid) {
	//Remove previous settings.
	Free();

	w = grid.w;
	h = grid.h;
	//Load texture.
	Sheet = new Texture(Renderer, path, ColorKeyEnabled, ColorKey);

	//Get rows, cols if not passed
	if (grid.cols == -1)
		grid.cols = (Sheet->w-grid.x_off) / (grid.w+grid.x_sep);
	if (grid.rows == -1)
		grid.rows = (Sheet->h-grid.y_off) / (grid.h+grid.y_sep);

	//Iterate over texture.
	ImgCount = grid.cols * grid.rows;
	ImgArr = new SDL_Rect[ImgCount];
	for (int i = 0; i < grid.rows; i++) {
		for (int j = 0; j < grid.cols; j++) {
			int temp_x = grid.x_off + (grid.w + grid.x_sep) * j;
			int temp_y = grid.y_off + (grid.h + grid.y_sep) * i;

			ImgArr[i * grid.cols + j] = {temp_x, temp_y, grid.h, grid.w}; //This *should* be fine??
		}
	}

}

void Sprite::LoadFromPaths(string* paths, SpriteGrid* grids) {

}

void Sprite::Render(int x, int y) {
	//Render TexArr[Frame] at pos (x,y)
	Sheet->RenderPart(x, y, ImgArr[Frame]);
}