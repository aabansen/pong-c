#pragma once
#include <raylib.h>

#ifndef _PADDLE_H_
#define _PADDLE_H_

typedef struct {
    Vector2 pos;
    Vector2 size;
} Paddle;

Paddle *create_paddle();
void move_paddle(Paddle *paddle, int SCREEN_HEIGHT);
void draw_paddle(Paddle *paddle);

#endif