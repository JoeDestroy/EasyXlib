#include <stdio.h>
#include <stdlib.h>

#include <X11/keysym.h>
#include <X11/Xlib.h>

#include "include/shapes.h"
#include "include/window.h"

void Draw(Win* win) {
    Rectangle rect;
    rect.RectHeight = 250;
    rect.RectWidth = 150;
    rect.RectX = 10;
    rect.RectY = 10;

    int mouseX;
    int mouseY;

    XFillRectangle(win->display, win->window, DefaultGC(win->display, win->screen), rect.RectX, rect.RectY, rect.RectWidth, rect.RectHeight);
}

int main() {
    Rectangle rect;
    Win win;

    rect.RectHeight = 50;
    rect.RectWidth =  100;
    rect.RectX =      50;
    rect.RectY =      50;

    int mouseX, mouseY;

    SetWinAttributes(&win, 10, 10, 1920, 1080);

    CreateWindow(&win);
    
    SetExitKey(&win, XK_Escape);

    while (1)
    {
        XNextEvent(win.display, &win.event);

        OnExpose(&win, Draw);

        if (win.event.type == KeyPress) {
            KeySym     keysym;
            XKeyEvent *kevent;
            char       buffer[1];
            
            kevent = (XKeyEvent *) &win.event;
            if (   (XLookupString((XKeyEvent *)&win.event,buffer,1,&keysym,NULL) == 1) && (keysym == (KeySym)win.ExitKey) ) {
                    DestroyWindow(&win);
                    exit(0);
            }
        }

        GetRelativeCursorPosition(&win, &mouseX, &mouseY);
        printf("X %d, Y %d\n", mouseX, mouseY);
    }
}