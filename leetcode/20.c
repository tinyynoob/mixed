struct stack{
    char ch;
    struct stack* next;
};

void push(struct stack** head, char in);
char pop(struct stack** head);
void clean(struct stack* head);

bool isValid(char * s){
    struct stack *head;
    char *it;
    char temp;
    head = NULL;
    
    for(it=s; *it; it++){
        if( *it=='(' || *it=='[' || *it=='{' )
            push(&head,*it);
        else if(!head) //if there is nothing to pop
            return 0;
        else{
            temp = pop(&head);
            if( (temp=='('&&*it==')')||(temp=='['&&*it==']')||(temp=='{'&&*it=='}') )
                ;
            else{    //not matched parentheses
                clean(head);
                return 0;
            }
        }
    }
    if(head){
        clean(head);
        return 0;
    }
    return 1;
}

void push(struct stack** head, char in){
    struct stack *newNode;
    newNode = (struct stack*)malloc(sizeof(struct stack));
    newNode->ch = in;
    newNode->next = *head;
    *head = newNode;
}
char pop(struct stack** head){
    struct stack *p;
    char out;
    out = (*head)->ch;
    p = (*head)->next;
    free(*head);
    *head = p;
    return out;
}
void clean(struct stack* head){
    while(head)
        pop(&head);
}
    