#include <X11/Xlib.h>
#include <X11/Xft/Xft.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define WIDTH  400
#define HEIGHT 200

char input[64] = {0};
char output[128] = "Fahrenheit: ???";

void convert_and_update_output() {
    double c;
    if (sscanf(input, "%lf", &c) == 1) {
        double f = (c * 9.0 / 5.0) + 32.0;
        snprintf(output, sizeof(output), "Fahrenheit: %.2f °F", f);
    } else {
        snprintf(output, sizeof(output), "Invalid input");
    }
}

int main() {
    Display* dpy = XOpenDisplay(NULL);
    if (!dpy) {
        fprintf(stderr, "Failed to open display\n");
        return 1;
    }

    int screen = DefaultScreen(dpy);
    Window root = RootWindow(dpy, screen);
    Window win = XCreateSimpleWindow(dpy, root, 100, 100, WIDTH, HEIGHT, 1,
                                     BlackPixel(dpy, screen), WhitePixel(dpy, screen));
    XSelectInput(dpy, win, ExposureMask | KeyPressMask);
    XMapWindow(dpy, win);

    XftFont* font = XftFontOpenName(dpy, screen, "Monospace-16");
    XRenderColor xr = {0, 0, 0, 65535};
    XftColor xft_color;
    XftColorAllocValue(dpy, DefaultVisual(dpy, screen),
                       DefaultColormap(dpy, screen), &xr, &xft_color);
    
    XftDraw* draw = NULL;

    XEvent e;
    while (1) {
        XNextEvent(dpy, &e);
        if (e.type == Expose) {
            if (!draw)
                draw = XftDrawCreate(dpy, win, DefaultVisual(dpy, screen),
                                     DefaultColormap(dpy, screen));
            XClearWindow(dpy, win);
            XftDrawStringUtf8(draw, &xft_color, font, 20, 60,
                              (XftChar8*)"Enter Celsius:", strlen("Enter Celsius:"));
            XftDrawStringUtf8(draw, &xft_color, font, 170, 60,
                              (XftChar8*)input, strlen(input));
            XftDrawStringUtf8(draw, &xft_color, font, 20, 120,
                              (XftChar8*)output, strlen(output));
        } else if (e.type == KeyPress) {
            char buf[32];
            KeySym keysym;
            int len = XLookupString(&e.xkey, buf, sizeof(buf) - 1, &keysym, NULL);
            buf[len] = '\0';

            if (keysym == XK_Return) {
                convert_and_update_output();
            } else if (keysym == XK_BackSpace) {
                size_t l = strlen(input);
                if (l > 0) input[l - 1] = '\0';
            } else if (isprint(buf[0]) && strlen(input) < sizeof(input) - 1) {
                strncat(input, buf, 1);
            }

            XClearWindow(dpy, win);
            XExposeEvent expose = {Expose, 0, True, win, 0, 0, WIDTH, HEIGHT, 0};
            XSendEvent(dpy, win, False, ExposureMask, (XEvent*)&expose);
            XFlush(dpy);
        }
    }

    if (draw) XftDrawDestroy(draw);
    XftFontClose(dpy, font);
    XCloseDisplay(dpy);
    return 0;
}
