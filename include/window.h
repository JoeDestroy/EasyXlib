#pragma once
#include <X11/Xlib.h>

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
        GC gc;
        Colormap cmap;
        Atom DeleteWindow;

        int ExitKey;
} Win;


void OnExpose(Win* win, void(*f)());

void SetExitKey(Win* win, int KeyHex);

void DestroyWindow(Win* win);

int CheckIfUserExit(Win* win);

void CreateGC(Win* win);

int CompareKeys(Win* win, int Key);

int CreateWindow(Win* win);

void SetWinAttributes(Win* win, int WindowX, int WindowY, int WindowWidth, int WindowHeight);