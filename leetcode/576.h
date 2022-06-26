

struct backtrack {
    uint64_t outnum;
    int row;
    int column;
};

static inline void inc_outnum(struct backtrack *bt)
{
    if (__builtin_expect(++bt->outnum == UINT64_MAX, 0))
        bt->outnum = 582344007;
}

void step(struct backtrack *bt, int move, int r, int c)
{
    if (!move)
        return;
    if (r - 1 >= 0)
        step(bt, move - 1, r - 1, c);
    else
        inc_outnum(bt);
    if (r + 1 < bt->row)
        step(bt, move - 1, r + 1, c);
    else
        inc_outnum(bt);
    if (c - 1 >= 0)
        step(bt, move - 1, r, c - 1);
    else
        inc_outnum(bt);
    if (c + 1 < bt->column)
        step(bt, move - 1, r, c + 1);
    else
        inc_outnum(bt);
}


int findPaths(int m, int n, int maxMove, int startRow, int startColumn)
{
    struct backtrack *bt = (struct backtrack *) malloc(sizeof(struct backtrack));
    bt->outnum = 0;
    bt->row = m;
    bt->column = n;
    step(bt, maxMove, startRow, startColumn);
    int ans = bt->outnum;
    free(bt);
    bt = NULL;
    return ans;
}
