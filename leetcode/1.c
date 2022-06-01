#include <limits.h>


struct data {
    int key;
    int index;
};

struct hash {
    unsigned cap;    // capacity
    struct data *tab;
};

static struct hash *hash_init(int sz)
{
    struct hash *h = (struct hash *) malloc(sizeof(struct hash));
    h->cap = 1;
    while (h->cap <= sz)
        h->cap <<= 1;
    h->tab = (struct data *) malloc(sizeof(struct data) * h->cap);
    for (int i = 0; i < h->cap; i++) {
        h->tab[i].key = INT_MIN;
        h->tab[i].index = -1;
    }
    return h;
}

static inline void hash_insert(struct hash *h, int key, int index)
{
    int val = key & (h->cap - 1);
    while (h->tab[val].index != -1)
        val = (val + 1) & (h->cap - 1);
    h->tab[val].key = key;
    h->tab[val].index = index;
}

/* Return (struct data).index */
static inline int hash_find(struct hash *h, int key)
{
    int val = key & (h->cap - 1);
    while (h->tab[val].index != -1 && h->tab[val].key != key)
        val = (val + 1) & (h->cap - 1);
    return h->tab[val].index;
}

static inline void hash_destroy(struct hash *h)
{
    free(h->tab);
    free(h);
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum(int* nums, int numsSize, int target, int* returnSize)
{
    *returnSize = 2;
    int *ans = (int *) malloc(sizeof(int) * (*returnSize));
    struct hash *h = hash_init(numsSize - 1);
    for (int i = 0; i < numsSize; i++) {
        int ret = hash_find(h, target - nums[i]);
        if (ret != -1) {    // found
            ans[0] = ret;
            ans[1] = i;
            goto end;
        } else {
            hash_insert(h, nums[i], i);
        }
    }
end:;
    hash_destroy(h);
    return ans;
}