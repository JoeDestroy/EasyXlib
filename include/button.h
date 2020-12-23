#pragma once
#include "window.h"

typedef struct {
    int ButtonX;
    int ButtonY;
    int ButtonWidth;
    int ButtonHeight;

    int NormalColor;
    int TouchedColor;
} Button;

void AddButton(Win* win, Button button);