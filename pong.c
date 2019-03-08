/*******************************************************************************************
*   raylib - Pong
********************************************************************************************/

#include "raylib.h"
#include <stdio.h>

// User-defined types.
typedef struct
{
    int x, y, xx, yy;
} int_rectangle_t;
// typedef enum GameScreen { LOGO = 0, TITLE, GAMEPLAY, ENDING } GameScreen;
typedef enum Direction { UP = 0, DOWN } Direction;

// Global variables. They are global indeed.
int_rectangle_t screen;
int_rectangle_t border;

// ----------------------------
// Paint court limits and half.
// ----------------------------
void DrawCourt()
{
    // Bounds
    DrawRectangle(screen.x, screen.y, screen.xx, screen.yy, GRAY);
    DrawRectangle(border.x, border.y, border.xx, border.yy, BLACK);

    // Half court.
    DrawRectangle((screen.xx/2) - 5, border.y, 10, border.yy, GRAY);
}

// ---------------------
// Manage ball movement.
// ---------------------
void AdvanceBall(int_rectangle_t *pBall)
{
    static int xx = 5;
    static int yy = 5;

    // Check and reverse direction.
    if (pBall->x <= border.x || pBall->x >= border.xx)
        xx = -xx;

    if (pBall->y <= border.y || pBall->y >= border.yy)
        yy = -yy;

    // Move ball.
    pBall->x += xx;
    pBall->y += yy;
}

// --------------------
// Just paint the ball.
// --------------------
void DrawBall(const int_rectangle_t pBall)
{
    DrawRectangle(pBall.x, pBall.y, pBall.xx, pBall.yy, WHITE);
}

// -------------
// Paint racket.
// -------------
void DrawRacket(const int_rectangle_t pRacket)
{
    DrawRectangle(pRacket.x, pRacket.y, pRacket.xx, pRacket.yy, WHITE);
}

// ------------
// Move racket.
// ------------
void  MoveRacket(int_rectangle_t *pRacket, Direction pDir)
{

    int step = (pDir == UP)? -5: 5;
    pRacket->y += step;

    if ((pRacket->y <= border.y) && pDir == UP)
    {
        pRacket->y = border.y;
    }
    else
    if ((pRacket->y >= border.yy - pRacket->yy) && pDir == DOWN)
    {
        pRacket->y = border.yy - pRacket->yy;
    }
}

// -----------
// Start game.
// -----------
int main(void)
{
    InitWindow(0, 0, "Pong");
    HideWindow(); // To avoid see window moving.

    // Calculate size, position and inner limits of window.
    screen = (int_rectangle_t){0, 0, GetMonitorWidth(0)/2, GetMonitorHeight(0)/2};
    border = (int_rectangle_t){10, 10, screen.xx - 20 , screen.yy - 20};
    SetWindowSize(screen.xx, screen.yy);
    SetWindowPosition(screen.xx/2, screen.yy/2);

    UnhideWindow(); // Now display window in final position.
    SetTargetFPS(60);

    int_rectangle_t ball = {100, 100, 10, 10};
    int_rectangle_t leftRacket = {50, 100, 10, 60};
    int_rectangle_t rightRacket = {screen.xx - 50, screen.yy - 100, 10, 60};
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
