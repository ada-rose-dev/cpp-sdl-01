#include "../include/sysSDLRunner.h"

SDLRunner::SDLRunner()
{
	init();
}
SDLRunner::~SDLRunner()
{
	//Delete shader program
	glDeleteProgram(gProgramID);

	////Destroy renderer
	//SDL_DestroyRenderer(Renderer);
	//Renderer = nullptr;

	//Destroy window
	SDL_DestroyWindow(Window);
	Window = nullptr;

	//Quit SDL
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}

//init
bool SDLRunner::init() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		return printErr();

/*	//Populate window
	Window = SDL_CreateWindow("SDL Scene", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ScrWidth, ScrHeight, SDL_WINDOW_SHOWN);
	if (Window == nullptr)
		return printErr();*/

	//Initialize OpenGL
	createGLContext(3,1);

	///-- Below is for SDL's in-built texture rendering. We're moving to OpenGL, BABEY

	////Get screen surface
	//ScreenSurf = SDL_GetWindowSurface(Window);
	//if (ScreenSurf == nullptr)
	//	return printErr();

	////Create renderer for texture
	//Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	//if (Renderer == nullptr)
	//	return printErr();

	////Init renderer
	//SDL_SetRenderDrawColor(Renderer, 0x11, 0x11, 0x11, 0x11); //Takes hex values for RGBA.

	////Init SDL_image
	//int imgFlags = IMG_INIT_PNG;
	//if (!(IMG_Init(imgFlags) & imgFlags)) //This line ensures we're initializing the flags we want to, and only those flags. Bitwise-AND.
	//	return printErrIMG();

	////Init SDL_ttf
	//if (TTF_Init() == -1) {
	//	printf("SDL_TTF ERR: %s\n", TTF_GetError());
	//	return false;
	//}

	return true;
}


SDL_Surface* SDLRunner::loadSurf(string path) {

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
	SDL_Surface* out = SDL_ConvertSurface(loaded, ScreenSurf->format, 0);
	//handle error
	if (out == nullptr)
		printf("SDL Err: %s\n Path: %s\n", SDL_GetError(), path.c_str());
	//free loaded, return
	SDL_FreeSurface(loaded);
	return out;
}


//Helpers - Error
bool SDLRunner::printErr() {
	printf("SDL ERR: %s\n", SDL_GetError());
	return false;
}
bool SDLRunner::printErr(string message, string path) {
	printf("%s",(message + "\n").c_str());
	if (path == "")
		printf("SDL ERR: %s\n", SDL_GetError());
	else printf("SDL ERR: %s\n PATH: %s\n", SDL_GetError(), path.c_str());
	return false;
}
bool SDLRunner::printErrIMG() {
	printf("SDL_Image ERR: %s\n", IMG_GetError());
	return false;
}


////////////////////////////////
/// OpenGL 3.3
////////////////////////////////

//Creation

bool SDLRunner::createGLContext(const int majorVersion, const int minorVersion) {
	//Set up version.
	bool success = true;
	
	//Create window
	Window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ScrWidth, ScrHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, majorVersion);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, minorVersion);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	//Init GLEW
	gContext = SDL_GL_CreateContext(Window);
	if (gContext == NULL)
	{
		printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Initialize GLEW
		glewExperimental = GL_TRUE;
		GLenum glewError = glewInit();
		if (glewError != GLEW_OK)
		{
			printf("Error initializing GLEW! %s\n", glewGetErrorString(glewError));
		}

		//Use Vsync
		if (SDL_GL_SetSwapInterval(1) < 0)
		{
			printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
		}

		//Initialize OpenGL
		if (!initGL())
		{
			printf("Unable to initialize OpenGL!\n");
			success = false;
		}
	}

	return success;
}

bool SDLRunner::initGL()
{
	//Success flag
	bool success = true;

	//Generate program
	gProgramID = glCreateProgram();

	//Create vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	//Get vertex source
		//- This is to loaded from external files.
	const GLchar* vertexShaderSource[] =
	{
		"#version 140\nin vec2 LVertexPos2D; void main() { gl_Position = vec4( LVertexPos2D.x, LVertexPos2D.y, 0, 1 ); }"
	};

	//Set vertex source
		//- Create an interface to easily load/set shaders.
	glShaderSource(vertexShader, 1, vertexShaderSource, NULL);

	//Compile vertex source
	glCompileShader(vertexShader);

	//Check vertex shader for errors
	GLint vShaderCompiled = GL_FALSE;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vShaderCompiled);
	if (vShaderCompiled != GL_TRUE)
	{
		printf("Unable to compile vertex shader %d!\n", vertexShader);
		printShaderLog(vertexShader);
		success = false;
	}
	else
	{
		//Attach vertex shader to program
		glAttachShader(gProgramID, vertexShader);


		//Create fragment shader
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		//Get fragment source
		const GLchar* fragmentShaderSource[] =
		{
			"#version 140\nout vec4 LFragment; void main() { LFragment = vec4( 1.0, 1.0, 1.0, 1.0 ); }"
		};

		//Set fragment source
		glShaderSource(fragmentShader, 1, fragmentShaderSource, NULL);

		//Compile fragment source
		glCompileShader(fragmentShader);

		//Check fragment shader for errors
		GLint fShaderCompiled = GL_FALSE;
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fShaderCompiled);
		if (fShaderCompiled != GL_TRUE)
		{
			printf("Unable to compile fragment shader %d!\n", fragmentShader);
			printShaderLog(fragmentShader);
			success = false;
		}
		else
		{
			//Attach fragment shader to program
			glAttachShader(gProgramID, fragmentShader);


			//Link program
			glLinkProgram(gProgramID);

			//Check for errors
			GLint programSuccess = GL_TRUE;
			glGetProgramiv(gProgramID, GL_LINK_STATUS, &programSuccess);
			if (programSuccess != GL_TRUE)
			{
				printf("Error linking program %d!\n", gProgramID);
				printProgramLog(gProgramID);
				success = false;
			}
			else
			{
				//Get vertex attribute location
				gVertexPos2DLocation = glGetAttribLocation(gProgramID, "LVertexPos2D");
				if (gVertexPos2DLocation == -1)
				{
					printf("LVertexPos2D is not a valid glsl program variable!\n");
					success = false;
				}
				else
				{
					//Initialize clear color
					glClearColor(0.f, 0.f, 0.f, 1.f);

					//VBO data -- TO BE LOADED EXTERNALLY
					GLfloat vertexData[] =
					{
						-0.5f, -0.5f,
						 0.5f, -0.5f,
						 0.5f,  0.5f,
						-0.5f,  0.5f
					};

					//IBO data - TO BE LOADED EXTERNALLY
					GLuint indexData[] = { 0, 1, 2, 3 };

					//Create VBO
					glGenBuffers(1, &gVBO);
					glBindBuffer(GL_ARRAY_BUFFER, gVBO);
					glBufferData(GL_ARRAY_BUFFER, 2 * 4 * sizeof(GLfloat), vertexData, GL_STATIC_DRAW);

					//Create IBO
					glGenBuffers(1, &gIBO);
					glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIBO);
					glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(GLuint), indexData, GL_STATIC_DRAW);
				}
			}
		}
	}

	return success;
}

//Logging

void SDLRunner::printProgramLog(GLuint program)
{
	//Make sure name is shader
	if (glIsProgram(program))
	{
		//Program log length
		int infoLogLength = 0;
		int maxLength = infoLogLength;

		//Get info string length
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

		//Allocate string
		char* infoLog = new char[maxLength];

		//Get info log
		glGetProgramInfoLog(program, maxLength, &infoLogLength, infoLog);
		if (infoLogLength > 0)
		{
			//Print Log
			printf("%s\n", infoLog);
		}

		//Deallocate string
		delete[] infoLog;
	}
	else
	{
		printf("Name %d is not a program\n", program);
	}
}

void SDLRunner::printShaderLog(GLuint shader)
{
	//Make sure name is shader
	if (glIsShader(shader))
	{
		//Shader log length
		int infoLogLength = 0;
		int maxLength = infoLogLength;

		//Get info string length
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

		//Allocate string
		char* infoLog = new char[maxLength];

		//Get info log
		glGetShaderInfoLog(shader, maxLength, &infoLogLength, infoLog);
		if (infoLogLength > 0)
		{
			//Print Log
			printf("%s\n", infoLog);
		}

		//Deallocate string
		delete[] infoLog;
	}
	else
	{
		printf("Name %d is not a shader\n", shader);
	}
}

//Rendering

void SDLRunner::renderGL() {
	//Clear color buffer
	glClear(GL_COLOR_BUFFER_BIT);

	//Bind program
	glUseProgram(gProgramID);

	//Enable vertex position
	glEnableVertexAttribArray(gVertexPos2DLocation);

	//Set vertex data
	glBindBuffer(GL_ARRAY_BUFFER, gVBO);
	glVertexAttribPointer(gVertexPos2DLocation, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL);

	//Set index data and render
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIBO);
	glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL);

	//Disable vertex position
	glDisableVertexAttribArray(gVertexPos2DLocation);

	//Unbind program
	glUseProgram(NULL);
}