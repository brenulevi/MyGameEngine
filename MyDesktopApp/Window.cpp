/********************************************************************************
*
* File:				Window.cpp
* Project:			Game Engine
* Author:			Breno Soares Alves
* Creation Date:	04-17-2023
*
* Subject:			A class to manipulate and create the Windows window.
********************************************************************************/

#include "Window.h"

//-----------------------------------------------------------------------------------
// Static attributes initialization

bool Window::windowKeyStates[256] = { 0 };
int Window::windowMouseX = 0;
int Window::windowMouseY = 0;

//-----------------------------------------------------------------------------------
// Constructor

Window::Window()
{
	hInstance = GetModuleHandle(NULL);
	handleWindow = 0;
	windowWidth = GetSystemMetrics(SM_CXSCREEN);
	windowHeight = GetSystemMetrics(SM_CYSCREEN);
	windowIcon = LoadIcon(NULL, IDI_APPLICATION);
	windowCursor = LoadCursor(NULL, IDC_ARROW);
	windowBackgroundColor = RGB(0, 0, 0);
	windowTitle = std::string("Windows Game");
	windowStyle = WS_POPUP | WS_VISIBLE;
	windowMode = FULLSCREEN;
	windowPosX = 0;
	windowPosY = 0;
	windowCenterX = windowWidth / 2.0f;
	windowCenterY = windowHeight / 2.0f;
}

// ---------------------------------------------------------------------------------

void Window::setMode(int mode)
{
	windowMode = mode;

	if (mode == WINDOWED)
		windowStyle = WS_OVERLAPPED | WS_SYSMENU | WS_VISIBLE;
	else
		windowStyle = WS_POPUP | WS_EX_TOPMOST | WS_VISIBLE;
}

// --------------------------------------------------------------------------

void Window::setSize(int width, int height)
{
	windowWidth = width;
	windowHeight = height;

	windowCenterX = windowWidth / 2.0f;
	windowCenterY = windowHeight / 2.0f;

	windowPosX = GetSystemMetrics(SM_CXSCREEN) / 2 - windowWidth / 2;
	windowPosY = GetSystemMetrics(SM_CYSCREEN) / 2 - windowHeight / 2;

}

// ---------------------------------------------------------------------------------

void Window::Print(std::string text, int x, int y, COLORREF color)
{
	HDC xdc = GetDC(handleWindow);

	SetTextColor(xdc, color);

	SetBkMode(xdc, TRANSPARENT);

	TextOut(xdc, x, y, text.c_str(), int(text.size()));

	ReleaseDC(handleWindow, xdc);
}

// ---------------------------------------------------------------------------------


bool Window::Create()
{
	// Creating window class
	WNDCLASSEX wndClass;

	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInstance;
	wndClass.lpfnWndProc = Window::WinProc;
	wndClass.style = CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	wndClass.hbrBackground = (HBRUSH) CreateSolidBrush(windowBackgroundColor);
	wndClass.hCursor = windowCursor;
	wndClass.hIcon = windowIcon;
	wndClass.lpszClassName = "GameWindow";
	wndClass.lpszMenuName = NULL;
	wndClass.hIconSm = windowIcon;

	// Registering window class
	if (!RegisterClassEx(&wndClass))
		return false;

	// Creating window
	handleWindow = CreateWindowEx(
		NULL,
		"GameWindow",
		windowTitle.c_str(),
		windowStyle,
		windowPosX,
		windowPosY,
		windowWidth,
		windowHeight,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	// Adjust client area size
	if (windowMode == WINDOWED)
	{
		RECT winRect = { 0, 0, windowWidth, windowHeight };

		AdjustWindowRectEx(
			&winRect,
			GetWindowStyle(handleWindow),
			GetMenu(handleWindow) != NULL,
			GetWindowExStyle(handleWindow)
		);

		windowPosX = (GetSystemMetrics(SM_CXSCREEN) / 2) - (winRect.right - winRect.left) / 2;
		windowPosY = (GetSystemMetrics(SM_CYSCREEN) / 2) - (winRect.bottom - winRect.top) / 2;

		MoveWindow(
			handleWindow,
			windowPosX,
			windowPosY,
			winRect.right - winRect.left,
			winRect.bottom - winRect.top,
			TRUE
		);
	}

	return (handleWindow ? true : false);
}

// ---------------------------------------------------------------------------------

LRESULT CALLBACK Window::WinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_KEYDOWN:
		windowKeyStates[wParam] = true;
		return 0;

	case WM_KEYUP:
		windowKeyStates[wParam] = false;
		return 0;

	case WM_MOUSEMOVE:
		windowMouseX = GET_X_LPARAM(lParam);
		windowMouseY = GET_Y_LPARAM(lParam);
		return 0;

	case WM_LBUTTONDOWN:
	case WM_LBUTTONDBLCLK:
		windowKeyStates[VK_LBUTTON] = true;
		return 0;

	case WM_MBUTTONDOWN:
	case WM_MBUTTONDBLCLK:
		windowKeyStates[VK_MBUTTON] = true;
		return 0;

	case WM_RBUTTONDOWN:
	case WM_RBUTTONDBLCLK:
		windowKeyStates[VK_RBUTTON] = true;
		return 0;

	case WM_LBUTTONUP:
		windowKeyStates[VK_LBUTTON] = false;
		return 0;

	case WM_MBUTTONUP:
		windowKeyStates[VK_MBUTTON] = false;
		return 0;

	case WM_RBUTTONUP:
		windowKeyStates[VK_RBUTTON] = false;
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

// ---------------------------------------------------------------------------------