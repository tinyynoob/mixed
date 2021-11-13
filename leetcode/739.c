
struct stack{
    int index;
    struct stack *next;
};

void stack_push(struct stack**, int);
void stack_pop(struct stack**);
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

int* dailyTemperatures(int* temperatures, int temperaturesSize, int* returnSize){
/*implement by stack. Note that the value in stack must be decreasing, otherwise it would be popped*/
    struct stack *head;
    int i, *ans;
    head = NULL;
    
    stack_push(&head, 0);
    for(i=1; i<temperaturesSize; i++){
        while(head && (temperatures[i] > temperatures[head->index])){
            temperatures[head->index] = i-(head->index);    //temperatures[] is used in-place
            stack_pop(&head);
        }
        stack_push(&head, i);
    }
    while(head){    //set the remainders to 0
        temperatures[head->index] = 0;
        stack_pop(&head);
    }
    *returnSize = temperaturesSize;
    return temperatures;
}

void stack_push(struct stack **head, int index){
    struct stack *newNode;
    newNode = (struct stack*)malloc(sizeof(struct stack));
    newNode->next = *head;
    newNode->index = index;
    *head = newNode;       
}

void stack_pop(struct stack **head){
    struct stack *temp;
    temp = (*head)->next;
    free(*head);
    *head = temp;
}
