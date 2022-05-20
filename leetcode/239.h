
struct rbuf {   // ring buffer
    int capacity;
    int *data;
    int start;
    int end;
    int length;
};

int rounding_up_base2(uint32_t v)
{
    int shift = v > 0;
    int m = (v > (uint32_t) 0xFFFFU) << 4;
    v >>= m;
    shift |= m;
    m = (v > 0xFFU) << 3;
    v >>= m;
    shift |= m;
    m = (v > 0xFU) << 2;
    v >>= m;
    shift |= m;
    m = (v > 0x3U) << 1;
    v >>= m;
    shift |= m;
    shift += (v > 1);
    return 1 << shift;
}

static struct rbuf *rbuf_init(int capacity)
{
    struct rbuf *rbf = (struct rbuf *) malloc(sizeof(struct rbuf));
    rbf->capacity = capacity;
    rbf->data = (int *) malloc(sizeof(int) * rbf->capacity);
    rbf->start = 0;
    rbf->end = 0;
    rbf->length = 0;
    return rbf;
}

static inline bool rbuf_isempty(struct rbuf *rbf)
{
    return !rbf->length;
}

// no empty check
static inline int rbuf_get_start(struct rbuf *rbf)
{
    return rbf->data[rbf->start];
}

// no empty check
static inline int rbuf_get_end(struct rbuf *rbf)
{
    return rbf->data[(rbf->end - 1) & (rbf->capacity - 1)];
}

// push at end
static void rbuf_push(struct rbuf *rbf, int data)
{
    // assume never full
    rbf->data[rbf->end] = data;
    rbf->end = (rbf->end + 1) & (rbf->capacity - 1);
    rbf->length++;
}

static bool rbuf_pop_start(struct rbuf *rbf)
{
    if (!rbf->length)
        return false;
    rbf->start = (rbf->start + 1) & (rbf->capacity - 1);
    rbf->length--;
    return true;
}

static bool rbuf_pop_end(struct rbuf *rbf)
{
    if (!rbf->length)
        return false;
    rbf->end = (rbf->end - 1) & (rbf->capacity - 1);
    rbf->length--;
    return true;
}

static void rbuf_destroy(struct rbuf *rbf)
{
    if (!rbf)
        return NULL;
    free(rbf->data);
    free(rbf);
}

/**
 * Note: The returned array must be malloced, assume caller calls fcapacity().
 */
int* maxSlidingWindow(int* nums, int numsSize, int k, int* returnSize)
{
    struct rbuf *rbf = rbuf_init(rounding_up_base2(k));
    rbuf_push(rbf, nums[0]);
    for (int i = 1; i < k; i++) {
        while (!rbuf_isempty(rbf) && rbuf_get_end(rbf) < nums[i])
            rbuf_pop_end(rbf);
        rbuf_push(rbf, nums[i]);
    }
    
    *returnSize = numsSize - k + 1;
    int *ans = (int *) malloc(sizeof(int) * (*returnSize));
    ans[0] = rbuf_get_start(rbf);
    for (int i = k; i < numsSize; i++) {
        rbuf_pop_start(rbf);
        while (!rbuf_isempty(rbf) && rbuf_get_end(rbf) < nums[i])
            rbuf_pop_end(rbf);
        rbuf_push(rbf, nums[i]);
        ans[i - k + 1] = rbuf_get_start(rbf);
    }
    
    rbuf_destroy(rbf);
    return ans;
}