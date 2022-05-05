
static inline void cycle(int *movr, int *movc)
{
    int temp = *movr;
    *movr = *movc;
    *movc = temp * (-1);
}

void rotate(int** matrix, int matrixSize, int* matrixColSize)
{
    for (int layer = 0; layer < (matrixSize + 1) / 2; layer++) {
        int movr = 0, movc = matrixSize - 2 * layer - 1;
        int r = layer, c = layer;
        while (movr < matrixSize - 2 * layer - 1) {
            int after = matrix[r][c];
            int before = matrix[r][c];
            for (int i = 0; i < 4; i++) {
                after = before;
                before = matrix[r + movr][c + movc];
                matrix[r + movr][c + movc] = after;
                r = r + movr;
                c = c + movc;
                cycle(&movr, &movc);
            }
            // back to origin movr, movc
            movc--;
            movr++;
            c++;
        }
    }
}