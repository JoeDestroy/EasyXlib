#include <stdio.h>
#include <stdlib.h>

#include <X11/keysym.h>
#include <X11/Xlib.h>


typedef struct WinStruct{
        // Window Attributes
        int WinX;
        int WinY;
        int WinWidth;
        int WinHeight;
        int WinBorder;

        // Variables for window
        Display *display;
        Window window;
        XEvent event;
        int screen;
        GC gc;

        int ExitKey;
} Win;

typedef struct {
	int RectX;
	int RectY;
	int RectWidth;
	int RectHeight;
} DrawRectangle;

void OnExpose(Win* win, void(*f)(Win* win)) {

        if (win->event.type == Expose) {
                //XFillRectangle(win->display, win->window, DefaultGC(win->display, win->screen), rect.RectX, rect.RectY, rect.RectWidth, rect.RectHeight);
                f(win);
        }
}

// Function to set attributes of a X11 window
void SetWinAttributes(Win* win, int WindowX, int WindowY, int WindowWidth, int WindowHeight) {
        win->WinX = WindowX;
        win->WinY = WindowY;
        win->WinWidth = WindowWidth;
        win->WinHeight = WindowHeight;
        win->WinBorder = 1;
}

// TODO: Fix segmentation fault caused by this function
void GetCursorPosition(Win* win, int* xPos, int* yPos) {
        Window windowReturned;
        int rootX, rootY;
        int winX, winY;
        unsigned int maskReturn;
        Bool result;

        result = XQueryPointer(win->display, win->window, &windowReturned, &windowReturned, &rootX, &rootY, &winX, &winY, &maskReturn);

        *xPos = rootX;
        *yPos = rootY;
}

// Set the key which, when pressed closes the program
void SetExitKey(Win* win, int KeyHex) {
        win->ExitKey = KeyHex;
}

// Self-Explanatory, DESTROY window
void DestroyWindow(Win* win) {
        XDestroyWindow(win->display, win->window);
        XCloseDisplay(win->display);
}

// Create a X11 window
int CreateWindow(Win* win) {
	DrawRectangle rect;

	rect.RectX = 20;
	rect.RectY = 20;
	rect.RectWidth = 500;
	rect.RectHeight = 500;

        /* open connection with the server */
        win->display = XOpenDisplay(NULL);
        if (win->display == NULL) {
                fprintf(stderr, "Cannot open display\n");
                exit(1);
        }

        win->screen = DefaultScreen(win->display);

        /* create window */
        win->window = XCreateSimpleWindow(win->display, RootWindow(win->display, win->screen), win->WinX, win->WinY, win->WinWidth, win->WinHeight,
                win->WinBorder, BlackPixel(win->display, win->screen), WhitePixel(win->display, win->screen));

        /* process window close event through event handler so XNextEvent does not fail */
        Atom del_window = XInternAtom(win->display, "WM_DELETE_WINDOW", 0);
        XSetWMProtocols(win->display, win->window, &del_window, 1);

        /* select kind of events we are interested in */
        XSelectInput(win->display, win->window, ExposureMask | KeyPressMask);

        /* display the window */
        XMapWindow(win->display, win->window);

        /* event loop */
        //while (1) {
        //XNextEvent(win->display, &win->event);
                

                /*switch (win->event.type) {
                        case KeyPress: {
                                KeySym     keysym;
                                XKeyEvent *kevent;
                                char       buffer[1];
                                
                                kevent = (XKeyEvent *) &win->event;
                                if (   (XLookupString((XKeyEvent *)&win->event,buffer,1,&keysym,NULL) == 1) && (keysym == (KeySym)XK_A) )
                                        exit(0);
                                        break;
                        }
			case LeaveNotify:
                        	XDestroyWindow(win->display, win->window);
				XCloseDisplay(win->display);

                        case Expose:
                                XFillRectangle(win->display, win->window, DefaultGC(win->display, win->screen), rect.RectX, rect.RectY, rect.RectWidth, rect.RectHeight);
                }
        }*/

        return 0;
}
