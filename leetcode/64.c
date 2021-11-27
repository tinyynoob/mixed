
#define min(a,b) (a>b?b:a)

int minPathSum(int** grid, int gridSize, int* gridColSize){
    int i, j;
    for(i=1; i<gridSize; i++)
        grid[i][0]+= grid[i-1][0];  //left
    for(i=1; i<gridColSize[0]; i++)
        grid[0][i]+= grid[0][i-1];  //top
    for(i=1; i<gridSize; i++)
        for(j=1; j<gridColSize[i]; j++)
            grid[i][j]+= min(grid[i-1][j], grid[i][j-1]);
    return grid[gridSize-1][gridColSize[gridSize-1]-1];
}