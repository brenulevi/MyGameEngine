/********************************************************************************
*
* File:				MyGame.cpp
* Project:			Game Engine
* Author:			Breno Soares Alves
* Creation Date:	04-17-2023
*
* Subject:			My Game actually.
********************************************************************************/

#include "Engine.h"
#include "Game.h"
#include <sstream>

// --------------------------------------------------------------------------

class MyGame : public Game
{
private:
	std::stringstream textSize;
	std::stringstream textMode;
	std::stringstream textMouse;

public:
	void Init();
	void Update();
	void Draw();
	void Finalize();
};

// --------------------------------------------------------------------------

void MyGame::Init()
{
	textSize << "Tamanho: " << window->getWindowWidth() << " x " << window->getWindowHeight();
	textMode << "Formato: " << (window->getWindowMode() == WINDOWED ? "Em janela" : "Tela cheia");
}

// --------------------------------------------------------------------------

void MyGame::Update()
{
	if (window->KeyDown(VK_ESCAPE))
		window->Close();

	textMouse.str("");
	textMouse << window->MouseX() << " x " << window->MouseY();
}

// --------------------------------------------------------------------------

void MyGame::Draw()
{
	window->Print("Window Game Zero", 10, 10, RGB(255, 255, 255));
	window->Print(textSize.str(), 10, 50, RGB(255, 255, 255));
	window->Print(textMode.str(), 10, 70, RGB(255, 255, 255));
	window->Print(textMouse.str(), 10, 90, RGB(255, 255, 255));
}

// --------------------------------------------------------------------------

void MyGame::Finalize()
{
}

// --------------------------------------------------------------------------

int APIENTRY WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow
)
{
	Engine* engine = new Engine();
	engine->window->setMode(WINDOWED);
	engine->window->setSize(960, 540);
	engine->window->setBackgroundColor(0, 0, 0);
	engine->window->setTitle("My Windows Game");
	
	engine->Start(new MyGame());

}