#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <windowsx.h>

int windowWidth = 1366;
int windowHeight = 768;
bool fullscreen = true;

bool vkKeys[256] = { false };
HWND hwnd;
HDC hdc;

LRESULT CALLBACK WinProc(HWND, UINT, WPARAM, LPARAM);

void GameInit()
{
	hdc = GetDC(hwnd);
}

void GameUpdate()
{
	if (vkKeys[VK_ESCAPE])
		PostMessage(hwnd, WM_DESTROY, 0, 0);
}

void GameDraw()
{
}

void GameFinalize()
{
	ReleaseDC(hwnd, hdc);
}

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ PSTR lpCmdLine, _In_ int nCmdShow) 
{
	MSG msg;
	WNDCLASS myWndClass = {};

	// Create wndClass
	myWndClass.hInstance = hInstance;
	myWndClass.lpfnWndProc = WinProc;
	myWndClass.style = CS_HREDRAW | CS_VREDRAW;
	myWndClass.hbrBackground = (HBRUSH) GetStockObject(BLACK_BRUSH);
	myWndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	myWndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	myWndClass.lpszClassName = "GameWindow";

	// Register wndClass
	RegisterClass(&myWndClass);

	int windowStyle = WS_OVERLAPPED | WS_SYSMENU;

	if (fullscreen)
	{
		windowWidth = GetSystemMetrics(SM_CXSCREEN);
		windowHeight = GetSystemMetrics(SM_CYSCREEN);
		windowStyle = WS_POPUP;
	}

	// Create window
	hwnd = CreateWindowEx(
		NULL,
		"GameWindow",
		"My Window",
		windowStyle,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		windowWidth,
		windowHeight,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (!fullscreen)
	{
		RECT clientRect = { 0, 0, windowWidth, windowHeight };
		AdjustWindowRectEx(
			&clientRect,
			GetWindowStyle(hwnd),
			GetMenu(hwnd) != NULL,
			GetWindowExStyle(hwnd)
		);

		int windowPosX = (GetSystemMetrics(SM_CXSCREEN) / 2) - ((clientRect.right - clientRect.left) / 2);
		int windowPosY = (GetSystemMetrics(SM_CYSCREEN) / 2) - ((clientRect.bottom - clientRect.top) / 2);

		MoveWindow(
			hwnd,
			windowPosX,
			windowPosY,
			clientRect.right - clientRect.left,
			clientRect.bottom - clientRect.top,
			TRUE
		);
	}
	
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	GameInit();

	do {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		} else {
			GameUpdate();
			GameDraw();
		}

	} while (msg.message != WM_QUIT);

	GameFinalize();

	return int(msg.wParam);
}

LRESULT CALLBACK WinProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_KEYDOWN:
		vkKeys[wParam] = true;
		return 0;

	case WM_KEYUP:
		vkKeys[wParam] = false;
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}