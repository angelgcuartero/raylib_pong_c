/*******************************************************************************************
*   raylib - Pong
********************************************************************************************/

#include "raylib.h"
#include <stdio.h>

typedef struct
{
    int left, top, right, bottom;
} lmt_t;


// Paint court.
void PaintCourt(const lmt_t lmt)
{
    // Bounds
    DrawRectangle(0, 0, lmt.right, lmt.top, GRAY);
    DrawRectangle(0, lmt.bottom, lmt.right, lmt.bottom, GRAY);
    DrawRectangle(0, 0, lmt.left, lmt.bottom, GRAY);
    DrawRectangle(lmt.right, 0, lmt.bottom, lmt.bottom + 10, GRAY);

    // Half court.
    DrawRectangle(((lmt.right +10)/2) - 5, lmt.top, 10, lmt.bottom - 10, GRAY);
}

// Manage ball movement.
Rectangle AdvanceBall(const Rectangle pball, const lmt_t limit)
{
    static int xx = 5;
    static int yy = 5;

    if (pball.x < limit.left || pball.x > limit.right)
        xx = -xx;

    if (pball.y < limit.top || pball.y > limit.bottom)
        yy = -yy;

    return (Rectangle) {pball.x + xx, pball.y + yy, pball.width, pball.height} ;

}

// Just paint the ball.
void DrawBall(const Rectangle pball)
{
    DrawRectangle(pball.x - pball.width/2 , pball.y - pball.height/2, pball.width, pball.height, WHITE);
}

// Start game.
int main(void)
{
    int screenWidth = 0;
    int screenHeight = 0;
    char Mensaje[512];
    Rectangle ball = {100, 100, 10, 10};

    InitWindow(0, 0, "Pong");

    HideWindow();
    screenWidth = GetMonitorWidth(0) / 2;
    screenHeight = GetMonitorHeight(0) / 2;
    SetWindowSize(screenWidth, screenHeight);
    SetWindowPosition(screenWidth/2, screenHeight/2);

    lmt_t limits = {10, 10, screenWidth-10 , screenHeight-10};

    sprintf(Mensaje, "%d %d %d %d", limits.left, limits.right, limits.top, limits.bottom);
    TraceLog(LOG_INFO, Mensaje);

    UnhideWindow();

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();

            ClearBackground(BLACK);

            PaintCourt(limits);
            ball = AdvanceBall(ball, limits);
            DrawBall (ball);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
