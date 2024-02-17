#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include <math.h>

#include "paddle.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 450
#define BALL_RADIUS 10

float xspeed = 5.0f;
float yspeed = 5.0f;

int player_score = 0, cpu_score = 0;

int paddle_ball_collide(Paddle *paddle, Vector2 ball_pos)
{
    float testX = ball_pos.x;
    float testY = ball_pos.y;

    // get closest edge
    if (ball_pos.x < paddle->pos.x)
        testX = paddle->pos.x; // left edge
    else if (ball_pos.x > paddle->pos.x + paddle->size.x)
        testX = paddle->pos.x + paddle->size.x; // right edge
    if (ball_pos.y < paddle->pos.y)
        testY = paddle->pos.y; // top edge
    else if (ball_pos.y > paddle->pos.y + paddle->size.y)
        testY = paddle->pos.y + paddle->size.y; // bottom edge

    float distX = ball_pos.x - testX;
    float distY = ball_pos.y - testY;
    float distance = sqrt((distX * distX) + (distY * distY));

    if (distance <= BALL_RADIUS) {
        return 1;
    }

    return 0;
}

void reset_ball_pos(Vector2 *ball_pos)
{
    ball_pos->x = (float)SCREEN_WIDTH / 2;
    ball_pos->y = (float)SCREEN_HEIGHT / 2;

    xspeed *= -1;
    yspeed *= -1;
}

void bounce_ball(Vector2 *ball_pos)
{

    if ((int)ball_pos->y >= SCREEN_HEIGHT || (int)ball_pos->y <= 0)
    {
        yspeed *= -1;
    }

    if ((int)ball_pos->x >= SCREEN_WIDTH)
    {
        reset_ball_pos(ball_pos);
        player_score++;
    }
    else if ((int)ball_pos->x <= 0)
    {
        reset_ball_pos(ball_pos);
        cpu_score++;
    }

    ball_pos->y += yspeed;
    ball_pos->x += xspeed;
}

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pong");

    Vector2 ball_pos = {(float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2};
    Vector2 paddle_size = {20.0f, 60.0f};
    Vector2 *pball_pos = &ball_pos;

    Paddle *player_paddle = create_paddle();
    player_paddle->pos = (Vector2){10.0f, (float)SCREEN_HEIGHT / 2};
    player_paddle->size = paddle_size;

    Paddle *cpu_paddle = create_paddle();
    cpu_paddle->pos = (Vector2){(float) SCREEN_WIDTH - 30, (float)SCREEN_HEIGHT / 2};
    cpu_paddle->size = paddle_size;

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        bounce_ball(pball_pos);
        move_paddle(player_paddle, SCREEN_HEIGHT);

        cpu_paddle->pos.y = ball_pos.y - 40;

        int hit = paddle_ball_collide(player_paddle, ball_pos) | paddle_ball_collide(cpu_paddle, ball_pos);

        if (hit) 
        {
            xspeed *= -1;
            yspeed *= -1;

            hit = 0;
        }

        BeginDrawing();
            ClearBackground(BLACK);

            DrawText(TextFormat("%d", player_score), 30, 30, 40, WHITE);
            DrawText(TextFormat("%d", cpu_score), SCREEN_WIDTH - 50, 30, 40, WHITE);

            DrawCircleV(ball_pos, BALL_RADIUS, RAYWHITE);
            draw_paddle(player_paddle);
            draw_paddle(cpu_paddle);
        EndDrawing();
    }

    CloseWindow();
    free(player_paddle);
    free(cpu_paddle);

    return 0;
}
