/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */


struct ListNode* oddEvenList(struct ListNode* head){
    struct ListNode *odd, *even, *it, *tail, *endpoint;
    if(!head || !head->next || !head->next->next)
        return head;
    for(it=head; it; it=it->next)
        tail = it;
    endpoint = tail;
    for(it=head; it!=endpoint;){
        odd = it;
        it = it->next;
        even = it;
        odd->next = even->next;
        even->next = NULL;
        tail->next = even;
        if(it==endpoint)
            break;
        tail = tail->next;  //update tail
        it = odd->next;
    }
    return head;
}