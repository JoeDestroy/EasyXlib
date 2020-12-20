#include <stdio.h>
#include <stdlib.h>

#include <X11/keysym.h>
#include <X11/Xlib.h>
#include "include/window.h"

void Draw(Win* win) {
    DrawRectangle rect;
    rect.RectHeight = 250;
    rect.RectWidth = 150;
    rect.RectX = 10;
    rect.RectY = 10;

    XFillRectangle(win->display, win->window, DefaultGC(win->display, win->screen), rect.RectX, rect.RectY, rect.RectWidth, rect.RectHeight);
}

void Draw2(Win* win) {
    DrawRectangle rect;
    rect.RectHeight = 150;
    rect.RectWidth = 250;
    rect.RectX = 500;
    rect.RectY = 500;
    
    XFillRectangle(win->display, win->window, DefaultGC(win->display, win->screen), rect.RectX, rect.RectY, rect.RectWidth, rect.RectHeight);
}

int main() {
    DrawRectangle rect;
    Win win;

    rect.RectHeight = 50;
    rect.RectWidth =  100;
    rect.RectX =      50;
    rect.RectY =      50;

    SetWinAttributes(&win, 10, 10, 600, 300);

    CreateWindow(&win);
    
    SetExitKey(&win, XK_e);

    while (1)
    {
        XNextEvent(win.display, &win.event);

        OnExpose(&win, Draw);

        OnExpose(&win, Draw2);

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
    }
    

    /*while (1) {
                XNextEvent(win.display, &win.event);
                

                switch (win.event.type) {
                        case KeyPress: {
                                KeySym     keysym;
                                XKeyEvent *kevent;
                                char       buffer[1];
                                
                                kevent = (XKeyEvent *) &win.event;
                                if (   (XLookupString((XKeyEvent *)&win.event,buffer,1,&keysym,NULL) == 1) && (keysym == (KeySym)win.ExitKey) )
                                        DestroyWindow(&win);
                                        exit(0);
                                
                                break;
                        }
			            case LeaveNotify:
                        	    XDestroyWindow(win.display, win.window);
				                XCloseDisplay(win.display);

                        case Expose:
                                XFillRectangle(win.display, win.window, DefaultGC(win.display, win.screen), rect.RectX, rect.RectY, rect.RectWidth, rect.RectHeight);
                }
    }*/
}