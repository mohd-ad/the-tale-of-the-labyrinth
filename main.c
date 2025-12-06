#include "raylib.h"
#include <stdio.h>

int main(void)
{

    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 800;
    int screenHeight = 450;

    scanf("%d", &screenWidth);
    scanf("%d", &screenHeight);

    InitWindow(screenWidth, screenHeight, "TTOTL");

    // TODO: Load resources / Initialize variables at this point

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update variables / Implement example logic at this point
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RED);

        // TODO: Draw everything that requires to be drawn at this point

        DrawLineEx((Vector2){ 0, 0 }, (Vector2){ screenWidth, screenHeight }, 2.0f, RED);
        DrawLineEx((Vector2){ 0, screenHeight }, (Vector2){ screenWidth, 0 }, 2.0f, RED);
        DrawText("example base code template", 260, 400, 20, LIGHTGRAY);

        DrawText("This is Black!", screenWidth/3, screenHeight/2, 40, BLACK);
        EndDrawing();


        if (IsKeyDown(KEY_UP))
        {

        }
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------

    // TODO: Unload all loaded resources at this point

    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}