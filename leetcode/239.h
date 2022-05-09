#include <stdlib.h>
#include <stdint.h>


/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

struct idxnode {
    int index;
    struct idxnode *next;
};

struct heap {
    int size;
    int *value;
    struct idxnode **lists;   // array of lists
};

static inline int ilog32(uint32_t v)
{
    uint32_t ans = v > 0;
    int m = (v > 0xFFFFU) << 4;
    v >>= m;
    ans |= m;
    m = (v > 0xFFU) << 3;
    v >>= m;
    ans |= m;
    m = (v > 0xFU) << 2;
    v >>= m;
    ans |= m;
    m = (v > 0x3u) << 1;
    v >>= m;
    ans |= m;
    ans += (v > 1);
    return ans;
}

static struct heap *heap_init(int window_size)
{
    struct heap *h = (struct heap *) malloc(sizeof(struct heap));
    h->size = (1 << ilog32(window_size)) - 1;
    h->value = (int *) malloc(sizeof(int) * h->size);
    h->lists = (struct idxnode **) malloc(sizeof(struct idxnode *) * h->size);
    for (int i = 0; i < h->size; i++)
        h->lists[i] = NULL;
    return h;
}



int* maxSlidingWindow(int* nums, int numsSize, int k, int* returnSize)
{
    struct heap *h = heap_init(k);



    int left = 0, right = 0;
    *returnSize = numsSize - k + 1;
    int *ans = (int *) malloc(sizeof(int) * (*returnSize));
    ans[0] = nums[0];
    int max = nums[0], maxidx = 0;  // maxidx is chosen right-most
    for (int i = 1; i < k; i++) {
        right++;
        if (nums[right] >= max) {
            max = nums[right];
            maxidx = right;
        }
    }
    ans[0] = max;

    for (int i = 1; i < (*returnSize); i++) {
        right++;
        if (maxidx == left) {   // max is gone, need rescan
            max = nums[left + 1];
            for (int j = left + 1; j <= right; j++) {
                if (nums[j] >= max) {
                    max = nums[j];
                    maxidx = j;
                }
            }
        } else {
            if (nums[right] >= max) {
                max = nums[right];
                maxidx = right;
            }
        }
        ans[++left] = max;
    }
    return ans;
}