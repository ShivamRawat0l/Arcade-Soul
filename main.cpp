#include "raylib.h"
#include <vector>
#include "src/screens/snakeGame/snakeGame.h"
#include "src/screens/mainMenu/mainMenu.h"
#include "src/utils/constants.h"

using namespace std;

int main(void)
{
    InitWindow(screenWidth, screenHeight, "Arcade - Soul");
    SetTargetFPS(60);
    //mainMenu();
    snakeGame(); // Here call which function to call
    CloseWindow();
    return 0;
}
