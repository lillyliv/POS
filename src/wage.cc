// WAGE v0.1 2023 lili

#include <iostream>
#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <thread>

#include "defs.hh"
#include "render/render.cc"

#ifdef USE_X_SERVER // dont include files we dont need to possibly reduce binary sizes on some (unoptimized) compilers
    #include "render/x.cc"
#endif

#ifdef USE_WAYLAND
    #include "render/way.cc"
#endif

int main(int argc, char** argv) {

    #ifdef USE_X_SERVER
        
        std::thread renderThread(XINIT);
        // XINIT();
        // XLOOP();

        while (1) {
            // XNextEvent(d, &e);
        }

        // XCLOSE();
    #endif

    #ifdef USE_WAYLAND
        // please add code here
    #endif

    exit(0);
}
