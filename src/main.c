#include <raylib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define CENTER_W width / 2 - p_width / 2
#define CENTER_H height / 2 - p_height / 2

const uint16_t width = 800;
const uint16_t height = 600;
const uint8_t step = 5;
const uint8_t fps = 60;
const uint8_t p_height = 80;
const uint8_t p_width = 20;
const uint8_t radius = 20;
const uint8_t vel_x = 5.0f;
const uint8_t vel_y = 5.0f;

int main(void)
{
    uint8_t l_score = 0;
    uint8_t r_score = 0;

    // RAYLIB stuff
    Vector2 ball_pos = {
        .x = 1.0f + radius,
        .y = 1.0f + radius,
    };
    Vector2 ball_vel = {
        .x = vel_x,
        .y = vel_y,
    };
    uint8_t l_collision = 0;
    uint8_t r_collision = 0;
    uint8_t isSoundPlaying = 0;

    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(width, height, "Raylib App");
    SetTargetFPS(fps);
    Rectangle l_paddle = {
        .x = 0,
        .y = CENTER_H,
        .height = p_height,
        .width = p_width,
    };

    Rectangle r_paddle = {
        .x = width - p_width,
        .y = CENTER_H,
        .height = p_height,
        .width = p_width,
    };

    Rectangle start_btn = {
        .height = 50,
        .width = 145,
        .x = width / 2 - 85,
        .y = 100,
    };

    // AUDIO
    InitAudioDevice();
    Sound hitSound = LoadSound("assets/bum.wav");

    // MAIN LOOP
    while (!WindowShouldClose())
    {

        // MOVE PADDLES
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

        // MOVE BALL
        ball_pos.x += ball_vel.x;
        ball_pos.y += ball_vel.y;

        // DETECT COLLISION with PADDLES
        l_collision = CheckCollisionCircleRec(ball_pos, (float)radius + 0.1f, l_paddle);
        r_collision = CheckCollisionCircleRec(ball_pos, (float)radius + 0.1f, r_paddle);

        // Collision detection right wall
        if ((ball_pos.y >= (GetScreenHeight() - radius + 5)) || (ball_pos.y <= radius - 5))
            ball_vel.y *= -1.0f;

        // change velocity on paddle collision
        if (r_collision)
        {
            if (!isSoundPlaying)
            {
                PlaySound(hitSound);
                isSoundPlaying = true;
            }
            ball_vel.x = -4;
        }
        if (l_collision)
        {
            PlaySound(hitSound);
            ball_vel.x = 4;
        }

        /**
         * Detect Collision with horizontal walls
         * reset ball
         * increase score
         */
        if (ball_pos.x <= radius - 10)
        {
            r_score += 1;
            ball_pos.x = CENTER_W;
            ball_pos.y = CENTER_H;

            ball_vel.x = 0;
            ball_vel.y = 0;
        }

        if (ball_pos.x >= width - radius + 10)
        {
            l_score += 1;
            ball_pos.x = CENTER_W;
            ball_pos.y = CENTER_H;

            ball_vel.x = 0;
            ball_vel.y = 0;
        }
        Vector2 mouse_pos = GetMousePosition();
        if ((CheckCollisionPointRec(mouse_pos, start_btn) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) || IsKeyDown(KEY_ENTER))
        {
            ball_vel.x = vel_x;
            ball_vel.y = -vel_y;
        }

        if (isSoundPlaying)
        {
            isSoundPlaying = false;
        }

        BeginDrawing();
        ClearBackground(DARKPURPLE);
        DrawRectangleRounded(start_btn, 4.0f, 0.0, Fade(RED, 0.3f));
        DrawText("START", width / 2 - 55, 115, 25, RAYWHITE);
        DrawText(TextFormat("Player 1: %u", l_score), p_width + 20, 25, 20, RAYWHITE);
        DrawText(TextFormat("Player 2: %u", r_score), width - 150, 25, 20, RAYWHITE);

        DrawRectangleRec(l_paddle, l_collision ? RED : ORANGE);
        DrawRectangleRec(r_paddle, r_collision ? RED : ORANGE);
        DrawCircleV(ball_pos, (float)radius, (r_collision || l_collision) ? BLUE : DARKBLUE);
        EndDrawing();
    }

    UnloadSound(hitSound);
    CloseAudioDevice();
    CloseWindow();
    return 0;
}
