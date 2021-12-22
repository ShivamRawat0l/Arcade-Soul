#include <vector>
#ifndef RAYLIB_H
#include "raylib.h"
#else
#error You need to include raylib
#endif
#ifndef screenHeight
#include "../../utils/constants.h"
#else
#error You need to include raylib
#endif
#include <iostream>
#include <queue>
using namespace std;

enum Directions
{
    left,
    right,
    up,
    down
};

bool crashed(vector<vector<int>> snakePosition)
{
    for (int i = 1; i < snakePosition.size(); i++)
    {
        if (snakePosition[0][0] == snakePosition[i][0] && snakePosition[0][1] == snakePosition[i][1])
        {
            cout << snakePosition[0][0] << " " << snakePosition[i][0] << " " << snakePosition[0][1] << " " << snakePosition[i][1] << endl;
            return true;
        }
    }
    return false;
}

void showq(queue<Directions> gq)
{
    queue<Directions> g = gq;
    while (!g.empty())
    {
        cout << '\t' << g.front();
        g.pop();
    }
    cout << '\n';
}

void handleInputQueue(queue<Directions> &inputQueue)
{
    showq(inputQueue);
    if (IsKeyReleased(KEY_RIGHT))
    {
        if (inputQueue.empty() || inputQueue.back() != Directions::right)
            inputQueue.push(Directions::right);
    }
    if (IsKeyReleased(KEY_LEFT))
    {
        if (inputQueue.empty() || inputQueue.back() != Directions::left)
            inputQueue.push(Directions::left);
    }
    if (IsKeyReleased(KEY_UP))
    {
        if (inputQueue.empty() || inputQueue.back() != Directions::up)
            inputQueue.push(Directions::up);
    }
    if (IsKeyReleased(KEY_DOWN))
    {
        if (inputQueue.empty() || inputQueue.back() != Directions::down)
            inputQueue.push(Directions::down);
    }
}
bool handleInput(Directions &snakeDirection, Directions &oldSnakeDirection, queue<Directions> &inputQueue)
{
    if (inputQueue.empty())
    {
        return false;
    }
    Directions inputDirection;
    inputDirection = inputQueue.front();
    inputQueue.pop();
    if (inputDirection == Directions::right && snakeDirection != Directions::left)
    {
        oldSnakeDirection = snakeDirection;
        snakeDirection = Directions::right;
        return true;
    }
    if (inputDirection == Directions::left && snakeDirection != Directions::right)
    {
        oldSnakeDirection = snakeDirection;
        snakeDirection = Directions::left;
        return true;
    }
    if (inputDirection == Directions::up && snakeDirection != Directions::down)
    {
        oldSnakeDirection = snakeDirection;
        snakeDirection = Directions::up;
        return true;
    }
    if (inputDirection == Directions::down && snakeDirection != Directions::up)
    {
        oldSnakeDirection = snakeDirection;
        snakeDirection = Directions::down;
        return true;
    }
    return false;
}

void updateHeadPosition(vector<vector<int>> &snakePosition, int chunk, int &oldPositionX, int &oldPositionY, Directions snakeDirection)
{

    oldPositionX = snakePosition[0][0];
    oldPositionY = snakePosition[0][1];
    switch (snakeDirection)
    {
    case Directions::right:
        snakePosition[0][0] += chunk;
        break;
    case Directions::left:
        snakePosition[0][0] -= chunk;
        break;
    case Directions::up:
        snakePosition[0][1] -= chunk;
        break;
    case Directions::down:
        snakePosition[0][1] += chunk;
        break;
    default:
        break;
    }
}

void updateTailPosition(vector<vector<int>> &snakePosition, int oldPositionX, int oldPositionY)
{
    for (int i = snakePosition.size() - 1; i > 0; i--)
    {

        if (i == 1)
        {
            snakePosition[1][0] = oldPositionX;
            snakePosition[1][1] = oldPositionY;
        }
        else
        {
            snakePosition[i][0] = snakePosition[i - 1][0];
            snakePosition[i][1] = snakePosition[i - 1][1];
        }
    }
}

int snakeGame(void)
{
    vector<vector<int>> snakePosition = {
        {50, 30},
        {40, 30},
        {30, 30},
        {20, 30},
        {10, 30},
        {0, 30},
    };

    Directions snakeDirection = Directions::right, oldSnakeDirection = Directions::right;

    const int speed = 1, chunk = 10; //Speed is how fast to move and chunk is at how much distance to move
    int move = 0;
    bool crashedFlag = false; // if the snake has moved or not
    int oldPositionX = -1, oldPositionY = -1;
    queue<Directions> inputQueue;
    Vector2 positions;
    positions.x = 30;
    positions.y = 60;
    Font font = LoadFont("resources/fonts/jupiter_crash.png");
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        handleInputQueue(inputQueue);

        move += speed;
        if (move == chunk)
        {
            handleInput(snakeDirection, oldSnakeDirection, inputQueue);
            move = 0;
            updateHeadPosition(snakePosition, chunk, oldPositionX, oldPositionY, snakeDirection);
            updateTailPosition(snakePosition, oldPositionX, oldPositionY);
        }

        if (crashed(snakePosition))
        {
            crashedFlag = true;
        }
        BeginDrawing();
        ClearBackground(RAYWHITE);
        //DrawText("move the ball with arrow keys", 10, 10, 20, DARKGRAY);
        DrawRectangle(0, 0, screenWidth, screenHeight, BLACK);
        if (crashedFlag)
        {
            DrawTextEx(font, "GAME OVER", positions, 48, 10.0, WHITE);
        }
        else
        {
            DrawRectangle(snakePosition[0][0], snakePosition[0][1], 10, 10, WHITE);
            for (int i = snakePosition.size() - 1; i > 0; i--)
            {
                DrawRectangle(snakePosition[i][0], snakePosition[i][1], 10, 10, WHITE);
            }
        }
        EndDrawing();
    }

    return 0;
}
