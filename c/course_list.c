#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

#define DEBUG 0

struct course {
    int id;
    char *name;
    struct course *next;
    struct course *prior;
};

struct queue {
    int id;
    struct queue *next;
};

struct hash {
    unsigned size;
    int *map;
};

struct hash *hash_init(unsigned size)
{
    if (!size)
        return NULL;
    struct hash *h = (struct hash *) malloc(sizeof(struct hash));
    h->size = size;
    h->map = (int *) malloc(sizeof(int) * size);
    for (int i = 0; i < size; i++)
        h->map[i] = INT_MIN;
    return h;
}

void hash_deinit(struct hash *h)
{
    free(h->map);
    free(h);
}

void hash_add(struct hash *h, int key)
{
    int index = key % h->size;
    /* linear probe */
    while (h->map[index] != INT_MIN)
        index = (index+1)%(h->size);
    h->map[index] = key;
}

/* if found, return in @value */
bool hash_find(struct hash *h, int key, int *value)
{
    int index = key % h->size;
    while (h->map[index] != INT_MIN) {
        if(h->map[index] == key) {
            value = NULL;   // TODO
            return true;   
        }
        index = (index + 1) % (h->size);
    }
    return false;
}



int main()
{
    int num;
    scanf("%d ", &num);
    struct hash *myHash = hash_init(num << 1);
    struct course *head = NULL;
    for (int i = 0; i < num; i++) {
        struct course *new = (struct course *) malloc(sizeof(struct course));
    }


    struct course **index =
        (struct course **) malloc(num * sizeof(struct course));
    int *ntable = (int *) malloc(num * sizeof(int));
    int *ptable = (int *) malloc(num * sizeof(int));
#if DEBUG
    puts("==========================");
#endif
    for (int i = 0; i < num; i++) {
        index[i] = (struct course *) malloc(sizeof(struct course));
        if (!index[i])
            ;
        scanf("%d %d %d ", &index[i]->id, &ntable[i], &ptable[i]);
        index[i]->name = (char *) calloc(sizeof(char), 50);
        fgets(index[i]->name, 49, stdin);
        for (int j = 49; j >= 0; j--) {
            // eliminate the '\n'
            if (index[i]->name[j] == '\n') {
                index[i]->name[j] = '\0';
                break;
            }
        }
        index[i]->next = NULL;
        index[i]->prior = NULL;
#if DEBUG
        printf("id: %d, next: %d, prior: %d\nname: %s\n", index[i]->id,
               ntable[i], ptable[i], index[i]->name);
#endif
    }

    /* can be improved by hash */
    for (int i = 0; i < num; i++) {
        /* @flag:
         * 0: not finish
         * 1: finish prior
         * 2: finish next
         * 3: finish prior and next
         */
        int flag = 0;
        for (int j = 0; j < num; j++) {
            if (index[j]->id == ptable[i]) {
                index[i]->prior = index[j];
                flag |= 1;
                if (flag == 3)
                    break;
            }
            if (index[j]->id == ntable[i]) {
                index[i]->next = index[j];
                flag |= 2;
                if (flag == 3)
                    break;
            }
        }
#if DEBUG
        printf("id: %d, flag: %d\n", index[i]->id, flag);
#endif
    }
    free(ntable);
    free(ptable);

    struct course *head = index[0];
#if DEBUG
    puts("==========================");
    // assume the forwarding direction is connected
    struct course *DEBUG_it = head;
    puts("The forward lists:");
    for (int i = 0; i < num; i++) {
        printf("%d  %s -> %d\n", DEBUG_it->id, DEBUG_it->name,
               index[i]->next ? index[i]->next->id : INT_MIN);
        DEBUG_it = DEBUG_it->next;
    }
    putchar('\n');
    puts("The backward lists:");
    for (int i = num - 1; i >= 0; i--)
        printf("%d  %s -> %d\n", index[i]->id, index[i]->name,
               index[i]->prior ? index[i]->prior->id : INT_MIN);
    puts("==========================");
#endif
    free(index);

    const struct course *current = head;
    while (1) {
        printf("Current Course: %s\n", current->name);
        printf("[n] Next course. [p] Prior course [q] Quit:");
        putchar('\n');
        int choose = getchar();
        switch (choose) {
        case 'q':
            goto end;
        case 'n':
            if (current->next)
                current = current->next;
            else
                puts("There is no next course.");
            break;
        case 'p':
            if (current->prior)
                current = current->prior;
            else
                puts("There is no next course.");
            break;
        default:
            perror("error option");
        }
        getchar();  // to discard '\n'
    }

end:
    hash_deinit(myHash);
    // assume they are well-connected
    for (int i = 0; i < num; i++) {
        struct course *tmp = head;
        head = head->next;
        free(tmp->name);
        free(tmp);
    }
    return 0;
}

