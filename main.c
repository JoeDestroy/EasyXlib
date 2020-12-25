#include <stdio.h>
#include <stdlib.h>

#include <X11/X.h>
#include <X11/keysym.h>
#include <X11/Xlib.h>

#include "include/utils.h"
#include "include/shapes.h"
#include "include/window.h"
#include "include/button.h"


void Draw(Win* win, Rectangle rect) {
    int mouseX;
    int mouseY;
    GetRelativeCursorPosition(win, &mouseX, &mouseY);

    if(mouseX < 100 && mouseY < 100) {
        SetColor(win, 0x888888);

        DrawRectangle(win, &rect);
    } else {
        SetColor(win, 0xBBBBBB);

        DrawRectangle(win, &rect);
    }
}

int main() {
    Win win;
    Button button;
    button.ButtonX = 20;
    button.ButtonY = 20;
    button.ButtonWidth = 100;
    button.ButtonHeight = 100;

    Button button2;
    button2.ButtonX = 200;
    button2.ButtonY = 200;
    button2.ButtonWidth = 300;
    button2.ButtonHeight = 100;

    Rectangle rect;
    SetRectangleAttributes(&rect, 0, 500, 500, 250);

    Rectangle rect2;
    SetRectangleAttributes(&rect2, 600, 500, 500, 250);

    int mouseX, mouseY;

    SetWinAttributes(&win, 10, 10, 1920, 1080);

    CreateWindow(&win);

    CreateGC(&win);
    
    SetExitKey(&win, XK_Escape);

    while (1)
    {
        XNextEvent(win.display, &win.event);

        if (EventType(&win, Expose) || EventType(&win, MotionNotify)) {
            AddButton(&win, button);
            AddButton(&win, button2);
            SetColor(&win, 0xFF0000);
            DrawRectangle(&win, &rect);
            SetColor(&win, 0x00FF00);
            DrawRectangle(&win, &rect2);
        }

        if (EventType(&win, KeyPress)) {
            if (CompareKeys(&win, win.ExitKey)) {
                DestroyWindow(&win);
                exit(0);
            }
        }

        CheckIfUserExit(&win);
    }
}