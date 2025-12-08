//
// Created by User on 12/8/2025.
//
// faz 1 project

#include <ctype.h>
#include <stdio.h>

int initializeGameMap(int gameMap[12][12], int m, int n, int verticalWalls[12][2], int horizontalWalls[12][2])
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            gameMap[i][j] = '0';
        }
    }

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%c", gameMap[i][j]);
        }
        printf("\n");
    }
    int coreLightX;
    int coreLightY;
    int isget = 0;

    while (isget == 0)
    {
        scanf(" %d %d", &coreLightX, &coreLightY);
        if (coreLightX < 0 || coreLightY < 0 || coreLightX >= m || coreLightY >= n)
        {
            printf("Error: Out of Index [1]\n");
            scanf(" %d %d", &coreLightX, &coreLightY);
        }
        else if (gameMap[coreLightX][coreLightY] == '0')
        {
            gameMap[coreLightX][coreLightY] = 'H';
            isget = 1;
        }
        else
        {
            printf("Error: This is filled [1]\n");
        }
    }

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%c", gameMap[i][j]);
        }
        printf("\n");
    }
    int surveyorCount;
    int x, y;
    isget = 0;
    scanf("%d", &surveyorCount);
    int surveyorLocations[surveyorCount][2];
    for (int i = 0; i < surveyorCount || isget == 0; i++)
    {
        scanf("%d %d", &x, &y);
        if (x >= m || y >= n || x < 0 || y < 0)
        {
            printf("Error: Out of Index [2]\n");
        }
        else if (gameMap[x][y] == '0')
        {
            gameMap[x][y] = 'P';
            surveyorLocations[i][0] = x;
            surveyorLocations[i][1] = y;
            isget = 1;
        }
        else
        {
            printf("Error: This is filled [2]\n");
        }
    }
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%c", gameMap[i][j]);
        }
        printf("\n");
    }
    int shadyCount;

    int r, c;
    isget = 0;
    scanf("%d", &shadyCount);
    int shadyLocations[shadyCount][2];
    for (int i = 0; i < shadyCount || isget == 0; i++)
    {
        scanf("%d %d", &r, &c);
        if (r >= m || c >= n || r < 0 || c < 0)
        {
            printf("Error: Out of Index [3]\n");
        }
        else if (gameMap[r][c] == '0')
        {
            gameMap[r][c] = 'S';
            shadyLocations[i][0] = r;
            shadyLocations[i][1] = c;
            isget = 1;
        }
        else
        {
            printf("Error: This is filled [3]\n");
        }
    }
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%c", gameMap[i][j]);
        }
        printf("\n");
    }
    int countWall;

    scanf("%d", &countWall);

    for (int i = 0; i < countWall; i++)
    {
        int x, y;
        char jahat;
        scanf("%d %d %c", &x, &y, &jahat);

        if (toupper(jahat) == 'H')
        {
            if (x >= m || y >= n - 1 || x < 0 || y < 0)
            {
                printf("Error: Out of Index [4]\n");
                i--;
                continue;
            }
            horizontalWalls[x][y] = 1;
        }
        else if (toupper(jahat) == 'V')
        {
            if (x >= m - 1 || y >= n || x < 0 || y < 0)
            {
                printf("Error: Out of Index [4]\n");
                i--;

                continue;
            }
            verticalWalls[x][y] = 1;
        }
        else
        {
            printf("Error: This is filled [4]\n");
            i--;
        }
    }

    return 0;
}


int printGameMap(char gameMap[12][12], int m, int n, int verticalWalls[12][2], int horizontalWalls[12][2])
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%c", gameMap[i][j]);
            if (verticalWalls[i][j] == 1)
            {
                printf("|");
            }
            else
            {
                printf(" ");
            }
        }
        printf("\n");
        for (int j = 0; j < n - 1; j++)
        {
            if (horizontalWalls[i][j] == 1)
            {
                printf("_");
            }
            else printf(" ");
        }
        printf("\n");
    }
    return 0;
}

// int main()
// {
//     int gameMap[12][12];
//     int gameMapWidth, gameMapHeight;
//     int verticalWalls[gameMapWidth-1][gameMapHeight];
//     int horizontalWalls[gameMapWidth][gameMapHeight-1];
//     scanf("%d %d", &gameMapWidth, &gameMapHeight);
//
//     initializeGameMap(gameMap, gameMapWidth, gameMapHeight, verticalWalls, horizontalWalls);
//
//
//     printGameMap(gameMap, gameMapWidth, gameMapHeight, verticalWalls, horizontalWalls);
// }
