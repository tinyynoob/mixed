/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */


struct ListNode* mergeTwoLists(struct ListNode* l1, struct ListNode* l2){
    struct ListNode *head, *tail, *it1, *it2, *newNode;
    head = NULL;
    tail = NULL;
    it1 = l1;
    it2 = l2;
    while(it1||it2)
    {
        newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
        newNode->next = NULL;
        if(!it1){
            newNode->val = it2->val;
            it2 = it2->next;
        }
        else if(!it2){
            newNode->val = it1->val;
            it1 = it1->next;
        }
        else if(it1->val < it2->val){
            newNode->val = it1->val;
            it1 = it1->next;
        }
        else{
            newNode->val = it2->val;
            it2 = it2->next;
        }
        
        //update tail
        if(!tail)   //first round
            tail = newNode;
        else{
            tail->next = newNode;
            tail = tail->next;
        }
            
        //update head in first round only
        if(!head)
            head = newNode;
    }
    return head;
}