#include <stdio.h>
#include <stdlib.h>

#include <X11/Xlib.h>
#include "include/window.h"

typedef struct {
    int RectX;
	int RectY;
	int RectWidth;
	int RectHeight;

    XColor color;
} Rectangle;
