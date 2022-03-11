/* Fibonacci tree drawer */
#include <stdio.h>
#include <stdlib.h>

static FILE *f;
static unsigned long long counter;

static void preorder(unsigned int n, const unsigned long long caller_id);

int main()
{
    unsigned int n;
    printf("Fib: ");
    scanf("%d", &n);
    f = fopen("fibonacci_tree.dot", "w");
    if (!f)
        return 1;
    counter = 1;
    fprintf(f, "graph fib {\n\t# F(%u)\n", n);
    preorder(n, 0);
    fprintf(f, "}");
    fclose(f);
    return 0;
}

static void preorder(unsigned int n, const unsigned long long caller_id)
{
    const unsigned long long id = counter++;
    fprintf(f, "\t%llu [label=\"F(%u)\"];\n", id, n);
    if (caller_id)
        fprintf(f, "\t%llu -- %llu;\n", caller_id, id);
    if (n > 2) {
        preorder(n - 1, id);
        preorder(n - 2, id);
    }
    return;
}
