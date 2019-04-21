# cpp-sdl-01
Learning SDL


## Current Project
### Restructuring main.cpp
I'm going to be completely restructing the main.cpp in this file.
 * I intend to make the code more modable so I can implement the tutorials as classes.
 * I will add a parent class for the tutorial classes to inherit from.
 * Main.cpp will initialize and close SDL, as it already does.
### Building Game Structure
See further down for reference.

# Hierarchy
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

# Class Documentation
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
