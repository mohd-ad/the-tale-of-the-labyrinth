//
// Created by User on 12/8/2025.
//
// faz 1 project

#include <ctype.h>
#include <stdio.h>

#define MAX_SIZE 20


int initializeGameMap(char gameMap[MAX_SIZE][MAX_SIZE], int m, int n,
                      int verticalWalls[MAX_SIZE][MAX_SIZE], int horizontalWalls[MAX_SIZE][MAX_SIZE]) {
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            gameMap[i][j] = '0';
        }
    }
    int coreLightX;
    int coreLightY;

    while (1) {
        scanf(" %d %d", &coreLightX, &coreLightY);
        if (coreLightX < 0 || coreLightY < 0 || coreLightX >= m || coreLightY >= n) {
            printf("Error: Out of Index [1]\n");
        } else if (gameMap[coreLightX][coreLightY] == '0') {
            gameMap[coreLightX][coreLightY] = 'H';
            break;
        } else {
            printf("Error: This is filled [1]\n");
        }
    }

    int surveyorCount;
    scanf("%d", &surveyorCount);
    int surveyorLocations[surveyorCount][2];

    for (int i = 0; i < surveyorCount; i++) {
        int x, y;
        while (1) {
            scanf("%d %d", &x, &y);
            if (x >= m || y >= n || x < 0 || y < 0) {
                printf("Error: Out of Index [2]\n");
            } else if (gameMap[x][y] == '0') {
                gameMap[x][y] = 'P';
                surveyorLocations[i][0] = x;
                surveyorLocations[i][1] = y;
                break;
            } else {
                printf("Error: This is filled [2]\n");
            }
        }
    }
    int shadyCount;

    scanf("%d", &shadyCount);
    int shadyLocations[shadyCount][2];
    for (int i = 0; i < shadyCount; i++) {
        int r, c;
        while (1) {
            scanf("%d %d", &r, &c);
            if (r >= m || c >= n || r < 0 || c < 0) {
                printf("Error: Out of Index [3]\n");
            } else if (gameMap[r][c] == '0') {
                gameMap[r][c] = 'S';
                shadyLocations[i][0] = r;
                shadyLocations[i][1] = c;
                break;
            } else {
                printf("Error: This is filled [3]\n");
            }
        }
    }

    int countWall;

    scanf("%d", &countWall);

    for (int i = 0; i < countWall; i++) {
        int x, y;
        char jahat;
        scanf("%d %d %c", &x, &y, &jahat);

        if (toupper(jahat) == 'H') {
            if (x >= m || y >= n - 1 || x < 0 || y < 0) {
                printf("Error: Out of Index [4]\n");
                i--;
                continue;
            }
            horizontalWalls[x][y] = 1;
        } else if (toupper(jahat) == 'V') {
            if (x >= m - 1 || y >= n || x < 0 || y < 0) {
                printf("Error: Out of Index [4]\n");
                i--;

                continue;
            }
            verticalWalls[x][y] = 1;
        } else {
            printf("Error: This is filled [4]\n");
            i--;
        }
    }

    return 0;
}

