/*******************************************************************************************
*   raylib - Pong
********************************************************************************************/

#include "raylib.h"
#include <stdio.h>

// User-defined types.
typedef struct
{
    int left, top, right, bottom;
} limit_t;
typedef enum GameScreen { LOGO = 0, TITLE, GAMEPLAY, ENDING } GameScreen;
typedef enum Direction { UP = 0, DOWN } Direction;

// Global variables. They are global indeed.
limit_t screen;
limit_t border;

// ----------------------------
// Paint court limits and half.
// ----------------------------
void DrawCourt()
{
    // Bounds
    DrawRectangle(0, 0, border.right, border.top, GRAY);
    DrawRectangle(0, border.bottom, border.right, border.bottom, GRAY);
    DrawRectangle(0, 0, border.left, border.bottom, GRAY);
    DrawRectangle(border.right, 0, border.bottom, border.bottom + 10, GRAY);

    // Half court.
    DrawRectangle(((border.right +10)/2) - 5, border.top, 10, border.bottom - 10, GRAY);
}

// ---------------------
// Manage ball movement.
// ---------------------
void AdvanceBall(Rectangle *pBall)
{
    static int xx = 5;
    static int yy = 5;

    // Check and reverse direction.
    if (pBall->x <= border.left || pBall->x >= border.right)
        xx = -xx;

    if (pBall->y <= border.top || pBall->y >= border.bottom)
        yy = -yy;

    // Move ball.
    pBall->x += xx;
    pBall->y += yy;
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
void  MoveRacket(Rectangle *pRacket, Direction pDir)
{
    int step = (pDir == UP)? -5: 5;
    pRacket->y += step;

    if (pRacket->y < border.top)
        pRacket->y = border.top ;

    if (pRacket->y + pRacket->height > border.bottom)
        pRacket->y = border.bottom - pRacket->height;

}

// -----------
// Start game.
// -----------
int main(void)
{
    InitWindow(0, 0, "Pong");
    HideWindow(); // To avoid see window moving.

    // Calculate size, position and inner limits of window.
    screen = (limit_t){0, 0, GetMonitorWidth(0)/2, GetMonitorHeight(0)/2};
    border = (limit_t){10, 10, screen.right - 10 , screen.bottom - 10};

    SetWindowSize(GetMonitorWidth(0)/2, GetMonitorHeight(0)/2);
    SetWindowPosition(GetMonitorWidth(0)/4, GetMonitorHeight(0)/4);


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
            AdvanceBall(&ball);

            // Check keys to move rackets. Q, A is left.
            if (IsKeyDown(KEY_Q))
            {
                MoveRacket(&leftRacket, UP);
            } else if (IsKeyDown(KEY_A))
            {
                MoveRacket(&leftRacket, DOWN);
            }
            if (IsKeyDown(KEY_I))
            {
                MoveRacket(&rightRacket, UP);
            } else if (IsKeyDown(KEY_J))
            {
                MoveRacket(&rightRacket, DOWN);
            }


            // Draw Scene.
            BeginDrawing();
            ClearBackground(BLACK);
            DrawCourt();
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
