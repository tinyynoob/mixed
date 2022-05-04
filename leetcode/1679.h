#include <stdlib.h>
#include <stdbool.h>


struct acuml {  // accumulate
    int number;
    int quantity;
};

struct hash {
    int capacity;
    struct acuml *ht;    // hash table
};

static struct hash *hash_init(int size)
{
    if (!size)
        return NULL;
    struct hash *h = (struct hash *) malloc(sizeof(struct hash));
    h->capacity = 1;
    for (int i = 1 << 20; i; i >>= 1) {
        if (size > i) {
            h->capacity = i << 2;   // maybe too waste
            break;
        }
    }
    h->ht = (struct acuml *) malloc(sizeof(struct acuml) * h->capacity);
    for (int i = 0; i < h->capacity; i++)
        h->ht[i].number = -1;
    return h;
}

// return index
static int hash_search(struct hash *h, int key)
{
    int value = key & (h->capacity - 1);
    while (h->ht[value].number != -1) {
        if (h->ht[value].number == key)
            return value;
        value = (value + 1) & (h->capacity - 1);
    }
    return -1;
}

// return index
static int hash_find_slot(struct hash *h, int key)
{
    int value = key & (h->capacity - 1);
    while (h->ht[value].number != -1) {
        if (h->ht[value].number == key)
            return value;
        value = (value + 1) & (h->capacity - 1);
    }
    return value;
}

static void hash_add(struct hash *h, int key)
{
    int index = hash_find_slot(h, key);
    if (h->ht[index].number == -1) {
        h->ht[index].number = key;
        h->ht[index].quantity = 1;
    } else {
        h->ht[index].quantity++;
    }
}

static bool hash_consume(struct hash *h, int key)
{
    int index = hash_search(h, key);
    if (index == -1)
        return false;
    else if (h->ht[index].quantity == 0)
        return false;
    h->ht[index].quantity--;
    return true;
}

static inline void hash_destroy(struct hash *h)
{
    free(h->ht);
    free(h);
}

int maxOperations(int* nums, int numsSize, int k)
{
    struct hash *h = hash_init(numsSize);
    for (int i = 0; i < numsSize; i++)
        hash_add(h, nums[i]);
    int ans = 0;
    for (int i = 0; i < h->capacity; i++) {
        if (h->ht[i].number == -1 || h->ht[i].quantity == 0)
            continue;
        const int target = k - h->ht[i].number;
        if (target == h->ht[i].number) {    // couple with self
            while (1) {
                if (h->ht[i].quantity >= 2) {
                    h->ht[i].quantity -= 2;
                    ans++;
                } else {
                    break;
                }
            }
        } else {    // couple with someone else
            while (hash_consume(h, target)) {
                ans++;
                h->ht[i].quantity--;
                if (!h->ht[i].quantity)
                    break;
            }
        }
    }
    hash_destroy(h);
    return ans;
}