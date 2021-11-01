#include<stdio.h>
#include<stdlib.h>
#include<string.h>

 struct ListNode {
    int val;
    struct ListNode *next;
};
 
struct ListNode* removeNthFromEnd(struct ListNode* head, int n);

int main()
{
    int i;
    struct ListNode *head, *newNode, *it;
    head = NULL;
    for(i=0; i<5; i++){
        newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
        newNode->val = 5-i;
        if(!head)
            newNode->next = NULL;
        else
            newNode->next = head;
        head = newNode;
    }
    head = removeNthFromEnd(head, 2);
    for(it=head; it; it=it->next)
        printf("%d\t",it->val);

    system("pause");
    return 0;
}

struct ListNode* removeNthFromEnd(struct ListNode* head, int n){
    int i, count;
    struct ListNode *it, *p;
    
    count = 0;
    for(it=head; it; it=it->next)
        count++;
    count = count-n;
    
    it = head;
    for(i=0; i<count-1; i++)
        it = it->next;
    p = (it->next)->next;
    free(it->next);
    it = p;
    return head;
}