/**
 sysSDLRunner.h
 Implementation file for SDLRunner class.
 Includes: none
 Included by: sysCommon.h -> sysTexture.h -> sysSprite.h -> sysAnimator.h     -> sysGameObj.h -> sysScene.h -> sysGameRunner.h
                                         \-> sysText.h   -> sysTextMachine.h -/
                                          \-> sysSound.h -> sysMixer.h      -/  
 Parents: none
 Children: none
 Author: Phoenix Mandala
 Last edited: 6-27-19
*/

#ifndef SDL_RUNNER
#define SDL_RUNNER

//SDL
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

//OpenGL
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SDL2/SDL_opengl.h>
#include <GL/GLU.h>


#include <list>
#include <string>
using namespace std;

class SDLRunner
{
private:
	//Error methods
	bool printErr();
	bool printErr(string message, string path);
	bool printErrIMG();

	//Members
	int ScrWidth = 640;
	int ScrHeight = 480;

public:
	//Create, Destroy
	SDLRunner();
	~SDLRunner();
	bool init();

	//Video
	SDL_Window* Window = nullptr;
	SDL_Renderer* Renderer = nullptr;
	SDL_Surface* ScreenSurf = nullptr;

	SDL_Surface* loadSurf(string path);

	//OpenGL
	SDL_GLContext gContext;

	GLuint gProgramID = 0;
	GLint gVertexPos2DLocation = -1;
	GLuint gVBO = 0; //Vertex Buffer Objects -- Vertices
	GLuint gIBO = 0; //Index Buffer Objects -- Vertex ordering

	bool createGLContext(const int majorVersion, const int minorVersion);
	bool initGL();
	void printProgramLog(GLuint program);
	void printShaderLog(GLuint shader);

	void renderGL();




};

#endif