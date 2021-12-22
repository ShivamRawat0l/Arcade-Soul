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

using namespace std;

int mainMenu(void)
{
    Vector2 mouseClickPosition;
    int display = GetCurrentMonitor();
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            mouseClickPosition = GetMousePosition();
            if (mouseClickPosition.x < 40 && mouseClickPosition.y < 40)
            {
                ToggleFullscreen();
            }
        }
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawRectangle(0, 0, screenWidth, screenHeight, BLACK);
        DrawCircle(0, 0, 40, WHITE);
        EndDrawing();
    }

    return 0;
}
