/*******************************************************************************************
*   raylib - Pong
********************************************************************************************/

#include "raylib.h"
#include <stdio.h>

typedef struct
{
    int left, top, right, bottom;
} limit_t;
typedef enum GameScreen { LOGO = 0, TITLE, GAMEPLAY, ENDING } GameScreen;
typedef enum Direction { UP = 0, DOWN } Direction;

// ----------------------------
// Paint court limits and half.
// ----------------------------
void DrawCourt(const limit_t limit)
{
    // Bounds
    DrawRectangle(0, 0, limit.right, limit.top, GRAY);
    DrawRectangle(0, limit.bottom, limit.right, limit.bottom, GRAY);
    DrawRectangle(0, 0, limit.left, limit.bottom, GRAY);
    DrawRectangle(limit.right, 0, limit.bottom, limit.bottom + 10, GRAY);

    // Half court.
    DrawRectangle(((limit.right +10)/2) - 5, limit.top, 10, limit.bottom - 10, GRAY);
}

// ---------------------
// Manage ball movement.
// ---------------------
Rectangle AdvanceBall(const Rectangle pBall, const limit_t pLimit)
{
    static int xx = 5;
    static int yy = 5;

    if (pBall.x <= pLimit.left || pBall.x >= pLimit.right)
        xx = -xx;

    if (pBall.y <= pLimit.top || pBall.y >= pLimit.bottom)
        yy = -yy;

    return (Rectangle) {pBall.x + xx, pBall.y + yy, pBall.width, pBall.height};
}

// --------------------
// Just paint the ball.
// --------------------
void DrawBall(const Rectangle pBall)
{
    DrawRectangle(pBall.x - pBall.width/2 , pBall.y - pBall.height/2, pBall.width, pBall.height, WHITE);
}

// -------------
// Paint racket.
// -------------
void DrawRacket(const Rectangle pRacket)
{
    DrawRectangle(pRacket.x - pRacket.width/2 , pRacket.y - pRacket.height/2, pRacket.width, pRacket.height, WHITE);
}

// ------------
// Move racket.
// ------------
void  MoveRacket(Rectangle *pRacket, Direction pDir, const limit_t pLimit)
{
    int step;

    step = (pDir == UP)? -5: 5;

    if (pRacket->y + step > pLimit.top)
        pRacket->y += step;

    if (pRacket->y + step < pLimit.bottom)
        pRacket->y += step;

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
    limit_t limits = {10, 10, (GetMonitorWidth(0)/2) - 10 , (GetMonitorHeight(0)/2) - 10};


    UnhideWindow(); // Now display window in final position.
    SetTargetFPS(60);

    Rectangle ball = {100, 100, 10, 10};
    Rectangle leftRacket = {50, 100, 10, 50};
    Rectangle rightRacket = {GetMonitorWidth(0)/2 - 50, GetMonitorHeight(0)/2 - 100, 10, 50};
    bool WeArePlaying = true;

    while (!WindowShouldClose()) // Check ESC key.
    {
        if (WeArePlaying)
        {
            // Move elements.
            ball = AdvanceBall(ball, limits);

            // Check keys to move rackets. Q, A is left.
            if (IsKeyDown(KEY_Q))
            {
                MoveRacket(&leftRacket, UP, limits);
            } else if (IsKeyDown(KEY_A))
            {
                MoveRacket(&leftRacket, DOWN, limits);
            }
            if (IsKeyDown(KEY_I))
            {
                MoveRacket(&rightRacket, UP, limits);
            } else if (IsKeyDown(KEY_J))
            {
                MoveRacket(&rightRacket, DOWN, limits);
            }


            // Draw Scene.
            BeginDrawing();
            ClearBackground(BLACK);
            DrawCourt(limits);
            DrawBall (ball);
            DrawRacket (leftRacket);
            DrawRacket (rightRacket);
            EndDrawing();
        }
        else
        {
            // Get out of game.
        }
    }

    CloseWindow();
    return 0;
}
