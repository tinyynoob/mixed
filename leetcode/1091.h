

struct qnode {
    int row;
    int column;
    struct qnode *next;
};

struct queue {
    struct qnode *head;
    struct qnode **tail;
    int size;
};

/* assume the input pixel not traversed
 */
static void enqueue(struct queue *q, int row, int column)
{
    struct qnode *new = (struct qnode *) malloc(sizeof(struct qnode));
    new->row = row;
    new->column = column;
    new->next = NULL;
    *q->tail = new;
    q->tail = &new->next;
    q->size++;
}

static struct qnode *dequeue(struct queue *q)
{
    struct qnode *ret = q->head;
    q->head = q->head->next;
    if (!q->head)
        q->tail = &q->head;
    q->size--;
    return ret;
}

int shortestPathBinaryMatrix(int** grid, int gridSize, int* gridColSize)
{
    if (grid[0][0])
        return -1;
    // surround grid by 1s to prevent access exceeding
    short **closure = (short **) malloc(sizeof(short *) * (gridSize + 2));
    closure[0] = (short *) malloc(sizeof(short) * (gridSize + 2));
    for (int j = 0; j < gridSize + 2; j++)
        closure[0][j] = 1;
    for (int i = 1; i < gridSize + 1; i++) {
        closure[i] = (short *) malloc(sizeof(short) * (gridSize + 2));
        closure[i][0] = 1;
        for (int j = 1; j < gridSize + 1; j++)
            closure[i][j] = grid[i - 1][j - 1];
        closure[i][gridSize + 1] = 1;
    }
    closure[gridSize + 1] = (short *) malloc(sizeof(short) * (gridSize + 2));
    for (int j = 0; j < gridSize + 2; j++)
        closure[gridSize + 1][j] = 1;

    struct queue *q = (struct queue *) malloc(sizeof(struct queue));
    q->head = NULL;
    q->tail = &q->head;
    q->size = 0;
    enqueue(q, 1, 1);
    closure[1][1] = 2; // set to 2 if traversed or cant tranverse
    int ans = 1;
    while (q->head) {
        int sz = q->size;
        for (int i = 0; i < sz; i++) {
            struct qnode *curr = dequeue(q);
            if (curr->row == gridSize && curr->column == gridSize)
                goto end;
            const int dirvec[8][2] = {{-1, -1}, {-1, 0}, {-1, +1}, {0, -1}, {0, +1},
                                      {+1, -1}, {+1, 0}, {+1, +1}};
            for (int i = 0; i < 8; i++) {
                if (!closure[curr->row + dirvec[i][0]][curr->column + dirvec[i][1]])
                    enqueue(q, curr->row + dirvec[i][0], curr->column + dirvec[i][1]);
                closure[curr->row + dirvec[i][0]][curr->column + dirvec[i][1]] = 2;
            }
            free(curr);
        }
        ans++;
    }
    ans = -1;
end:;
    while (q->head) {
        struct qnode *tmp = q->head;
        q->head = q->head->next;
        free(tmp);
    }
    free(q);
    for (int i = 0; i < gridSize + 2; i++)
        free(closure[i]);
    free(closure);
    return ans;
}