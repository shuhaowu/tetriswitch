#include <stdio.h>
#include <stdarg.h>

#include <switch.h>

#include "draw.h"

static u32* framebuf;
static u32 stride;

#define FB_WIDTH 1280
#define FB_HEIGHT 720

static inline u32 idx(u32 x, u32 y) {
    return y * stride / sizeof(u32) + x;
}

void drawStart(u32* fb, u32 s) {
    framebuf = fb;
    stride = s;
}

void drawClearScreen(u32 color) {
    for (u32 y = 0; y < FB_HEIGHT; y++) {
        for (u32 x = 0; x < FB_WIDTH; x++){
            framebuf[idx(x, y)] = color;
        }
    }
}

void drawPixel(int x, int y, u32 color) {
    if (x >= 0 && x < FB_WIDTH && y >= 0 && y < FB_HEIGHT) {
        framebuf[idx(x, y)] = color;
    }
}

void drawLine(int x1, int y1, int x2, int y2, u32 color) {
    int x, y;
    if (x1 == x2) {
        for (y = y1; y <= y2; ++y) {
            drawPixel(x1, y, color);
        }
    } else {
        for (x = x1; x <= x2; ++x) {
            drawPixel(x, y1, color);
        }
    }
}

void drawRectangle(int x1, int y1, int x2, int y2, u32 color) {
    drawLine(x1, y1, x2, y1, color);
    drawLine(x2, y1, x2, y2, color);
    drawLine(x1, y2, x2, y2, color);
    drawLine(x1, y1, x1, y2, color);
}

void drawFillRect(int x1, int y1, int x2, int y2, u32 color) {
    int i, j;
    for (i = x1; i <= x2; ++i) {
        for (j = y1; j <= y2; ++j) {
            drawPixel(i, j, color);
        }
    }
}

void drawBitmap(int x, int y, Bitmap bmp) {
    int xx, yy;
    for (yy = y; yy < y + bmp.height; ++yy) {
        for (xx = x; xx < x + bmp.width; ++xx) {
            if (xx >= 0 && xx < FB_WIDTH && yy >= 0 && yy < FB_HEIGHT) {
                int pos = yy * FB_HEIGHT + xx;
                framebuf[idx(x, y)] = bmp.buf[pos];
            }
        }
    }
}

void drawText(const ffnt_header_t* font, int x, int y, u32 color, const char* str) {
    color_t clr;
    clr.abgr = color;
    DrawText(font, x, y, clr, str);
}

void drawTextFormat(const ffnt_header_t* font, int x, int y, u32 color, const char* str, ...) {
    char buffer[256];
    va_list valist;
    va_start(valist, str);
    vsnprintf(buffer, 255, str, valist);
    drawText(font, x, y, color, buffer);
    va_end(valist);
}
