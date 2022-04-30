#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG 0

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

#define SIZE 231  // 231 = \binom{11}{3} + \binom{11}{2} + \binom{11}{1}

struct split {
    short dot[SIZE][3];  // record position of the dots
    bool valid[SIZE];
    int used;
};

/* try to split @s to @remain of 0~255 number
 *
 */
static void insert_dots(struct split *sp, const char *s, int start, int remain)
{
    const char *mys = s + start;
    const int parent = sp->used;
#if DEBUG
    if (parent == -1)  // no parent
        puts("I am the first.");
    else
        printf("My parent is: [0] = %d, [1] = %d, [2] = %d\n",
               sp->dot[parent][0], sp->dot[parent][1], sp->dot[parent][2]);
#endif
    if (remain == 0) {  // check validity of the address
        if (mys[0] == '\0')
            sp->valid[parent] = false;
        else if (mys[0] == '0' && mys[1] != '\0')
            sp->valid[parent] = false;
        else if (strlen(mys) > 3)
            sp->valid[parent] = false;
        else if (atoi(mys) > 255)
            sp->valid[parent] = false;
        else
            sp->valid[parent] = true;
        return;
    }

    // remain \in \{1, 2, 3\}
    int len = strlen(mys);
    // consume 1 digit
    if (len < 1)
        return;
    sp->used++;
    for (int i = 0; i < 3 - remain; i++)
        sp->dot[sp->used][i] = sp->dot[parent][i];
    sp->dot[sp->used][3 - remain] = start + 1;
    sp->valid[sp->used] = false;
    insert_dots(sp, s, start + 1, remain - 1);
    // consume 2 digits
    if (len < 2)
        return;
    if (mys[0] == '0')
        return;
    sp->used++;
    for (int i = 0; i < 3 - remain; i++)
        sp->dot[sp->used][i] = sp->dot[parent][i];
    sp->dot[sp->used][3 - remain] = start + 2;
    sp->valid[sp->used] = false;
    insert_dots(sp, s, start + 2, remain - 1);
    // consume 3 digits
    if (len < 3)
        return;
    char sub[4];
    sub[0] = mys[0];
    sub[1] = mys[1];
    sub[2] = mys[2];
    sub[3] = '\0';
    if (atoi(sub) > 255)
        return;
    sp->used++;
    for (int i = 0; i < 3 - remain; i++)
        sp->dot[sp->used][i] = sp->dot[parent][i];
    sp->dot[sp->used][3 - remain] = start + 3;
    sp->valid[sp->used] = false;
    insert_dots(sp, s, start + 3, remain - 1);
}

char **restoreIpAddresses(char *s, int *returnSize)
{
    *returnSize = 0;
    if (strlen(s) < 4)
        return NULL;
    struct split *sp = (struct split *) malloc(sizeof(struct split));
    sp->used = -1;
    insert_dots(sp, (const char *) s, 0, 3);
    int valid_index[SIZE];
    for (int i = 0; i <= sp->used; i++) {
#if DEBUG
        printf("i = %d, bool %d, *returnSize = %d\n", i, sp->valid[i],
               *returnSize);
#endif
        if (sp->valid[i])
            valid_index[(*returnSize)++] = i;
    }
    char **ans = (char **) malloc(sizeof(char *) * *returnSize);
    for (int i = 0; i < *returnSize; i++) {
        ans[i] = (char *) malloc(sizeof(char) * (strlen(s) + 3 + 1));
        ans[i][sp->dot[valid_index[i]][0]] = '.';
        ans[i][sp->dot[valid_index[i]][1] + 1] = '.';
        ans[i][sp->dot[valid_index[i]][2] + 2] = '.';
        ans[i][strlen(s) + 3] = '\0';
        int index = 0;
        for (int j = 0; j < strlen(s); j++) {
            if (ans[i][index] == '.')
                index++;
            ans[i][index++] = s[j];
        }
    }
    free(sp);
    return ans;
}
