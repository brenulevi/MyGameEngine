/********************************************************************************
*
* File:				Engine.cpp
* Project:			Game Engine
* Author:			Breno Soares Alves
* Creation Date:	04-17-2023
*
* Subject:			A class responsable to manage the game (Entry point)
********************************************************************************/

#include "Engine.h"
#include <Windows.h>

// --------------------------------------------------------------------------
// Static attributes initialization

Game* Engine::game = nullptr;
Window* Engine::window = nullptr;

// --------------------------------------------------------------------------

Engine::Engine()
{
	window = new Window();
}

// --------------------------------------------------------------------------

Engine::~Engine()
{
	delete game;
	delete window;
}

// --------------------------------------------------------------------------

int Engine::Start(Game* level)
{
	game = level;

	window->Create();

	return Loop();
}

// --------------------------------------------------------------------------

int Engine::Loop()
{
	MSG msg = { 0 };
	HDC hdc;
	RECT rect;

	hdc = GetDC(window->getWindowId());

	GetClientRect(window->getWindowId(), &rect);

	game->Init();

	do
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			game->Update();

			FillRect(hdc, &rect, CreateSolidBrush(window->getWindowBackgroundColor()));

			game->Draw();

			Sleep(16);		// FPS CONTROL (TEMPORARY)
		}

	} while (msg.message != WM_QUIT);

	game->Finalize();

	ReleaseDC(window->getWindowId(), hdc);

	return int(msg.wParam);
}