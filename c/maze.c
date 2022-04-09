#include <stdio.h>
#include <stdlib.h>

#define DEBUG 1

int main()
{
    int row, column;
    scanf("%d %d\n", &row, &column);

    /* ignore failure check after malloc() */
    /* note that short type has at least 16 bits */
    unsigned short **matrix =
        (unsigned short **) malloc(sizeof(unsigned short *) * (row + 2));
    for (int i = 0; i < row + 2; i++)
        matrix[i] =
            (unsigned short *) malloc(sizeof(unsigned short) * (column + 2));
    /* If we surround the matrix by walls, then there is no special case, that
     * is, we do not have to check array exceeding.
     * The +1 below are due to the bound we pad.
     */
    int color = -1;  // indicate black/white (chessboard) at source
    /* read map */
    for (int r = 0; r < row; r++) {
        for (int c = 0; c < column + 1; c++) {
            /* matrix value:
             * 0: wall
             * 1: have not been visited
             * 2,3: being visited
             * 4,7,6: have been visited, 6 is source
             * 8: destination
             */
            int get = getchar();
            switch (get) {
            case '\n':
            case EOF:
                break;
            case '#':
                matrix[r + 1][c + 1] = 0;
                break;
            case '.':
                matrix[r + 1][c + 1] = 1;
                break;
            case 'A':
                matrix[r + 1][c + 1] = 2;
                color = (r ^ c) & 1;  // = ((r+1) ^ (c+1)) & 1
                break;
            case 'B':
                matrix[r + 1][c + 1] = 8;
                break;
            default:
                perror("Invalid input!\n");
                exit(1);
            }
        }
        matrix[r + 1][column + 1] = 0;
        matrix[r + 1][0] = 0;
    }
    for (int c = 0; c < column + 2; c++) {
        matrix[0][c] = 0;
        matrix[row + 1][c] = 0;
    }
    /* end read map */
    if (color == -1) {
        perror("no starting point!\n");
        exit(1);
    }

    unsigned long long round = 0;
    int pioneer = 1;  // if a new place is visited
    int achieve = 0;  // if the destination B is achieved
    /*--- spreading ---*/
    while (pioneer && !achieve) {
#if DEBUG
        printf("\nAt begining of round: %llu\n", round);
        for (int i = 0; i < row + 2; i++) {
            for (int j = 0; j < column + 2; j++)
                printf("%hu", matrix[i][j]);
            putchar('\n');
        }
#endif
        pioneer = 0;
        int c = color + 1;
        /* go through chess grid (black/white grid) */
        for (int r = 1; r < row + 1;
             r++, c = (c & 1) ? 2 : 1) {  // c switches between even and odd
#if DEBUG
            printf("r = %d, c = %d\n", r, c);
#endif
            for (; c < column + 1; c += 2) {
                /* I am matrix[r][c].
                 * If I am in visiting state, shift = 1
                 * Otherwise, shift = 0
                 */
                const unsigned short shift = (matrix[r][c] & 2) >> 1;
                /* If I am in visiting state,
                 * my neightbors: not visited => visiting
                 *                destination => 16
                 */
                matrix[r][c - 1] |= (matrix[r][c - 1] & 0x9) << shift;
                matrix[r][c + 1] |= (matrix[r][c + 1] & 0x9) << shift;
                matrix[r - 1][c] |= (matrix[r - 1][c] & 0x9) << shift;
                matrix[r + 1][c] |= (matrix[r + 1][c] & 0x9) << shift;
                /* me: visiting => visited */
                matrix[r][c] |= (matrix[r][c] & 2) << shift;
                /* update pioneer and achieve */
                pioneer |= matrix[r][c - 1] & 2;
                pioneer |= matrix[r][c + 1] & 2;
                pioneer |= matrix[r - 1][c] & 2;
                pioneer |= matrix[r + 1][c] & 2;
                achieve |= matrix[r][c - 1] & 16;
                achieve |= matrix[r][c + 1] & 16;
                achieve |= matrix[r - 1][c] & 16;
                achieve |= matrix[r + 1][c] & 16;
            }
        }
        round++;
        /* switch to another color */
        color ^= 1;
#if DEBUG
        printf("achieve = %d  after this round\n", achieve);
#endif
    }
    for (int i = 0; i < row + 2; i++)
        free(matrix[i]);
    free(matrix);

    if (achieve)
        printf("YES\n%llu\n", round);
    else
        puts("NO");  // puts() contains '\n'
    return 0;
}
