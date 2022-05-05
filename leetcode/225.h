#include <stdlib.h>
#include <stdbool.h>


struct node {
    int data;
    struct node *next;
};

typedef struct {
    struct node *first;
} MyStack;


MyStack* myStackCreate() {
    MyStack *ans = (MyStack *) malloc(sizeof(MyStack));
    ans->first = NULL;
    return ans;
}

void myStackPush(MyStack* obj, int x) {
    struct node *new = (struct node *) malloc(sizeof(struct node));
    new->data = x;
    new->next = obj->first;
    obj->first = new;
}

int myStackPop(MyStack* obj) {
    struct node *remove = obj->first;
    obj->first = obj->first->next;
    int ans = remove->data;
    free(remove);
    return ans;
}

int myStackTop(MyStack* obj) {
    return obj->first->data;
}

bool myStackEmpty(MyStack* obj) {
    return !obj->first;
}

void myStackFree(MyStack* obj) {
    while (obj->first) {
        struct node *temp = obj->first;
        obj->first = obj->first->next;
        free(temp);
    }
    free(obj);
}

/**
 * Your MyStack struct will be instantiated and called as such:
 * MyStack* obj = myStackCreate();
 * myStackPush(obj, x);
 
 * int param_2 = myStackPop(obj);
 
 * int param_3 = myStackTop(obj);
 
 * bool param_4 = myStackEmpty(obj);
 
 * myStackFree(obj);
*/