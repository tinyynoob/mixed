

int uniquePathsWithObstacles(int** obstacleGrid, int obstacleGridSize, int* obstacleGridColSizea)
{
    obstacleGrid[0][0] = !obstacleGrid[0][0];
    for (int i = 1; i < obstacleGridSize; i++) {
        if (obstacleGrid[i][0])
            obstacleGrid[i][0] = 0;
        else
            obstacleGrid[i][0] = obstacleGrid[i - 1][0];
    }
    for (int i = 1; i < obstacleGridColSizea[0]; i++) {
        if (obstacleGrid[0][i])
            obstacleGrid[0][i] = 0;
        else
            obstacleGrid[0][i] = obstacleGrid[0][i - 1];
    }
    for (int r = 1; r < obstacleGridSize; r++) {
        for(int c = 1; c < obstacleGridColSizea[0]; c++) {
            if (obstacleGrid[r][c])
                obstacleGrid[r][c] = 0;
            else
                obstacleGrid[r][c] = obstacleGrid[r][c - 1] + obstacleGrid[r - 1][c];
        }
    }
    return obstacleGrid[obstacleGridSize - 1][obstacleGridColSizea[0] - 1];
}