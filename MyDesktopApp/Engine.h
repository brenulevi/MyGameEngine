/********************************************************************************
*
* File:				Engine.h
* Project:			Game Engine
* Author:			Breno Soares Alves
* Creation Date:	04-17-2023
*
* Subject:			A class responsable to manage the game (Entry point)
********************************************************************************/

#ifndef _ENGINE_H_
#define _ENGINE_H_

// --------------------------------------------------------------------------

#include "Game.h"
#include "Window.h"

// --------------------------------------------------------------------------

class Engine
{
private:
	int Loop();

public:
	static Game* game;
	static Window* window;

	Engine();
	~Engine();

	int Start(Game* level);
};

// --------------------------------------------------------------------------

#endif
