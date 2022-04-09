#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define DEBUG 0

/* bitwise, branchless solution */
int main()
{
    int row, column;
    scanf("%d %d\n", &row, &column);

    /* ignore failure check after malloc() */
    unsigned char **matrix =
        (unsigned char **) malloc(sizeof(unsigned char *) * (row + 2));
    for (int i = 0; i < row + 2; i++)
        matrix[i] =
            (unsigned char *) malloc(sizeof(unsigned char) * (column + 2));
    /* If we add one layer of extra wall to surround the matrix, then there is
     * no special case, that is, we can traverse in there without exceeding the
     * array. The +1 below are due to the left and top bound we pad.
     */
    int color = -1;  // indicate black/white (chessboard)
    /* read map */
    for (int r = 0; r < row; r++) {
        for (int c = 0; c < column + 1; c++) {
            /* matrix value:
             * 0: wall
             * 1: have not been visited
             * 2: being visited
             * 4: have been visited
             * 8: destination
             * 16: achieved dest
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
                /* init color according to position of source */
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
    uint32_t pioneer = 1;  // if a new place is visited
    uint32_t achieve = 0;  // if the destination B is achieved
    /*--- spreading ---*/
    while (pioneer && !achieve) {
#if DEBUG
        printf("\nAt begining of round: %llu\n", round);
        for (int i = 0; i < row + 2; i++) {
            for (int j = 0; j < column + 2; j++)
                printf("%u", (unsigned) matrix[i][j]);
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
                const unsigned shift = (matrix[r][c] & 2u) >> 1;
                /* If I am in visiting state,
                 * my neightbors: not visited => visiting
                 *                destination => 16
                 */
                uint32_t swar = ((uint32_t) matrix[r][c - 1] << 24) |
                                ((uint32_t) matrix[r][c + 1] << 16) |
                                ((uint32_t) matrix[r - 1][c] << 8) |
                                ((uint32_t) matrix[r + 1][c]);
                swar = ((swar & 0x09090909u) << shift) | (swar & ~0x09090909u);
                matrix[r][c - 1] = swar >> 24;
                matrix[r][c + 1] = swar >> 16;
                matrix[r - 1][c] = swar >> 8;
                matrix[r + 1][c] = swar;
                /* me: visiting => visited */
                matrix[r][c] =
                    ((matrix[r][c] & 2u) << shift) | (matrix[r][c] & ~2u);
                /* update pioneer and achieve */
                pioneer |= swar & 0x02020202u;
                achieve |= swar & 0x10101010u;
            }
#if DEBUG
            printf("pioneer = %d,\n", pioneer);
#endif
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
