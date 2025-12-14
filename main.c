#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "functions.c"


#define MAX_SIZE 20
#define BLOCK_SIZE 60


int main(void) {
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 1000;
    int screenHeight = 800;
    int itemSize = BLOCK_SIZE / 2 - 1;
    int offset = BLOCK_SIZE / 2 + 1;

    int m, n;
    scanf("%d", &m);
    scanf("%d", &n);
    if (m > MAX_SIZE || n > MAX_SIZE || m <= 3 || n <= 3) {
        printf("Error: Grid size must be between 3 and %d\n", MAX_SIZE);
        return -1;
    }

    char gameMap[MAX_SIZE][MAX_SIZE];
    // Verticals are m-1, n
    int verticalWalls[MAX_SIZE][MAX_SIZE];
    // Horizontals are m, n-1
    int horizontalWalls[MAX_SIZE][MAX_SIZE];

    for (int i = 0; i < MAX_SIZE; i++) {
        for (int j = 0; j < MAX_SIZE; j++) {
            gameMap[i][j] = '0';
            verticalWalls[i][j] = 0;
            horizontalWalls[i][j] = 0;
        }
    }

    initializeGameMap(gameMap, m, n, verticalWalls, horizontalWalls);
    InitAudioDevice();

    Music music = LoadMusicStream("music.ogg");

    PlayMusicStream(music);
    float volume = 0.3f;
    SetMusicVolume(music, volume);

    InitWindow(screenWidth, screenHeight, "TTOTL");

    // TODO: Load resources / Initialize variables at this point
    Texture2D background = LoadTexture("background.jpg");

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        UpdateMusicStream(music);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawTexture(background, 0, 0, WHITE);
        // 40 * m = width
        // 40 * n = hegiht
        int aNumber = (screenWidth - BLOCK_SIZE * m) / 2;
        int firstPointUp[2] = {aNumber, (screenHeight - BLOCK_SIZE * n) / 2};

        DrawRectangle(firstPointUp[0], firstPointUp[1], BLOCK_SIZE * m + 13, BLOCK_SIZE * n + 13, BLACK);
        DrawRectangle(firstPointUp[0] + 5, firstPointUp[1] + 5, BLOCK_SIZE * m + 2, BLOCK_SIZE * n + 2, GRAY);


        int startMapV[2] = {firstPointUp[0] + 5, firstPointUp[1] + 5};

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                DrawRectangle(startMapV[0] + (BLOCK_SIZE * i) + 2, startMapV[1] + (BLOCK_SIZE * j) + 2,
                              itemSize * 2 - 1, itemSize * 2 - 1, WHITE);
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m-1; j++) {
                if (verticalWalls[i][j] == 1) {
                    DrawRectangle(startMapV[0] + (BLOCK_SIZE * (j+1))-2, startMapV[1] + (BLOCK_SIZE * i) + 1, 5,
                                  itemSize * 2 + 2, BLACK);
                }
            }
        }
        for (int i = 0; i < n-1; i++) {
            for (int j = 0; j < m; j++) {
                if (horizontalWalls[i][j] == 1) {
                    DrawRectangle(startMapV[0] + (BLOCK_SIZE * j), startMapV[1] + (BLOCK_SIZE * (i+1)) -2, itemSize * 2 + 2,
                                  5, BLACK);
                }
            }
        }
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                char now = toupper(gameMap[i][j]);
                if (now == 'H') {
                    DrawRectangle(startMapV[0] + (BLOCK_SIZE * j) + 2, startMapV[1] + (BLOCK_SIZE * i) + 2,
                                  itemSize * 2 - 1, itemSize * 2 - 1, YELLOW);
                } else if (now == 'P') {
                    DrawCircle(startMapV[0] + (BLOCK_SIZE * j) + offset-1,
                               startMapV[1] + (BLOCK_SIZE * i) + BLOCK_SIZE / 2, itemSize, RED);
                } else if (now == 'S') {
                    DrawCircle(startMapV[0] + (BLOCK_SIZE * j) + offset-1,
                               startMapV[1] + (BLOCK_SIZE * i) + BLOCK_SIZE / 2, itemSize, BLUE);
                }
            }
        }



        EndDrawing();

        if (IsKeyDown(KEY_UP)) {
        }
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------

    UnloadTexture(background);
    UnloadMusicStream(music);
    CloseAudioDevice();
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
