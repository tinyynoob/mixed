/**
 * Definition for a Node.
 * struct Node {
 *     int val;
 *     struct Node *left;
 *     struct Node *right;
 *     struct Node *next;
 * };
 */

struct queue {
    struct Node *head;
    struct Node **tail;
    int size;
};

/* enqueue at tail */
void enqueue(struct queue *q, struct Node *data)
{
    data->next = NULL;
    *q->tail = data;
    q->tail = &data->next;
    q->size++;
}

/* dequeue at head */
struct Node *dequeue(struct queue *q)
{
    struct Node *ans = q->head;
    q->head = q->head->next;
    if (!q->head)
        q->tail = &q->head;
    q->size--;
    return ans;
}

struct Node* connect(struct Node* root)
{
    if (!root)
        return NULL;
    struct queue *q = (struct queue *) malloc(sizeof(struct queue));
    q->head = NULL;
    q->tail = &q->head;
    q->size = 0;
    enqueue(q, root);
    
    while (q->head) {
        int sz = q->size;
        for (int i = 0; i < sz; i++) {
            struct Node *curr = dequeue(q);
            curr->next = (i == sz - 1) ? NULL : q->head;
            if (curr->left)
                enqueue(q, curr->left);
            if (curr->right)
                enqueue(q, curr->right);
        }
    }
	free (q);
    return root;
}