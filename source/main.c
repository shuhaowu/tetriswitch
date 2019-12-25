#include <stdio.h>
#include <switch.h>

#include "tetris.h"

#define FB_WIDTH  1280
#define FB_HEIGHT 720

int running = 1;

int main() {
    tetrisInit();

    // Retrieve the default window
    NWindow* win = nwindowGetDefault();

    // Create a linear double-buffered framebuffer
    Framebuffer fb;
    framebufferCreate(&fb, win, FB_WIDTH, FB_HEIGHT, PIXEL_FORMAT_RGBA_8888, 2);
    framebufferMakeLinear(&fb);

    char buf[100];

    while(appletMainLoop() && running) {
        hidScanInput();
        update();

        // Retrieve the framebuffer
        u32 stride;
        u32* framebuf = (u32*) framebufferBegin(&fb, &stride);

        snprintf(buf, 100, "stride: %u %lu", stride, sizeof(u32));
        logg(buf);

        render(framebuf, stride);

        // We're done rendering, so we end the frame here.
        framebufferEnd(&fb);
    }

    framebufferClose(&fb);
    return 0;
}
