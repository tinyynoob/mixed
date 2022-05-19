

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

struct dfs {
    int sequence[4];    // \in [2, 9]
    int len;
    int gening[4];  // \in [0, size[sequence[i]])
    char **out;
    int outSize;
    int used;
};

static char lookup[10][5] = {"", "", "abc", "def", "ghi", 
                        "jkl", "mno", "pqrs", "tuv", "wxyz"};

static int size[10] = {0, 0, 3, 3, 3, 3, 3, 4, 3, 4};

static struct dfs *dfs_init(const char *digits)
{
    struct dfs *d = (struct dfs *) malloc(sizeof(struct dfs));
    d->len = strlen(digits);
    d->outSize = 1;
    for (int i = 0; i < d->len; i++) {
        d->sequence[i] = digits[i] ^ '0';
        d->outSize *= size[d->sequence[i]];
    }
    d->out = (char **) malloc(sizeof(char *) * d->outSize);
    for (int i = 0; i < d->outSize; i++)
        d->out[i] = (char *) calloc(sizeof(char), (d->len + 1));
    d->used = -1;
    return d;
}

static void generate(struct dfs *d, int pos)
{
    if (pos == d->len) {    // end recursion
        ++d->used;
        for (int i = 0; i < d->len; i++)
            d->out[d->used][i] = lookup[d->sequence[i]][d->gening[i]];
        d->out[d->used][d->len] = '\0';
        return;
    }

    for (int i = 0; i < size[d->sequence[pos]]; i++) {
        d->gening[pos] = i;
        generate(d, pos + 1);
    }
}

char ** letterCombinations(char * digits, int* returnSize)
{
    if (digits[0] == '\0') {
        *returnSize = 0;
        return NULL;
    }
    struct dfs *d = dfs_init(digits);
    generate(d, 0);
    *returnSize = d->outSize;
    char **ans = d->out;
    free(d);
    return ans;
}