#include <stddef.h>  // to contain NULL

struct ListNode {
    int val;
    struct ListNode *next;
};

/* must contain at least 2 nodes */
static inline struct ListNode *sep_tail(struct ListNode *head)
{
    while (head->next->next)
        head = head->next;
    struct ListNode *tmp = head->next;
    head->next = NULL;
    return tmp;
}

void reorderList(struct ListNode *head)
{
    if (!head || !head->next)
        return;
    struct ListNode *old = head;
    struct ListNode **tail = &head;  // tail of ans
    while (old) {
        struct ListNode *next = old->next;
        *tail = old;
        tail = &(*tail)->next;
        if (!next)  // odd number
            break;
        *tail = sep_tail(old);
        tail = &(*tail)->next;
        old = next;
    }
    *tail = NULL;
}
