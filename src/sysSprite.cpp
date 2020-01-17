#include "sysSprite.h"


  /**********************************/
 /*** Constructor, Deconstructor ***/
/**********************************/

Sprite::Sprite(SDL_Renderer* r, bool EnableCK){
	Renderer = r;
	ColorKeyEnabled = EnableCK;

	timer = new Timer();
}


Sprite::Sprite(SDL_Renderer* r, Texture* tex, SpriteGrid grid) {
	Renderer = r;
	ColorKeyEnabled = tex->ColorKeyEnabled;
	if (ColorKeyEnabled)
		ColorKey = tex->GetColorKey();
	LoadFromTex(tex, grid);

	timer = new Timer();
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

	delete timer;
	timer = nullptr;
}


  /**********************************/
 /*** Loading Methods            ***/
/**********************************/

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

void Sprite::SetColorKey(SDL_Color k) {
	ColorKey = k;
	LoadFromTex(Sheet, ImgGrid, false);
}


  /***************/
 /*** Render  ***/
/***************/

void Sprite::Render(int x, int y) {
	//Render TexArr[Frame] at pos (x,y)
	
	timer->resetTime = ImgSpd*1000;

	timer->tick();
	if (timer->trigger)
		Frame++;

	if (Frame >= ImgCount) Frame = 0;

	SDL_Rect* f = ImgArr[Frame];

	if (transVec != nullptr)
		Sheet->RenderPartTransform(x, y, *f, w, h, transVec->rotation, transVec->flip, transVec->origin);
	else
		Sheet->RenderPart(x, y, *f, w, h);
}