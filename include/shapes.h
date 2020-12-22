#pragma once

#include "window.h"

typedef struct {
	int red;
	int green;
	int blue;
} RGB;

typedef struct {
    int RectX;
	int RectY;
	int RectWidth;
	int RectHeight;
} Rectangle;

RGB Hex2Rgb(int HexValue);

void DrawRectangle(Win* win, Rectangle* rect);

void SetRectangleAttributes(Rectangle* rect, int X, int Y, int Width, int Height);

void SetColor(Win* win, int RGBhex);