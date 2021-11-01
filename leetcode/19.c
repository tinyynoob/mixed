/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */


struct ListNode* removeNthFromEnd(struct ListNode* head, int n){
    int i, count;
    struct ListNode *it, *p;
    
    count = 0;
    for(it=head; it; it=it->next)   //count length of the list
        count++;
    // if(n>count||n<=0)
    //     fprintf(stderr,"ERROR\n");
    count = count-n;
    if(!count){     //target at head
        p = head->next;
        free(head);
        head = p;
        return head;
    }
    it = head;
    for(i=0; i<count-1; i++)    //it points to the node before target
        it = it->next;
    if( (it->next)->next )      //target at mid
        p = (it->next)->next;
    else        //target at tail
        p = NULL;
    free(it->next);
    it->next = p;
    return head;
}
