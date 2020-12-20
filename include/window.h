#include <X11/Xlib.h>
#pragma once

typedef struct WinStruct{
        // Window Attributes
        int WinX;
        int WinY;
        int WinWidth;
        int WinHeight;
        int WinBorder;

        // Variables for window
        Display *display;
        Window window;
        XEvent event;
        int screen;

        int ExitKey;
} Win;

typedef struct {
	int RectX;
	int RectY;
	int RectWidth;
	int RectHeight;
} DrawRectangle;

void SetExitKey(Win* win, int KeyHex);

void DestroyWindow(Win* win);

int CreateWindow(Win* win);

void SetWinAttributes(Win* win, int WindowX, int WindowY, int WindowWidth, int WindowHeight);