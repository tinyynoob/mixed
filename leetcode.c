#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct stack{
    char ch;
    struct stack* next;
};

int isValid(char * s);
void push(struct stack** head, char in);
char pop(struct stack** head);
void clean(struct stack* head);


int main()
{
    char s[10]="(";
    printf("%d\n",isValid(s));
    system("pause");
    return 0;
}

int isValid(char * s){
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
            if( temp=='('&&*it==')' || temp=='['&&*it==']' || temp=='{'&&*it=='}' )
                ;
            else{   //not matched parentheses
                clean(head);
                return 0;
            }
        }
    }
    //if(!head)   //if empty, return True
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