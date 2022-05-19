#include <stdio.h>
#include <stdbool.h>
#include <limits.h>


/* INT_MIN is used to represent NULL child.
 */
int main()
{
    const int nums[] = {5,4,6,INT_MIN,INT_MIN,3,7};
    const int numsSize = sizeof(nums)/sizeof(int);
    FILE *f = fopen("serialBST.dot", "w");
    fprintf(f, "graph BST {\n");
    if (numsSize)
        fprintf(f, "    %d [label=\"%d\"];\n", 0, nums[0]);
    for (int i = 1; i < numsSize; i++) {
        if (nums[i] != INT_MIN) {
            fprintf(f, "    %d [label=\"%d\"];\n", i, nums[i]);
            fprintf(f, "    %d -- %d\n", (i - 1) / 2, i);
        }
    }
    fprintf(f, "}");
    fclose(f);
    return 0;
}