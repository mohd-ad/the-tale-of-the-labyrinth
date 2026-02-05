#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "raylib.h"
#include "functions.c"
#include "string.h"


#define MAX_SIZE 20
#define BLOCK_SIZE 60


int main(void) {
    srand(time(NULL));
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

    Music music = LoadMusicStream("music.mp3");

    PlayMusicStream(music);
    float volume = 0.3f;
    SetMusicVolume(music, volume);

    InitWindow(screenWidth, screenHeight, "TTOTL");

    // TODO: Load resources / Initialize variables at this point
    Texture2D background = LoadTexture("background.jpg");
    Texture2D character = LoadTexture("character.png");
    Texture2D shady = LoadTexture("shady.png");
    Texture2D peace = LoadTexture("peace.png");
    Texture2D peace2 = LoadTexture("peace2.png");
    Texture2D vWall = LoadTexture("vWall.png");
    Texture2D hWall = LoadTexture("hWall.png");


    Texture2D coreLight1 = LoadTexture("core light-1.png");


    Image icon = LoadImage("character.png");
    SetWindowIcon(icon);

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------
    int checkAnimation = 1;
    int yourTurn = 1;
    float turnTimer = 0.0f;
    float turnDelayDuration = 0.5f;
    int aNumber = (screenWidth - BLOCK_SIZE * m) / 2;
    int gameOver = 0;
    char endMessage[50] = "";
    int firstPointUp[2] = {aNumber, (screenHeight - BLOCK_SIZE * n) / 2};

    int startMapV[2] = {firstPointUp[0] + 5, firstPointUp[1] + 5};

    int pPosition[2] = {0, 0};
    char message[200];


    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        checkAnimation *= -1;
        // Update
        //----------------------------------------------------------------------------------
        UpdateMusicStream(music);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(GRAY);
        DrawTexture(background, 0, 0, WHITE);
        // 40 * m = width
        // 40 * n = hegiht


        DrawRectangle(firstPointUp[0] - 7, firstPointUp[1] - 7, BLOCK_SIZE * m + 26, BLOCK_SIZE * n + 26, BLACK);
        DrawRectangle(firstPointUp[0] + 5, firstPointUp[1] + 5, BLOCK_SIZE * m + 2, BLOCK_SIZE * n + 2, GRAY);


        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                DrawRectangle(startMapV[0] + (BLOCK_SIZE * i) + 2, startMapV[1] + (BLOCK_SIZE * j) + 2,
                              itemSize * 2 - 1, itemSize * 2 - 1
                              , WHITE);
            }
        }
        for (int i = 0; i < m - 1; i++) {
            for (int j = 0; j < n; j++) {
                if (verticalWalls[i][j] == 1) {
                    DrawRectangle(startMapV[0] + (BLOCK_SIZE * (i + 1)) - 2, startMapV[1] + (BLOCK_SIZE * j) + 1, 5,
                                  itemSize * 2 + 2, BLACK);
                } else if (verticalWalls[i][j] == 2) {
                    DrawRectangle(startMapV[0] + (BLOCK_SIZE * (i + 1)) - 2, startMapV[1] + (BLOCK_SIZE * j) + 1, 5,
                                  itemSize * 2 + 2, GREEN);
                }
            }
        }

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n - 1; j++) {
                if (horizontalWalls[i][j] == 1) {
                    DrawRectangle(startMapV[0] + (BLOCK_SIZE * i), startMapV[1] + (BLOCK_SIZE * (j + 1)) - 2,
                                  itemSize * 2 + 2,
                                  5, BLACK);
                } else if (horizontalWalls[i][j] == 2) {
                    DrawRectangle(startMapV[0] + (BLOCK_SIZE * i), startMapV[1] + (BLOCK_SIZE * (j + 1)) - 2,
                                  itemSize * 2 + 2,
                                  5, GREEN);
                }
            }
        }
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                char now = toupper(gameMap[i][j]);
                if (now == 'H') {
                    DrawTexture(coreLight1, startMapV[0] + (BLOCK_SIZE * i) + 2, startMapV[1] + (BLOCK_SIZE * j) + 2, WHITE);
                } else if (now == 'P') {
                    pPosition[0] = i;
                    pPosition[1] = j;
                    DrawTexture(character, startMapV[0] + (BLOCK_SIZE * i) + 2, startMapV[1] + (BLOCK_SIZE * j) + 2, WHITE);

                } else if (now == 'S') {
                    DrawTexture(shady, startMapV[0] + (BLOCK_SIZE * i) + 2, startMapV[1] + (BLOCK_SIZE * j) + 2, WHITE);
                }
            }
        }

        if (yourTurn && strcmp(message, "You can't go there!") == 0) {
            DrawText(message, 430, 700, 36, RED);
        } else if (yourTurn) {
            DrawText("Your turn!\nPress SPACE for skip your turn.", 330, 700, 36, WHITE);
        } else {
            DrawText("Wait ...", 430, 700, 36, RED);
        }
        int surveyorCountOnMap = 0;
        int surveyorOnCoreLight = 0;
        int shadyOnSurveyor = 0;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                char cell = toupper(gameMap[i][j]);
                if (cell == 'P') surveyorCountOnMap++;
            }
        }

        if (surveyorCountOnMap == 0 && gameOver == 0) {
            gameOver = 1;
            strcpy(endMessage, "GAME OVER! All surveyors lost.");
        }
        if (gameOver != 0) {
            DrawRectangle(0, 0, screenWidth, screenHeight, Fade(BLACK, 0.8f));
            DrawText(endMessage, screenWidth / 2 - MeasureText(endMessage, 40) / 2, screenHeight / 2, 40,
                     (gameOver == 2) ? GREEN : RED);
            DrawText("Press ESC to Exit", screenWidth / 2 - MeasureText("Press ESC to Exit", 20) / 2,
                     screenHeight / 2 + 60, 20, WHITE);

            yourTurn = 0;
        }

        EndDrawing();

        if ((IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) && yourTurn) {
            if (checkWallAround(m, n, verticalWalls, horizontalWalls, pPosition[0], pPosition[1], "UP")) {
                strcpy(message, "You can't go there!");
            } else {
                if (gameMap[pPosition[0]][pPosition[1] - 1] == 'H') {
                    gameOver = 2;
                    strcpy(endMessage, "YOU WIN! Reached Core Light.");
                } else if (gameMap[pPosition[0]][pPosition[1] - 1] == 'S') {
                    gameOver = 1;
                    strcpy(endMessage, "GAME OVER! Do you want to eat shady?");
                }
                gameMap[pPosition[0]][pPosition[1]] = '0';
                pPosition[1]--;
                gameMap[pPosition[0]][pPosition[1]] = 'P';
                yourTurn = 0;
            }
            turnTimer = turnDelayDuration;
        } else if ((IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) && yourTurn) {
            if (checkWallAround(m, n, verticalWalls, horizontalWalls, pPosition[0], pPosition[1], "DOWN")) {
                strcpy(message, "You can't go there!");
            } else {
                if (gameMap[pPosition[0]][pPosition[1] + 1] == 'H') {
                    gameOver = 2;
                    strcpy(endMessage, "YOU WIN! Reached Core Light.");
                } else if (gameMap[pPosition[0]][pPosition[1] + 1] == 'S') {
                    gameOver = 1;
                    strcpy(endMessage, "GAME OVER! Do you want to eat shady?");
                }
                gameMap[pPosition[0]][pPosition[1]] = '0';
                pPosition[1]++;
                gameMap[pPosition[0]][pPosition[1]] = 'P';
                yourTurn = 0;
            }
            turnTimer = turnDelayDuration;
        } else if ((IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) && yourTurn) {
            if (checkWallAround(m, n, verticalWalls, horizontalWalls, pPosition[0], pPosition[1], "LEFT")) {
                strcpy(message, "You can't go there!");
            } else {
                if (gameMap[pPosition[0] - 1][pPosition[1]] == 'H') {
                    gameOver = 2;
                    strcpy(endMessage, "YOU WIN! Reached Core Light.");
                } else if (gameMap[pPosition[0] - 1][pPosition[1]] == 'S') {
                    gameOver = 1;
                    strcpy(endMessage, "GAME OVER! Do you want to eat shady?");
                }
                gameMap[pPosition[0]][pPosition[1]] = '0';
                pPosition[0]--;
                gameMap[pPosition[0]][pPosition[1]] = 'P';
                yourTurn = 0;
            }
            turnTimer = turnDelayDuration;
        } else if ((IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) && yourTurn) {
            if (checkWallAround(m, n, verticalWalls, horizontalWalls, pPosition[0], pPosition[1], "RIGHT")) {
                strcpy(message, "You can't go there!");
            } else {
                if (gameMap[pPosition[0] + 1][pPosition[1]] == 'H') {
                    gameOver = 2;
                    strcpy(endMessage, "YOU WIN! Reached Core Light.");
                } else if (gameMap[pPosition[0] + 1][pPosition[1]] == 'S') {
                    gameOver = 1;
                    strcpy(endMessage, "GAME OVER! Do you want to eat shady?");
                }
                gameMap[pPosition[0]][pPosition[1]] = '0';
                pPosition[0]++;
                gameMap[pPosition[0]][pPosition[1]] = 'P';
                yourTurn = 0;
            }
            turnTimer = turnDelayDuration;
        } else if (IsKeyPressed(KEY_SPACE)) {
            yourTurn = 0;
            turnTimer = turnDelayDuration;
        }


        if (!yourTurn && gameOver != 2) {
            if (turnTimer > 0) {
                turnTimer -= GetFrameTime();
            } else {
                int shadyPositions[MAX_SIZE * MAX_SIZE][2];
                int shadyCount = 0;

                for (int i = 0; i < m; i++) {
                    for (int j = 0; j < n; j++) {
                        if (gameMap[i][j] == 'S') {
                            shadyPositions[shadyCount][0] = i;
                            shadyPositions[shadyCount][1] = j;
                            shadyCount++;
                        }
                    }
                }

                for (int k = 0; k < shadyCount; k++) {
                    int sx = shadyPositions[k][0];
                    int sy = shadyPositions[k][1];

                    int nextX = sx;
                    if (pPosition[0] > sx) nextX = sx + 1;
                    else if (pPosition[0] < sx) nextX = sx - 1;

                    if (nextX != sx) {
                        char target = gameMap[nextX][sy];
                        if (!checkWallAround(m, n, verticalWalls, horizontalWalls, sx, sy,
                                             (nextX > sx ? "RIGHT" : "LEFT"))) {
                            if (target == '0' || target == 'P') {
                                gameMap[sx][sy] = '0';
                                if (target == 'P') {
                                    gameOver = 1;
                                    strcpy(endMessage, "GAME OVER! Shady caught a surveyor.");
                                }
                                sx = nextX;
                                gameMap[sx][sy] = 'S';
                            }
                        }
                    }

                    int nextY = sy;
                    if (pPosition[1] > sy) nextY = sy + 1;
                    else if (pPosition[1] < sy) nextY = sy - 1;

                    if (nextY != sy && gameOver == 0) {
                        char target = gameMap[sx][nextY];
                        if (!checkWallAround(m, n, verticalWalls, horizontalWalls, sx, sy,
                                             (nextY > sy ? "DOWN" : "UP"))) {
                            if (target == '0' || target == 'P') {
                                gameMap[sx][sy] = '0';
                                if (target == 'P') {
                                    gameOver = 1;
                                    strcpy(endMessage, "GAME OVER! Shady caught a surveyor.");
                                }
                                sy = nextY;
                                gameMap[sx][sy] = 'S';
                            }
                        }
                    }
                }
                yourTurn = 1;
                turnTimer = 0;
            }
        }
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(character);
    UnloadTexture(shady);
    UnloadTexture(peace);
    UnloadTexture(background);
    UnloadMusicStream(music);
    CloseAudioDevice();
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
