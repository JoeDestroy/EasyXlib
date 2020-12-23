#include <stdio.h>
#include <stdlib.h>

#include <X11/Xlib.h>

#include "../include/window.h"
#include "../include/shapes.h"

typedef struct {
    int ButtonX;
    int ButtonY;
    int ButtonWidth;
    int ButtonHeight;

    int NormalColor;
    int TouchedColor;
} Button;

void AddButton(Win* win, Button button) {
    int mouseX, mouseY;
    GetRelativeCursorPosition(win, &mouseX, &mouseY);

    Rectangle rect;
    SetRectangleAttributes(&rect, button.ButtonX, button.ButtonY, button.ButtonWidth, button.ButtonHeight);

    int SelectW = button.ButtonX + button.ButtonWidth;
    int SelectH = button.ButtonY + button.ButtonHeight;
    int BX = button.ButtonX;
    int BY = button.ButtonY;

    if (mouseX >= BX && mouseX <= SelectW && mouseY >= BY && mouseY <= SelectH) {
        SetColor(win, 0x555555);
        DrawRectangle(win, &rect);
    } else {
        SetColor(win, 0x888888);
        DrawRectangle(win, &rect);
    }
}