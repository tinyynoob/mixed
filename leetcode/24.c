/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
void swap_next_two(struct ListNode*);

struct ListNode* swapPairs(struct ListNode* head){
    struct ListNode *it, *next_it;
    if(!head)
        return NULL;
    it = head;
    if(it&&it->next){  //first round of while
        head = it->next;
        it->next = head->next;
        head->next = it;
    }
    while(it->next&&(it->next)->next){
        next_it = it->next;
        swap_next_two(it);
        it = next_it;
    }
    return head;
}

void swap_next_two(struct ListNode* subhead)
{
    struct ListNode *temp;
    temp = (subhead->next)->next;
    (subhead->next)->next = temp->next;
    temp->next = subhead->next;
    subhead->next = temp;
}