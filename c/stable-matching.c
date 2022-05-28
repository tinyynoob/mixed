#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define DEBUG 1

struct male {
    int *rank;  // [rank] = female
    int progs;  // increasing
};

struct female {
    int *ref;  // [male] = rank
    int partner;
};

struct list_node {
    int male;
    struct list_node *next;
};

struct sm {
    int size;
    struct male *male;
    struct female *female;
    struct list_node *single;  // list to record single males
};

struct sm *sm_init(int sz)
{
    struct sm *gs = (struct sm *) malloc(sizeof(struct sm));
    gs->size = sz;
    gs->single = NULL;
    /* male */
    gs->male = (struct male *) malloc(sizeof(struct male) * gs->size);
    for (int m = 0; m < gs->size; m++) {
        gs->male[m].rank = (int *) malloc(sizeof(int) * gs->size);
        for (int i = 0; i < gs->size; i++)
            scanf("%d ", &gs->male[m].rank[i]);
        gs->male[m].progs = -1;
        struct list_node *new =
            (struct list_node *) malloc(sizeof(struct list_node));
        new->male = m;
        new->next = gs->single;
        gs->single = new;
    }
    /* female */
    gs->female = (struct female *) malloc(sizeof(struct female) * gs->size);
    for (int f = 0; f < gs->size; f++) {
        gs->female[f].ref = (int *) malloc(sizeof(int) * gs->size);
        for (int i = 0; i < gs->size; i++) {
            int m;
            scanf("%d ", &m);
            gs->female[f].ref[m] = i;
        }
        gs->female[f].partner = -1;
    }
    return gs;
}

void sm_destroy(struct sm *gs)
{
    for (int m = 0; m < gs->size; m++)
        free(gs->male[m].rank);
    free(gs->male);
    for (int f = 0; f < gs->size; f++)
        free(gs->female[f].ref);
    free(gs->female);
    while (gs->single) {
        struct list_node *tmp = gs->single;
        gs->single = gs->single->next;
        free(tmp);
    }
    free(gs);
}

/* A single male proposes to his next target.
 * If there is no single male, return false.
 * Otherwise, no matter the proposal is accepted or not, return true.
 */
bool propose(struct sm *gs)
{
    if (!gs->single)
        return false;
    const int m = gs->single->male;
    const int f = gs->male[m].rank[++gs->male[m].progs];
#if DEBUG
    printf("%d proposes to %d ... ", m, f);
#endif
    if (gs->female[f].partner == -1) {  // accepted
#if DEBUG
        puts("accepted");
#endif
        struct list_node *tmp = gs->single;
        gs->single = gs->single->next;
        free(tmp);
        gs->female[f].partner = m;
    } else if (gs->female[f].ref[m] <
               gs->female[f].ref[gs->female[f].partner]) {  // accepted
#if DEBUG
        puts("accepted");
#endif
        gs->single->male = gs->female[f].partner;  // dump current partner
        gs->female[f].partner = m;
    } else {  // rejected
        ;     // do nothing
#if DEBUG
        puts("rejected");
#endif
    }
    return true;
}

int main()
{
    int sz;
    scanf("%d ", &sz);
    struct sm *gs = sm_init(sz);
    while (propose(gs)) {
    }
    puts("male\tfemale");
    for (int m = 0; m < gs->size; m++)
        printf("%d -- %d\n", m, gs->male[m].rank[gs->male[m].progs]);
    sm_destroy(gs);
    gs = NULL;
    return 0;
}
