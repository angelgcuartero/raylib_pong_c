/*******************************************************************************************
*   raylib - Pong
*   Angel G. Cuartero. 2019-03-07.
********************************************************************************************/

#include "raylib.h"
#include <stdio.h>

#define CALIBER 12

// User-defined types.
typedef enum GameScreen { TITLE = 0, GAMEPLAY, ENDING } GameScreen;
typedef enum Direction { UP = 0, DOWN } Direction;

// Global variables. They are global indeed.
Rectangle screen, border, top, bottom, ball, leftRacket, rightRacket;
int rightScore = 0, leftScore = 0, scoreWidth, winner;

// Prototipes.
void InitializeElements();
void setupScore();
void MoveBall();
void MoveRacket(Rectangle *pRacket, Direction pDir);
void ServeBall();

// Initialize window and primary game elements.
// --------------------------------------------
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
    scoreWidth = MeasureText("00", 60);
}

// Manage ball movement.
// ---------------------
void MoveBall()
{
    static int xx = CALIBER/2;
    static int yy = CALIBER/2;

    // Check collision with rackets and ball has not surpassed rackets.
    if ((CheckCollisionRecs(ball, leftRacket) && ball.x < leftRacket.x + leftRacket.width) ||
        (CheckCollisionRecs(ball, rightRacket) && ball.x > rightRacket.x - rightRacket.width))
        xx = -xx;
    else
        if (ball.y <= border.y || ball.y >= border.height)
            yy = -yy;
    else
    {
        // Score.
        if (ball.x <= border.x)
        {
            ++rightScore;
            ServeBall();
        }
        else if (ball.x >= border.width)
        {
            ++leftScore;
            ServeBall();
        }
    }

    // Move pBall.
    ball.x += xx;
    ball.y += yy;
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
void ServeBall()
{
    ball.x = border.width/2;
    ball.y = GetRandomValue(border.y + 10, border.height);
}

// Start game.
// -----------
int main(void)
{
    GameScreen currentScreen = TITLE;
    InitializeElements();

    // Main loop.
    while (!WindowShouldClose()) // Check ESC key.
    {
        // Updating.
        switch(currentScreen)
        {
            case TITLE:
            {
                if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
                    currentScreen = GAMEPLAY;
            } break;
            case GAMEPLAY:
            {
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

                if ((leftScore == 10) || (rightScore == 10))
                {
                    winner = (leftScore == 10)? 1 : 2;
                    rightScore = leftScore = 0; // Reset Score.
                    currentScreen = ENDING;
                }
            } break;
            case ENDING:
            {
                if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
                    currentScreen = GAMEPLAY;
            } break;
            default: break;
        }

        // Rendering.
        BeginDrawing();
        ClearBackground(RAYWHITE);
        switch(currentScreen)
        {
            case TITLE:
            {
                ClearBackground(BLACK);
                DrawText("PONG", 120, 20, 120, GRAY);
                DrawText("Based on Atari PONG", 120, 140, 60, GRAY);
                DrawText("Programmed by Angel G. Cuartero", 120, 220, 20, GRAY);
                DrawText("Player 1: Q, A", 120, 390, 20, GRAY);
                DrawText("Player 2: I, J", 120, 420, 20, GRAY);
                DrawText("Press ENTER to PLAY", 120, 450, 20, GRAY);
                DrawText("Press ESCAPE to QUIT", 120, 480, 20, GRAY);

            } break;
            case GAMEPLAY:
            {
                // Draw court.
                DrawRectangle(screen.x, screen.y, screen.width, screen.height, GRAY);
                DrawRectangle(screen.x, border.y, screen.width, border.height, BLACK);
                DrawRectangle((screen.width/2) - 5, border.y, CALIBER, border.height, GRAY);
                // Draw score.
                DrawText(FormatText("%02d", leftScore), (screen.width/2) - 50 - scoreWidth, 50, 60, GRAY);
                DrawText(FormatText("%02d", rightScore), (screen.width/2) + 50, 50, 60, GRAY);
                // Draw ball.
                DrawRectangle(ball.x, ball.y, ball.width, ball.height, WHITE);
                // Draw rackets.
                DrawRectangle(leftRacket.x, leftRacket.y, leftRacket.width, leftRacket.height, WHITE);
                DrawRectangle(rightRacket.x, rightRacket.y, rightRacket.width, rightRacket.height, WHITE);
            } break;
            case ENDING:
            {
                ClearBackground(BLACK);
                DrawText(FormatText("Winner is Player %d", winner), 120 , 50, 60, GRAY);
                DrawText("Press ENTER to PLAY AGAIN", 120, 420, 20, GRAY);
                DrawText("Press ESCAPE to QUIT", 120, 450, 20, GRAY);
            } break;
            default: break;
            }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
