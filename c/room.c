#include <stdio.h>

/* [left, right) */
struct interval {
    int left;
    int right;
    int room;  // the interval belongs to which room
};

static inline int overlap(struct interval above, struct interval below)
{
    if (above.right <= below.left || above.left >= below.right)
        return 0;
    return 1;
}

int main()
{
    int row, column;
    scanf("%d %d\n", &row, &column);
    // printf("%d, %d\n", row, column);
    const int max_inter =
        (column + 1) / 2;  // max possible number of interval in a single line

    int ans = 0, room_counter = 0;
    struct interval above[max_inter], this[max_inter];  // above row, this row
    int index = -1;                  // indicates index of this[]
    for (int r = 0; r < row; r++) {  // scan through lines
        /* updates above */
        const int above_inter_num = index + 1;
        for (int i = 0; i < above_inter_num; i++) {
            above[i].left = this[i].left;
            above[i].right = this[i].right;
            above[i].room = this[i].room;
        }
        index = -1;  // reset index

        /* loop for reading and processing a line */
        int c = 0;
        while (c < column + 1) {    // +1 to include '\n'
            int input = getchar();  // declare as int to contain EOF
            switch (input) {
            case '#':
            case '\n':
            case EOF:
                c++;
                break;
            case '.':
                index++;
                this[index].left = c++;
                while ((input = getchar()) == '.')
                    c++;
                // @input is currently either '\n' or '#'
                this[index].right = c++;

                this[index].room = -1;
                for (int i = 0; i < above_inter_num; i++) {
                    if (overlap(above[i],
                                this[index])) {  // it belongs to an old room
                        if (this[index].room == -1) {
                            this[index].room = above[i].room;
                        } else if (above[i].room != above[i - 1].room) {
                            above[i].room =
                                above[i - 1].room;  // merge two old rooms
                            ans--;
                        }
                    }
                }
                if (this[index].room == -1) {
                    this[index].room = room_counter++;  // creates a new room
                    ans++;
                }
                break;
            default:
                perror("invalid input\n");
                return 1;
            }
        }
        // printf("ans = %d after processing row %d\n", ans, r);
    }
    printf("%d\n", ans);
    return 0;
}
