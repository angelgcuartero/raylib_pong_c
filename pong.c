/*******************************************************************************************
*   raylib - Pong
********************************************************************************************/

#include "raylib.h"
#include <stdio.h>

typedef struct
{
    int left, top, right, bottom;
} lmt_t;


// ----------------------------
// Paint court limits and half.
// ----------------------------
void DrawCourt(const lmt_t lmt)
{
    // Bounds
    DrawRectangle(0, 0, lmt.right, lmt.top, GRAY);
    DrawRectangle(0, lmt.bottom, lmt.right, lmt.bottom, GRAY);
    DrawRectangle(0, 0, lmt.left, lmt.bottom, GRAY);
    DrawRectangle(lmt.right, 0, lmt.bottom, lmt.bottom + 10, GRAY);

    // Half court.
    DrawRectangle(((lmt.right +10)/2) - 5, lmt.top, 10, lmt.bottom - 10, GRAY);
}

// ---------------------
// Manage ball movement.
// ---------------------
Rectangle AdvanceBall(const Rectangle pball, const lmt_t limit)
{
    static int xx = 5;
    static int yy = 5;

    if (pball.x <= limit.left || pball.x >= limit.right)
        xx = -xx;

    if (pball.y <= limit.top || pball.y >= limit.bottom)
        yy = -yy;

    return (Rectangle) {pball.x + xx, pball.y + yy, pball.width, pball.height};
}

// --------------------
// Just paint the ball.
// --------------------
void DrawBall(const Rectangle pball)
{
    DrawRectangle(pball.x - pball.width/2 , pball.y - pball.height/2, pball.width, pball.height, WHITE);
}

void DrawRacket(const Rectangle pracket)
{
    DrawRectangle(pracket.x - pracket.width/2 , pracket.y - pracket.height/2, pracket.width, pracket.height, WHITE);
}

// -----------
// Start game.
// -----------
int main(void)
{
    InitWindow(0, 0, "Pong");
    HideWindow(); // To avoid see window moving.

    // Calculate size, position and inner limits of window.
    SetWindowSize(GetMonitorWidth(0)/2, GetMonitorHeight(0)/2);
    SetWindowPosition(GetMonitorWidth(0)/4, GetMonitorHeight(0)/4);

    lmt_t limits = {10, 10, (GetMonitorWidth(0)/2) - 10 , (GetMonitorHeight(0)/2) - 10};

    UnhideWindow(); // Now display window in final position.
    SetTargetFPS(60);

    Rectangle ball = {100, 100, 10, 10};
    Rectangle leftRacket = {50, 100, 10, 50};
    Rectangle rightRacket = {GetMonitorWidth(0)/2 - 50, GetMonitorHeight(0)/2 - 100, 10, 50};

    while (!WindowShouldClose()) // Check ESC key.
    {
        BeginDrawing();

            ClearBackground(BLACK);

            DrawCourt(limits);
            ball = AdvanceBall(ball, limits);
            DrawBall (ball);
            DrawRacket (leftRacket);
            DrawRacket (rightRacket);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
