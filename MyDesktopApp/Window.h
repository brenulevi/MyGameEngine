/********************************************************************************
*
* File:				Window.h
* Project:			Game Engine
* Author:			Breno Soares Alves
* Creation Date:	04-16-2023
*
* Subject:			A class to manipulate and create the Windows window.
********************************************************************************/

#ifndef WINDOW_H_
#define WINDOW_H_

// ---------------------------------------------------------------------------------

#include <Windows.h>
#include <windowsx.h>
#include <string>

// ---------------------------------------------------------------------------------
// Global Constants and	Enumerators

enum WindowModes {FULLSCREEN, WINDOWED};

// ---------------------------------------------------------------------------------

class Window
{
private:
	HINSTANCE hInstance;				// Application Identifier
	HWND handleWindow;					// Window Identifier
	int windowWidth;					// Window Width
	int windowHeight;					// Window Height
	HICON windowIcon;					// Window Icon
	HCURSOR windowCursor;				// Window Cursor
	COLORREF windowBackgroundColor;		// Window Background Color
	std::string windowTitle;			// Window Title
	DWORD windowStyle;                  // Window Style 
	int windowMode;						// Window Mode (Fullscreen or Windowed)
	int windowPosX;						// Window Position X
	int windowPosY;						// Window Position Y
	float windowCenterX;				// Window Center X 
	float windowCenterY;				// Window Center Y

	static bool windowKeyStates[256];	// Keyboard keys state
	static int windowMouseX;			// Mouse Position X in the window
	static int windowMouseY;			// Mouse Position Y in the window

public:
	Window();							// Constructor

	// Getters
	HINSTANCE		getAppId();						// Return the application id
	HWND			getWindowId();					// Return the window id

	int				getWindowWidth();				// Return the window width
	int				getWindowHeight();				// Return the window height

	COLORREF		getWindowBackgroundColor();		// Returns the background color
	std::string		getWindowTitle();				// Return the window title
	int				getWindowMode();				// Return the window mode
	
	float			getCenterX();					// Return the window center in X axis
	float			getCenterY();					// Return the window center in Y axis

	bool			KeyUp(int);						// Return true if the key is released
	bool			KeyDown(int);					// Return true if the key is pressed
	int				MouseX();						// Return the mouse position in X axis
	int				MouseY();						// Return the mouse position in Y axis

	// Setters
	void setSize(int, int);						// Set window size
	void setBackgroundColor(int, int, int);		// Set window background color
	void setTitle(const std::string);			// Set window title
	void setCursor(const unsigned int);			// Set window cursor
	void setIcon(const unsigned int);			// Set window icon
	void setMode(int);							// Set window mode

	bool Create();								// Creates the window with the attributes values
	void Close();								// Close the window

	void Print(std::string text, int x, int y, COLORREF color);

	// WinProcedure
	static LRESULT CALLBACK WinProc(HWND, UINT, WPARAM, LPARAM);
};

// ---------------------------------------------------------------------------------

// Inline methods

// Get application id
inline HINSTANCE Window::getAppId() { return hInstance; }

// Get window id
inline HWND Window::getWindowId() { return handleWindow; }

// Get window width
inline int Window::getWindowWidth() { return windowWidth; }

// Get window height
inline int Window::getWindowHeight() { return windowHeight; }

// Get window background color
inline COLORREF Window::getWindowBackgroundColor() { return windowBackgroundColor; }

// Get window title
inline std::string Window::getWindowTitle() { return windowTitle; }

// Get window mode (FULLSCREEN/WINDOWED)
inline int Window::getWindowMode() { return windowMode; }

// Get center position in X axis
inline float Window::getCenterX() { return windowCenterX; }

// Get cecnter position in Y axis
inline float Window::getCenterY() { return windowCenterY; }

// Verify if a key is pressed
inline bool Window::KeyDown(int key) { return windowKeyStates[key]; }

// Verify if a key is released
inline bool Window::KeyUp(int key) { return !(windowKeyStates[key]); }

// Get mouse position in X axis
inline int Window::MouseX() { return windowMouseX; }

// Get mouse position in Y axis 
inline int Window::MouseY() { return windowMouseY; }

// Set window background color
inline void Window::setBackgroundColor(int r, int g, int b) { windowBackgroundColor = RGB(r, g, b); }

// Set window title
inline void Window::setTitle(const std::string title) { windowTitle = title; }

// Set window cursor
inline void Window::setCursor(const unsigned int cursor) { windowCursor = LoadCursor(GetModuleHandle(NULL), MAKEINTRESOURCE(cursor)); }

// Set window icon
inline void Window::setIcon(const unsigned int icon) { windowIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(icon)); }

// Close window
inline void Window::Close() { PostMessage(handleWindow, WM_DESTROY, 0, 0); }

#endif
