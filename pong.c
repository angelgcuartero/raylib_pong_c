/*******************************************************************************************
*   raylib - Pong
********************************************************************************************/

#include "raylib.h"
#include <stdio.h>

int screenWidth = 0;
int screenHeight = 0;
Rectangle ball = {100, 100, 10, 10};
int xx = 5, yy = 5;
int left;
int right;
int top;
int bottom;

// Paint court.
void PaintCourt()
{
    left = 10;
    right = screenWidth - 10;
    top = 10;
    bottom = screenHeight - 10;

    // Bounds
    DrawRectangle(0, 0, screenWidth, top, GRAY);
    DrawRectangle(0, bottom, screenWidth, screenHeight, GRAY);
    DrawRectangle(0, 0, left, screenHeight, GRAY);
    DrawRectangle(right, 0, bottom, screenHeight, GRAY);

    // Half court.
    DrawRectangle((screenWidth/2) - 5, top, 10, bottom - 10, DARKGRAY);
}

// Start game.
int main(void)
{
    InitWindow(0, 0, "Pong");

    HideWindow();
    screenWidth = GetMonitorWidth(0) / 2;
    screenHeight = GetMonitorHeight(0) / 2;
    SetWindowSize(screenWidth, screenHeight);
    SetWindowPosition(screenWidth/2, screenHeight/2);
    UnhideWindow();

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();

            ClearBackground(BLACK);

            PaintCourt();
            if (!(ball.x > left && ball.x < right))
                xx = -xx;

            if (!(ball.y > top && ball.y < bottom))
                yy = -yy;

            ball.x += xx;
            ball.y += yy;
            DrawRectangle(ball.x-5, ball.y-5, 10, 10, WHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
