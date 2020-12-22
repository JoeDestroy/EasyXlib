#include <stdio.h>
#include <stdlib.h>

#include <X11/keysym.h>
#include <X11/Xlib.h>

#include "include/shapes.h"
#include "include/window.h"

void Draw(Win* win) {
    Rectangle rect;
    SetRectangleAttributes(&rect, 20, 20, 50, 50);

    int mouseX;
    int mouseY;
    GetRelativeCursorPosition(win, &mouseX, &mouseY);

    SetColor(win, 0x888888);

    DrawRectangle(win, &rect);
}

int main() {
    Win win;

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