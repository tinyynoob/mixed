#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROW 100
#define COLUMN 100

int main()
{
    printf("%d %d\n", ROW, COLUMN);
    srand(time(NULL));
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COLUMN; j++) {
            char c = rand() & 1 ? '#' : '.';
            putchar(c);
        }
        putchar('\n');
    }
    return 0;
}