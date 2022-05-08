#include <stdlib.h>
#include <stdbool.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

/* enqueue at tail and dequeue at head
 */
struct queue {
    struct qnode *head;
    struct qnode **tail;    // **tail == NULL
    int size;
};

struct qnode {
    struct TreeNode *node;
    struct qnode *next;
};

static struct queue *queue_init()
{
    struct queue *q = (struct queue *) malloc(sizeof(struct queue));
    q->head = NULL;
    q->tail = &q->head;
    q->size = 0;
    return q;
}

static inline bool queue_size(struct queue *q)
{
    return q->size;
}

static void enqueue(struct queue *q, struct TreeNode *node)
{
    struct qnode *new = (struct qnode *) malloc(sizeof(struct qnode));
    new->node = node;
    new->next = NULL;
    (*q->tail) = new;
    q->tail = &new->next;
    q->size++;
}

static struct TreeNode *dequeue(struct queue *q)
{
    if (!q->head)
        return NULL;
    struct qnode *tmp = q->head;
    q->head = q->head->next;
    if (!q->head)
        q->tail = &q->head;
    struct TreeNode *ans = tmp->node;
    free(tmp);
    q->size--;
    return ans;
}

static inline void queue_destroy(struct queue *q)
{
    while (q->head) {
        struct qnode *tmp = q->head;
        q->head = q->head->next;
        free(tmp);
    }
}

int minDepth(struct TreeNode* root)
{
    if (!root)
        return 0;
    struct queue *q = queue_init();
    enqueue(q, root);
    int height = 0;
    while (queue_size(q)) {
        height++;
        const int sz = q->size;
        for (int i = 0; i < sz; i++) {
            struct TreeNode *tn = dequeue(q);
            if (tn->left && tn->right) {
                enqueue(q, tn->left);
                enqueue(q, tn->right);
            } else if (tn->left) {
                enqueue(q, tn->left);
            } else if (tn->right) {
                enqueue(q, tn->right);
            } else {    // is a leaf
                queue_destroy(q);
                return height;
            }
        }
    }
    queue_destroy(q);
    return -1;
}