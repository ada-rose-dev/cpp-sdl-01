#include "../include/sysTextWrapper.h"

  /*****************************************/
 /*** Costructor, Deconstructor, Free() ***/
/*****************************************/
//Construct, Deconstruct
TextWrapper::TextWrapper() {
	FontList = new list<Font*>;
	MessageList = new list<Message*>;
}
TextWrapper::~TextWrapper() {
	Free();
	delete[] FontList;
}
//Free
void TextWrapper::Free() {
	FontList->erase(FontList->begin(), FontList->end());
	MessageList->erase(MessageList->begin(), MessageList->end());
}


  /************/
 /*** Font ***/
/************/
//Create
Font* TextWrapper::CreateFont(string name, string path, double ptsize, bool load) {
	Font* newFont = new Font{ name, TTF_OpenFont(path.c_str(),ptsize), path, ptsize };
	if (newFont->index == nullptr) {
		printf("SDL_TTF ERR: %s", TTF_GetError());
	}

	if (load)
		FontList->push_back(newFont);
	return newFont;
}
//Load
void TextWrapper::LoadFont(Font* font) {
	FontList->push_back(font);
}
Font* TextWrapper::UnloadFont(string name) {
	Font* f = GetFont(name);
	FontList->remove(GetFont(name));
	return f;
}
//Erase
void TextWrapper::EraseFont(string name) {
	Font* f = GetFont(name);
	FontList->remove(GetFont(name));
	delete f;
}
void TextWrapper::EraseAllFonts() {
	FontList->erase(FontList->begin(), FontList->end());
}


  /***************/
 /*** Message ***/
/***************/
//Create
Message* TextWrapper::CreateMessage(string name, string message, Font* font, bool load) {
	Texture* t = new Texture(Renderer);
	t->LoadMessage(message, font->index);
	Message* newMessage = new Message{ name, message, font, t };
	MessageList->push_back(newMessage);
	return newMessage;
}
Message* TextWrapper::CreateMessage(string name, string message, string font, bool load) {
	return CreateMessage(name, message, GetFont(font), load);
}
//Load
void TextWrapper::LoadMessage(Message* message) {
	MessageList->push_back(message);
}
Message* TextWrapper::UnloadMessage(string name) {
	Message* m = GetMessage(name);
	MessageList->remove(m);
	return m;
}
//Erase
void TextWrapper::EraseMessage(string name) {
	Message* m = GetMessage(name);
	MessageList->remove(m);
	delete m;
}
void TextWrapper::EraseAllMessages() {
	FontList->erase(FontList->begin(), FontList->end());
}


  /************************/
 /*** Getters, Setters ***/
/************************/
//Get
Font* TextWrapper::GetFont(string name) {
	for (list<Font*>::iterator it = FontList->begin(); it != FontList->end(); it++) {
		if ((*it)->name == name)
			return (*it);
	}
	printf("Font %s was not found!", name.c_str());
	return nullptr;
}
Message* TextWrapper::GetMessage(string name) /* TODO - add ASSET_NOT_FOUND_EXCEPTION */ {
	for (list<Message*>::iterator it = MessageList->begin(); it != MessageList->end(); it++) {
		if ((*it)->name == name)
			return (*it);
	}
	printf("Message %s was not found!", name.c_str());
	return nullptr;
}
//Set
Font* TextWrapper::SetFont(string name, double ptsize, string path) {
	Font* f = GetFont(name);
	
	if (f == nullptr)
		return nullptr;

	if (path == "")
		path = f->path;

	delete f->index;
	f->index = TTF_OpenFont(path.c_str(),ptsize);
	f->path = path;
	f->ptsize = ptsize;
}
Message* TextWrapper::SetMessage(string name, string message, Font* font) {
	Message* m = GetMessage(name);
	m->message = message;
	m->font = font;
	return m;
}
Message* TextWrapper::SetMessage(string name, string message, string font) {
	return SetMessage(name, message, GetFont(font));
}


  /**************/
 /*** Render ***/
/**************/

//auto ParseSettings(string settings) {} - TODO

void TextWrapper::RenderMessage(string name, int x, int y, string settings) {
	//Loop through textures, render matching
	GetMessage(name)->index->Render(x, y);
}