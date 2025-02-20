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

// typedef enum
// {
//     UP,
//     DOWN
// } POSITION;

int main(void)
{
    // POSITION pos = UP;
    int l_posX = 0;
    int l_posY = height / 2 - p_height / 2;
    uint8_t l_score = 0;

    int r_posX = width - p_width;
    int r_posY = height / 2 - p_height / 2;
    uint8_t r_score = 0;

    // raylib stuff
    Vector2 posBall = {
        .x = 1.0f + radius,
        .y = 1.0f + radius,
    };
    Vector2 velBall = {
        .x = 5.0f,
        .y = 4.0f,
    };
    uint8_t l_collision = 0;
    uint8_t r_collision = 0;

    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(width, height, "Raylib App");
    SetTargetFPS(fps);
    Rectangle l_paddle = {
        .x = l_posX,
        .y = l_posY,
        .height = p_height,
        .width = p_width,
    };

    Rectangle r_paddle = {
        .x = r_posX,
        .y = r_posY,
        .height = p_height,
        .width = p_width,
    };

    Rectangle start_btn = {
        .height = 50,
        .width = 145,
        .x = width / 2 - 85,
        .y = 100,
    };

    while (!WindowShouldClose())
    {

        if (IsKeyDown(KEY_W) && l_paddle.y > 0)
        {
            l_paddle.y -= step;
        }

        if (IsKeyDown(KEY_S) && l_paddle.y < height - p_height)
        {
            l_paddle.y += step;
        }

        if (IsKeyDown(KEY_UP) && r_paddle.y > 0)
        {
            r_paddle.y -= step;
        }

        if (IsKeyDown(KEY_DOWN) && r_paddle.y < height - p_height)
        {
            r_paddle.y += step;
        }
        posBall.x += velBall.x;
        posBall.y += velBall.y;

        l_collision = CheckCollisionCircleRec(posBall, (float)radius, l_paddle);
        r_collision = CheckCollisionCircleRec(posBall, (float)radius, r_paddle);
        // Check walls collision for bouncing
        if ((posBall.x >= (GetScreenWidth() - radius)))
            velBall.x *= -1.0f;
        if ((posBall.y >= (GetScreenHeight() - radius)) || (posBall.y <= radius))
            velBall.y *= -1.0f;

        if (r_collision || l_collision)
        {
            velBall.x *= -1.0f;
        }

        if (posBall.x <= radius)
        {
            r_score += 1;
            posBall.x = width / 2 - p_width / 2;
            posBall.y = height / 2 - p_height / 2;

            velBall.x = 0;
            velBall.y = 0;
        }

        if (posBall.x >= width - radius)
        {
            l_score += 1;
            posBall.x = width / 2 - p_width / 2;
            posBall.y = height / 2 - p_height / 2;

            velBall.x = 0;
            velBall.y = 0;
        }
        Vector2 mouse_pos = GetMousePosition();
        if (CheckCollisionPointRec(mouse_pos, start_btn) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            velBall.x = 2.0f;
            velBall.y = -4.0f;
        }

        BeginDrawing();
        ClearBackground(DARKPURPLE);
        DrawRectangleRounded(start_btn, 4.0f, 0.0, Fade(RED, 0.3f));
        DrawText("START", width / 2 - 55, 115, 25, RAYWHITE);
        DrawText(TextFormat("Player 1: %u", l_score), p_width + 20, 25, 20, RAYWHITE);
        DrawText(TextFormat("Player 2: %u", r_score), width - 150, 25, 20, RAYWHITE);

        DrawRectangleRec(l_paddle, l_collision ? RED : ORANGE);
        DrawRectangleRec(r_paddle, r_collision ? RED : ORANGE);
        DrawCircleV(posBall, (float)radius, (r_collision || l_collision) ? BLUE : DARKBLUE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
