#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG 1

struct course {
    int id;
    char *name;
    struct course *next;
    struct course *prior;
};

int main()
{
    int num;
    scanf("%d ", &num);
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
               index[i]->next ? index[i]->next->id : -9999);
        DEBUG_it = DEBUG_it->next;
    }
    putchar('\n');
    puts("The backward lists:");
    for (int i = num - 1; i >= 0; i--)
        printf("%d  %s -> %d\n", index[i]->id, index[i]->name,
               index[i]->prior ? index[i]->prior->id : -9999);
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
    // assume they are well-connected
    for (int i = 0; i < num; i++) {
        struct course *tmp = head;
        head = head->next;
        free(tmp->name);
        free(tmp);
    }
    return 0;
}
