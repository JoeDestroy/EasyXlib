#pragma once

#include "window.h"

typedef struct {
    int RectX;
	int RectY;
	int RectWidth;
	int RectHeight;
} Rectangle;

void DrawRectangle(Win* win, Rectangle* rect);

void SetRectangleAttributes(Rectangle* rect, int X, int Y, int Width, int Height);

void SetColor(Win* win, int RGBhex);