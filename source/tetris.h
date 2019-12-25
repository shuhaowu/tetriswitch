#ifndef TETRIS_H
#define TETRIS_H

#include <switch.h>

void tetrisInit();

void update();
void render(u32* framebuf, u32 stride);
void logg(const char*);

extern int running;

#endif /* TETRIS_H */