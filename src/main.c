#include <raylib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

const uint16_t width = 800;
const uint16_t height = 600;
const uint8_t step = 5;
const uint8_t fps = 60;
const uint8_t p_height = 80;
const uint8_t p_width = 20;
const uint8_t radius = 20;

typedef enum
{
    UP,
    DOWN
} POSITION;

int main(void)
{
    POSITION pos = UP;
    int posX = 0;
    int posY = height - p_height / 2;

    // raylib stuff
    Vector2 posBall = {
        .x = 1.0f + radius,
        .y = 1.0f + radius,
    };
    Vector2 velBall = {
        .x = 5.0f,
        .y = 4.0f,
    };
    uint8_t collision = 0;

    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(width, height, "Raylib App");
    SetTargetFPS(fps);
    Rectangle paddle =
        {.x = posX, .y = posY, .height = p_height, .width = p_width};

    while (!WindowShouldClose())
    {

        if (IsKeyDown(KEY_W) && paddle.y > 0)
        {
            paddle.y -= step;
        }

        if (IsKeyDown(KEY_S) && paddle.y < height - p_height)
        {
            paddle.y += step;
        }
        posBall.x += velBall.x;
        posBall.y += velBall.y;

        collision = CheckCollisionCircleRec(posBall, (float)radius, paddle);
        // Check walls collision for bouncing
        if ((posBall.x >= (GetScreenWidth() - radius)) || (posBall.x <= radius))
            velBall.x *= -1.0f;
        if ((posBall.y >= (GetScreenHeight() - radius)) || (posBall.y <= radius))
            velBall.y *= -1.0f;

        if (collision)
        {
            velBall.x *= -1.0f;
        }

        BeginDrawing();
        ClearBackground(DARKPURPLE);
        DrawText("Hello, Bibi!", 250, 100, 50, RAYWHITE);
        DrawRectangleRec(paddle, collision ? RED : ORANGE);
        DrawCircleV(posBall, (float)radius, BLUE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
