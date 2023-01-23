// WAGE renderer for X11

#pragma once
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <thread>
#include <chrono>

#include "../defs.hh"
#include "render.cc"

Display *d; // display
Window w;   // window
XEvent e;   // current event
GC gc;      // graphics context
int s;      // screen number

Colormap cmap;

SHAPE testShape;
XColor ClearColor;

void XCLOSE() {
    XCloseDisplay(d);
    XFreeGC(d, gc);
    exit(0);
}

void XRENDER_SHAPE(SHAPE shape) {
    if(shape.PRIM = PRIM_RECT) {
        XAllocColor(d, cmap, &shape.color);
        XSetForeground(d, gc, shape.color.pixel);
        XFillRectangle(d, w, gc, shape.x, shape.y, shape.w, shape.h);
    }
}

void XLOOP() {
    while (1) {
        // XNextEvent(d, &e);
        // if (e.type == Expose) {
            // XFillRectangle(d, w, gc, 20, 20, 10, 10);
            // XColor xcolour;

            // I guess XParseColor will work here
            // xcolour.red = 0x0; xcolour.green = 0xFFFF; xcolour.blue = 0x0;
            // xcolour.flags = DoRed | DoGreen | DoBlue;
            // XAllocColor(d, cmap, &xcolour);

            // XSetForeground(d, gc, xcolour.pixel);
            // XFillRectangle(d, w, gc, 0, 0, 30, 30);
            // XDrawString(d, w, DefaultGC(d, s), 10, 50, msg, strlen(msg));

            // XClearWindow(d, w);

            testShape.x++;
            XSetBackground(d, gc, BlackPixel(d, s));
            // XClearArea(d, w, 0, 0, 300, 300, True);
            XRENDER_SHAPE(testShape);
            std::this_thread::sleep_for (std::chrono::milliseconds(1000));

            // XSetForeground(d, gc, ClearColor.pixel);
            // XFillRectangle(d, w, gc, 0, 0, 500, 500);

            // XClearWindow(d, w);
        // }
        // if (e.type == KeyPress) {
        //     break;
        // }
    }
}


void XINIT() {
    ClearColor.red = 0xFFFF; ClearColor.green = 0xFFFF; ClearColor.blue = 0xFFFF;
    ClearColor.flags = DoRed | DoGreen | DoBlue;

    testShape.PRIM = PRIM_RECT;
    testShape.x = 50;
    testShape.y = 50;
    testShape.w = 100;
    testShape.h = 100;
    XColor tmpColor;
    tmpColor.red = 0xFFFF; tmpColor.green = 0x0; tmpColor.blue = 0x0;
    tmpColor.flags = DoRed | DoGreen | DoBlue;
    testShape.color = tmpColor;

    d = XOpenDisplay(NULL);
    if (d == NULL) {
        fprintf(stderr, "Could not connect to X11 Display!");
        exit(1);
    }

    s = DefaultScreen(d);
    w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, 500, 500, 1, BlackPixel(d, s), WhitePixel(d, s));
    XStoreName(d, w, WAGE_WINDOW_NAME); // window title

    // XSelectInput(d, w, ExposureMask | KeyPressMask);
    XSelectInput(d, w, 0);
    XMapWindow(d, w);

    gc = XCreateGC(d, w, 0, 0);
    XSetBackground(d, gc, BlackPixel(d, s));
	XSetForeground(d, gc, BlackPixel(d, s));

    cmap = DefaultColormap(d, s);
    XAllocColor(d, cmap, &ClearColor);

    XLOOP();
    XCLOSE();
}