#include "sysTexture.h"

class Font {
public:
	TTF_Font* font = nullptr;
	Texture* tex = nullptr;

	Font(string path, double ptsize=12);
	~Font();
	void Free();
	void Load(string path, double ptsize=12);
};