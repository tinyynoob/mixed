/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */


struct ListNode* removeElements(struct ListNode* head, int val){
    struct ListNode *prev, *it, *temp;
    if(!head)
        return head;
    while(head->val==val){ //if at head
        temp = head->next;
        free(head);
        head = temp;
        if(!head)
            return head;
    }
    it = head;
    while(it){     
        if(it->val==val){
            temp = it->next;
            free(it);
            prev->next = temp;
            it = temp;
        }
        else{
            prev = it;
            it = it->next;
        }
    }
    return head;
}