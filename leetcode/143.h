#include <stddef.h>  // to contain NULL

struct ListNode {
    int val;
    struct ListNode *next;
};

void reorderList(struct ListNode *head)
{
    if (!head || !head->next)
        return;
    struct ListNode *fast = head, *slow = head, *pre = NULL;
    while (fast) {
        fast = fast->next;
        pre = slow;
        slow = slow->next;
        if (fast)
            fast = fast->next;
    }
    pre->next = NULL;

    /* reverse the backlist */
    struct ListNode *backlist = slow;
    struct ListNode *remain = backlist->next;
    backlist->next = NULL;
    while (remain) {
        struct ListNode *tmp = remain->next;
        remain->next = backlist;
        backlist = remain;
        remain = tmp;
    }

    /* merge forward and backward list */
    struct ListNode **tail = &head;
    struct ListNode *fit = head;    // forward iterator
    while (backlist) {
        *tail = fit;
        tail = &(*tail)->next;
        fit = fit->next;
        *tail = backlist;
        tail = &backlist->next;
        backlist = backlist->next;
    }
    if (fit)    // odd
        *tail = fit;
}
