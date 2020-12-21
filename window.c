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
        Colormap cmap;

        int ExitKey;
} Win;


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
        XSelectInput(win->display, win->window, ExposureMask | KeyPressMask | PointerMotionMask);

        /* display the window */
        XMapWindow(win->display, win->window);

        return 0;
}
