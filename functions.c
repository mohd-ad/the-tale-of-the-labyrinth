#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 20

int cRand(int min, int max)
{
    return (rand() % (max - min + 1)) + min;
}

int canMove(int x1, int y1, int x2, int y2, int m, int n,
            int verticalWalls[MAX_SIZE][MAX_SIZE],
            int horizontalWalls[MAX_SIZE][MAX_SIZE])
{
    if (x2 < 0 || x2 >= m || y2 < 0 || y2 >= n)
        return 0;

    if (x2 == x1 && y2 == y1 + 1) return horizontalWalls[x1][y1] == 0;
    if (x2 == x1 && y2 == y1 - 1) return horizontalWalls[x1][y2] == 0;
    if (x2 == x1 + 1 && y2 == y1) return verticalWalls[x1][y1] == 0;
    if (x2 == x1 - 1 && y2 == y1) return verticalWalls[x2][y1] == 0;

    return 0;
}

int checkWalls(int m, int n,
               int verticalWalls[MAX_SIZE][MAX_SIZE],
               int horizontalWalls[MAX_SIZE][MAX_SIZE])
{
    int visited[MAX_SIZE][MAX_SIZE] = {0};

    int queue[MAX_SIZE * MAX_SIZE][2];
    int front = 0;
    int rear = 0;

    int startX = 0, startY = 0;

    queue[rear][0] = startX;
    queue[rear][1] = startY;
    rear++;

    visited[startX][startY] = 1;
    int visitedCount = 1;

    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    while (front < rear)
    {
        int currentX = queue[front][0];
        int currentY = queue[front][1];
        front++;

        for (int dir = 0; dir < 4; dir++)
        {
            int newX = currentX + dx[dir];
            int newY = currentY + dy[dir];

            if (newX >= 0 && newX < m && newY >= 0 && newY < n &&
                !visited[newX][newY] &&
                canMove(currentX, currentY, newX, newY, m, n,
                        verticalWalls, horizontalWalls))
            {
                visited[newX][newY] = 1;
                visitedCount++;

                queue[rear][0] = newX;
                queue[rear][1] = newY;
                rear++;
            }
        }
    }


    if (visitedCount == m * n)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int initializeGameMap(char gameMap[MAX_SIZE][MAX_SIZE], int m, int n,
                      int verticalWalls[MAX_SIZE][MAX_SIZE], int horizontalWalls[MAX_SIZE][MAX_SIZE])
{
    for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j < 12; j++)
        {
            gameMap[i][j] = '0';
        }
    }


    while (1)
    {
        int coreLightX = cRand(0, m - 1);
        int coreLightY = cRand(0, n - 1);
        if (gameMap[coreLightX][coreLightY] == '0')
        {
            gameMap[coreLightX][coreLightY] = 'H';
            break;
        }
        else
        {
            printf("Error: This is filled [1]\n");
        }
    }

    int surveyorCount;
    scanf("%d", &surveyorCount);
    int surveyorLocations[surveyorCount][2];

    for (int i = 0; i < surveyorCount; i++)
    {
        while (1)
        {
            int x = cRand(0, m - 1);
            int y = cRand(0, n - 1);

            if (x >= m || y >= n || x < 0 || y < 0)
            {
                printf("Error: Out of Index [2]\n");
            }
            else if (gameMap[x][y] == '0')
            {
                gameMap[x][y] = 'P';
                surveyorLocations[i][0] = x;
                surveyorLocations[i][1] = y;
                break;
            }
            else
            {
                printf("Error: This is filled [2]\n");
            }
        }
    }
    int shadyCount;

    scanf("%d", &shadyCount);
    int shadyLocations[shadyCount][2];
    for (int i = 0; i < shadyCount; i++)
    {
        while (1)
        {
            int r = cRand(0, m - 1);
            int c = cRand(0, n - 1);

            if (r >= m || c >= n || r < 0 || c < 0)
            {
                printf("Error: Out of Index [3]\n");
            }
            else if (gameMap[r][c] == '0')
            {
                gameMap[r][c] = 'S';
                shadyLocations[i][0] = r;
                shadyLocations[i][1] = c;
                break;
            }
            else
            {
                printf("Error: This is filled [3]\n");
            }
        }
    }

    int countWall;

    scanf("%d", &countWall);

    do
    {
        for (int i = 0; i < MAX_SIZE; i++)
        {
            for (int j = 0; j < MAX_SIZE; j++)
            {
                verticalWalls[i][j] = 0;
                horizontalWalls[i][j] = 0;
            }
        }

        int vWallCount = cRand(0, countWall);
        int hWallCount = countWall - vWallCount;
        printf("%d", vWallCount);
        printf("\n");
        printf("%d\n", hWallCount);
        int count = 0;

        int i = 0;
        while (i < vWallCount && count <= countWall)
        {
            int x = cRand(0, m - 2);
            int y = cRand(0, n - 1);

            if (verticalWalls[x][y] == 1)
            {
                continue;
            }
            else
            {
                verticalWalls[x][y] = 1;
                i++;
                count++;
            }
        }

        i = 0;
        while (i < hWallCount && count <= countWall)
        {
            int x = cRand(0, m - 1);
            int y = cRand(0, n - 2);

            if (horizontalWalls[x][y] == 1)
            {
                continue;
            }
            else
            {
                horizontalWalls[x][y] = 1;
                i++;
                count++;
            }
        }
    }
    while (checkWalls(m, n, verticalWalls, horizontalWalls));


    return 0;
}
