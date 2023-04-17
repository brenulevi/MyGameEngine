/*
*
* File:				Window.h
* Project:			Game Engine
* Author:			Breno Soares Alves
* Creation Date:	04-16-2023
*
* Subject:			A class to manipulate and create the Windows window.
*/

#ifndef WINDOW_H_
#define WINDOW_H_

// ---------------------------------------------------------------------------------

#include <Windows.h>
#include <windowsx.h>
#include <string>

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

	void Create();								// Creates the window with the attributes values
	void Close();								// Close the window

	// WinProcedure
	static LRESULT CALLBACK WinProc(HWND, UINT, WPARAM, LPARAM);
};

// ---------------------------------------------------------------------------------

// Inline methods


#endif
