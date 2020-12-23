#include <stdio.h>
#include <stdlib.h>

#include <X11/keysym.h>
#include <X11/Xlib.h>

#include "include/shapes.h"
#include "include/window.h"
#include "include/button.h"

void Draw(Win* win, Rectangle rect) {
    //SetRectangleAttributes(&rect, 0, 0, 100, 100);

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

    int mouseX, mouseY;

    SetWinAttributes(&win, 10, 10, 1920, 1080);

    CreateWindow(&win);

    CreateGC(&win);
    
    SetExitKey(&win, XK_Escape);

    XSync(win.display, False);

    while (1)
    {
        XNextEvent(win.display, &win.event);

        OnExpose(&win, Draw);

        if (win.event.type == KeyPress) {
            if (CompareKeys(&win, win.ExitKey)) {
                DestroyWindow(&win);
                exit(0);
            }
        }

        AddButton(&win, button);
    }
}