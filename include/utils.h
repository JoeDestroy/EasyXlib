#pragma once
#include "window.h"

typedef struct {
	int red;
	int green;
	int blue;
} RGB;

int CompareKeys(Win* win, int Key);

void GetRelativeCursorPosition(Win* win, int* xPos, int* yPos);

void GetCursorPosition(Win* win, int* xPos, int* yPos);

RGB Hex2Rgb(int HexValue);