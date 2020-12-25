#include <stdio.h>
#include <stdlib.h>

#include <X11/Xutil.h>
#include <X11/keysym.h>
#include <X11/Xlib.h>

#include "include/window.h"
#include "include/shapes.h"


typedef struct {
	int red;
	int green;
	int blue;
} RGB;


int CompareKeys(Win* win, int Key) {
        if (win->event.type == KeyPress) {
            KeySym     keysym;
            XKeyEvent *kevent;
            char       buffer[1];
            
            kevent = (XKeyEvent *) &win->event;
            if (   (XLookupString((XKeyEvent *)&win->event,buffer,1,&keysym,NULL) == 1) && (keysym == (KeySym)win->ExitKey) ) 
                return 1;
            
            return 0;
        }
}

// Return the mouse position relative to the window position
void GetRelativeCursorPosition(Win* win, int* xPos, int* yPos){
        Window windowReturned;
        int rootX, rootY;
        int winX, winY;
        unsigned int maskReturn;
        Bool result;

        if (win->event.type == MotionNotify) {
                result = XQueryPointer(win->display, win->window, &windowReturned, &windowReturned, &rootX, &rootY, &winX, &winY, &maskReturn);
                *xPos = winX;
                *yPos = winY;
        }
}

// Return the mouse position on screen
void GetCursorPosition(Win* win, int* xPos, int* yPos){
        Window windowReturned;
        int rootX, rootY;
        int winX, winY;
        unsigned int maskReturn;
        Bool result;

        if (win->event.type == MotionNotify) {
                result = XQueryPointer(win->display, win->window, &windowReturned, &windowReturned, &rootX, &rootY, &winX, &winY, &maskReturn);
                *xPos = rootX;
                *yPos = rootY;
        }
}

RGB Hex2Rgb(int HexValue) {
	RGB ReturnColor;
    
	ReturnColor.red = ((HexValue >> 16) & 0xFF) / 255.0 * 65535.0;
	ReturnColor.green = ((HexValue >> 8) & 0xFF) / 255.0 * 65535.0;
	ReturnColor.blue = ((HexValue) & 0xFF) / 255.0  * 65535.0;
	
	return ReturnColor;
}