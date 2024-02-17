#include <raylib.h>
#include <stdlib.h>

#include "paddle.h"

#define PADDLE_SPEED 5.0f

Paddle *create_paddle()
{
    return (Paddle *)malloc(sizeof(Paddle));
}

void move_paddle(Paddle *paddle, int SCREEN_HEIGHT)
{
    if (IsKeyDown(KEY_W))
        paddle->pos.y -= PADDLE_SPEED;
    if (IsKeyDown(KEY_S))
        paddle->pos.y += PADDLE_SPEED;

    if ((int)paddle->pos.y <= 0)
    {
        paddle->pos.y = 0.0f;
    }
    if ((int)paddle->pos.y >= SCREEN_HEIGHT-60)
    {
        paddle->pos.y = (float)SCREEN_HEIGHT-60;
    }
}

void draw_paddle(Paddle *paddle)
{
    DrawRectangleV(paddle->pos, paddle->size, RAYWHITE);
}