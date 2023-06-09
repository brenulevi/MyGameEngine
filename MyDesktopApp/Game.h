/********************************************************************************
* 
* File:				Game.h
* Project:			Game Engine
* Author:			Breno Soares Alves
* Creation Date:	04-16-2023
* 
* Subject:			An abstract class which every game will derives. 
* 
********************************************************************************/

#ifndef _GAME_H_
#define _GAME_H_

// --------------------------------------------------------------------------

#include "Window.h"

// --------------------------------------------------------------------------

class Game
{
protected:
	static Window*& window;

public:
	Game();
	virtual ~Game();

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Finalize() = 0;
};

// --------------------------------------------------------------------------

#endif