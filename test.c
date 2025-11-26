/*#========================================================================#*/
#include <stdio.h>


/*#==========================Global Variables======================+=======#*/
int boardWidth, boardHeight;
int coreLightPosX, coreLightPosY;
int surveyorCount;
int surveyorPos[2][2];
int shadyCount;
int shadyPos[1][2];
int wallCount;
int wallPos[1000][3];


/*#==========================Another Functions=============================#*/
void getInformation()
{
    scanf("%d %d", &boardWidth, &boardHeight);
    scanf("%d %d", &coreLightPosX, &coreLightPosY);
    scanf("%d", &surveyorCount);
    for (int i = 0; i < surveyorCount; i++)
        scanf("%d %d", &surveyorPos[i][0], &surveyorPos[i][1]);

    scanf("%d", &shadyCount);
    for (int i = 0; i < shadyCount; i++)
        scanf("%d %d", &shadyPos[i][0], &shadyPos[i][1]);
    scanf("%d", &wallCount);
    for (int i = 0; i < wallCount; i++)
        scanf("%d %d %d", &wallPos[i][0], &wallPos[i][1], &wallPos[i][2]);
}

void updateBoard(char &boardGame[boardWidth][boardHeight])
{
    for (int x = 0; x < boardWidth; x++)
    {
        for (int y = 0; y < boardHeight; y++)
        {
            printf("%c ", boardGame[x][y]);
        }
        printf("\n");
    }
}
/*#============================main Function===============================#*/

int main()
{
    getInformation();

    char boardGame[boardWidth][boardHeight];

    int nextAction;

    while (1)
    {
        updateBoard(boardGame);
        scanf("%s", &nextAction);
    }
    return 0;
}
