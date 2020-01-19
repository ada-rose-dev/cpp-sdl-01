#pragma once
#include "sysTexture.h"

struct Font {
	string name;
	TTF_Font* index;
	string path;
	double ptsize;
};

struct Message {
	string name;
	string message;
	Font* font;
	Texture* index;
};

class TextWrapper {
protected:
	//Members
	list<Font*>* FontList = nullptr;
	list<Message*>* MessageList = nullptr;

public:
		//Constructor, Deconstructor, Free()
	TextWrapper(); //Constructor
	~TextWrapper(); //Deconstructor
	void Free(); //Unloads all fonts and messages.

		//Font
	Font* CreateFont(string name, string path, double ptsize, bool load=true); //Creates a font.
	void LoadFont(Font* font); //Loads a font to FontList
	Font* UnloadFont(string name); //Unloads a single font by name. Returns that font.
	void EraseFont(string name); //Deletes a font.
	void EraseAllFonts(); //Erases all fonts.
	
		//Message
	Message* CreateMessage(string name, string message, Font* font, bool load=true); //Adds a message.
	Message* CreateMessage(string name, string message, string font, bool load = true); //Adds a message.
	void LoadMessage(Message* message); //Loads a message to MessageList
	Message* UnloadMessage(string name); //Removes a message.
	void EraseMessage(string name); //Deletes a message.
	void EraseAllMessages(); //Erases all messages.

		//Getters and Setters
	Font* GetFont(string name); //Return Font by name.
	Message* GetMessage(string name); //Return Message by name.

	Font* SetFont(string name, double ptsize, string path=""); //Modifies a font.

	Message* SetMessage(string name, string message, Font* font=nullptr); //Modifies a message.
	Message* SetMessage(string name, string message, string font=""); //Modifies a message.

	void RenderMessage(string name, int x, int y, string settings=""); //Renders a single message.
};