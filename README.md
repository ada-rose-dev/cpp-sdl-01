# cpp-sdl-01
Open source SDL game engine project by Phoenix Ada Rose Mandala.

This documentation last updated 8 June 2019.

# File Structure #
Below is a rough sketch of the overall project structure.
_main.cpp_
>game
>>objects
>>>_gameobject classes_ (go\*.cpp)
>>textures
>>>_images_ (tx\*.png)
>>sounds
>>>_audio files_ (sn\*.wav)
>sys
>>_System implementation files_ (.cpp)
>>headers
>>>_System header files_ (.h,.hpp)




# Class Documentation #
## System Hierarchy ##
_System objects run the game. They are the parent objects for every class used in the game._

SDLRunner - _Runs all game commands. Implements SDL._
 * Scene - _Scenes to render._
 * * GameObj - _(local)_
 * * * Sprite - _(base)_
 * * * Texture - _(base)_
 * * Sprite - _(static)_
 * * * Texture - _(base)_
 * * Texture - _(static)_
 * GameObj - _(globals)_
 * * Sprite - _(base)_
 * * Texture - _(base)_

## _SDLRunner_
Runs the game.
### Run Sequence
The following is listed in execution order, meaning items further down the list have higher execution priority. E.g. local objects will always render _after_ static sprites.
 * tick()
 * * Global Objects
 * * Scene Objects
 * render()
 * * Scene->Render()
 * * * Textures
 * * * Sprites
 * * * Objects
 * * Global GameObj->Render()
 
## _Scene_ 
Scenes to be rendered. Will be populated with objects, sprites, textures, etc.
## _GameObj_
GameObjs have _behaviors_. They change over time.
### _Global_
These GameObjs are handled by SDLRunner.
### _Local_
These GameObjs are handled by Scene.
## _Sprite_
Animated textures.
### _Base_
Typically unnamed, used with GameObjs.
### _Static_
Sprites that will be handleded by the Scene.
## _Texture_
Non-animated images.
### _Base_
Typically unnamed, used with Sprites.
### _Static_
Textures that will be handled by the Scene.
