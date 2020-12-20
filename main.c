#include <stdio.h>
#include <stdlib.h>

#include <X11/keysym.h>
#include <X11/Xlib.h>
#include "include/window.h"


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

    while (1) {
                XNextEvent(win.display, &win.event);
                

                switch (win.event.type) {
                        case KeyPress: {
                                KeySym     keysym;
                                XKeyEvent *kevent;
                                char       buffer[1];
                                /* It is necessary to convert the keycode to a
                                * keysym before checking if it is an escape */
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
        }
}