/*******************************************************************************************
*   raylib - Pong
*   Angel G. Cuartero. 2019-03-07.
********************************************************************************************/

#include "raylib.h"
#include <stdio.h>

#define CALIBER 12

// User-defined types.
typedef enum GameScreen { LOGO = 0, TITLE, GAMEPLAY, ENDING } GameScreen;
typedef enum Direction { UP = 0, DOWN } Direction;

// Global variables. They are global indeed.
Rectangle screen, border, top, bottom, ball, leftRacket, rightRacket;
int rightScore, leftScore, scoreWidth;

// Prototipes.
void InitializeElements();
void setupScore();
void MoveBall(Rectangle *pBall);
void MoveRacket(Rectangle *pRacket, Direction pDir);
void ServeBall(Rectangle *pBall);
void DrawCourt();
void DrawBall(Rectangle *pBall);
void DrawRacket(Rectangle *pRacket);
void DrawScore();

// Initialize window and primary game elements.
void InitializeElements()
{
    InitWindow(0, 0, "Pong");
    HideWindow(); // To avoid see window moving.

    // Calculate size, position and inner limits of window.
    screen = (Rectangle){0, 0, GetMonitorWidth(0)/2, GetMonitorHeight(0)/2};
    border = (Rectangle){CALIBER, CALIBER, screen.width - (2*CALIBER) , screen.height - (2*CALIBER)};
    top = (Rectangle) {screen.x, screen.y, border.width, border.y};
    bottom = (Rectangle) {screen.x, border.height+CALIBER, screen.width, screen.y};
    SetWindowSize(screen.width, screen.height);
    SetWindowPosition(screen.width/2, screen.height/2);

    UnhideWindow(); // Now display window in final position.
    SetTargetFPS(60);

    // Initialize elements.
    ball = (Rectangle) {5*CALIBER, border.height, CALIBER, CALIBER};
    leftRacket = (Rectangle) {border.x + CALIBER, border.height/2, CALIBER, 5*CALIBER};
    rightRacket = (Rectangle) {border.width - CALIBER, border.height/2, CALIBER, 5*CALIBER};
    setupScore();
    scoreWidth = MeasureText("00", 60);
}

// Initialize Score
// ----------------
void setupScore() {
    rightScore = 0;
    leftScore = 0;
}

// Manage ball movement.
// ---------------------
void MoveBall(Rectangle *pBall)
{
    static int xx = CALIBER/2;
    static int yy = CALIBER/2;

    // Check collision with rackets
    if (CheckCollisionRecs(*pBall, leftRacket) || CheckCollisionRecs(*pBall, rightRacket))
        xx = -xx;
    else
        if (pBall->y <= border.y || pBall->y >= border.height)
            yy = -yy;
    else
    {
        // Score.
        if (pBall->x <= border.x)
        {
            ++rightScore;
            ServeBall(pBall);

        }
        else if (pBall->x >= border.width)
        {
            ++leftScore;
            ServeBall(pBall);
        }

    }

    // Move pBall.
    pBall->x += xx;
    pBall->y += yy;
}

// Manage racket movement.
// -----------------------
void MoveRacket(Rectangle *pRacket, Direction pDir)
{

    int step = (pDir == UP)? -CALIBER/2: CALIBER/2;

    if ((CheckCollisionRecs(top, *pRacket) && pDir == UP) ||
        (CheckCollisionRecs(bottom, *pRacket) && pDir == DOWN))
            return;
    pRacket->y += step;
}

// Serve ball after scoring.
// -------------------------
void ServeBall(Rectangle *pBall)
{
    pBall->x = border.width/2;
    pBall->y = GetRandomValue(border.y + 10, border.height);
}

// Draw court limits and half.
// ---------------------------
void DrawCourt()
{
    DrawRectangle(screen.x, screen.y, screen.width, screen.height, GRAY);
    DrawRectangle(screen.x, border.y, screen.width, border.height, BLACK);
    DrawRectangle((screen.width/2) - 5, border.y, CALIBER, border.height, GRAY);
}

// Just paint the ball.
// --------------------
void DrawBall(Rectangle *pBall)
{
    DrawRectangle(pBall->x, pBall->y, pBall->width, pBall->height, WHITE);
}

// Draw racket.
// ------------
void DrawRacket(Rectangle *pRacket)
{
    DrawRectangle(pRacket->x, pRacket->y, pRacket->width, pRacket->height, WHITE);
}

// Draw score.
// -----------
void DrawScore()
{
    DrawText(FormatText("%02d", rightScore), (screen.width/2) - 50 - scoreWidth, 50, 60, GRAY);
    DrawText(FormatText("%02d", leftScore), (screen.width/2) + 50, 50, 60, GRAY);
}

// Start game.
// -----------
int main(void)
{
    InitializeElements();

    bool WeArePlaying = true;

    // Main loop.
    while (!WindowShouldClose()) // Check ESC key.
    {
        if (WeArePlaying)
        {
            // Moves.
            MoveBall(&ball);

            // Check racket keys.
            if (IsKeyDown(KEY_Q))
                MoveRacket(&leftRacket, UP);
            else if (IsKeyDown(KEY_A))
                MoveRacket(&leftRacket, DOWN);

            if (IsKeyDown(KEY_I))
                MoveRacket(&rightRacket, UP);
            else if (IsKeyDown(KEY_J))
                MoveRacket(&rightRacket, DOWN);

            // Renders.
            BeginDrawing();
            // No need to clear background, this renders the full court.
            // ClearBackground(BLACK);
            DrawCourt();
            DrawScore();
            DrawBall(&ball);
            DrawRacket(&leftRacket);
            DrawRacket(&rightRacket);
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
