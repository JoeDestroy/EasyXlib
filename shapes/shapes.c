#include <stdio.h>
#include <stdlib.h>

#include <X11/Xlib.h>
#include "../include/window.h"
#include "../include/utils.h"

typedef struct {
    int RectX;
	int RectY;
	int RectWidth;
	int RectHeight;
} Rectangle;

typedef struct {

} Triangle;


void DrawRectangle(Win* win, Rectangle* rect) {
	XFillRectangle(win->display, win->window, win->gc, rect->RectX, rect->RectY, rect->RectWidth, rect->RectHeight);
}

void SetRectangleAttributes(Rectangle* rect, int X, int Y, int Width, int Height) {
	rect->RectX = X;
	rect->RectY = Y;
	rect->RectWidth = Width;
	rect->RectHeight = Height;
}

void SetColor(Win* win, int RGBhex) {
	Colormap ScreenColormap = DefaultColormap(win->display, DefaultScreen(win->display));

    Visual* Default_Visual = DefaultVisual(win->display, DefaultScreen(win->display));

    Colormap MyColormap = XCreateColormap(
        win->display, 
        win->window,
        Default_Visual, 
        AllocNone
    );

    XColor SystemColor2;
    XColor ExactColor;

	RGB NewColor = Hex2Rgb(RGBhex);

    SystemColor2.red = NewColor.red;
    SystemColor2.green = NewColor.green;
    SystemColor2.blue = NewColor.blue;

    Status xc = XAllocColor(
        win->display,
        ScreenColormap,
        &SystemColor2
    );

    XSetForeground(win->display, win->gc, SystemColor2.pixel);
}