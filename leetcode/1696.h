


struct entry {
    int index;
    int value;
};

/* ring buffer
 * interval: [start, end)
 */
struct rbuf {
    unsigned start;
    unsigned end;
    unsigned size;
    struct entry *buf;
};


unsigned roundup_power2(int v)
{
    unsigned u = v;
    u |= u >> 1;
    u |= u >> 2;
    u |= u >> 4;
    u |= u >> 8;
    u |= u >> 16;
    return u + 1;
}

void mono_add(struct rbuf *rb, int index, int value)
{
    if (rb->start == rb->end) {
        rb->buf[rb->end].index = index;
        rb->buf[rb->end].value = value;
        rb->end = (rb->end + 1) & (rb->size - 1);
        return;
    }
    unsigned idx = (rb->end - 1) & (rb->size - 1);
    while (idx != rb->start && rb->buf[idx].value <= value)
        idx = (idx - 1) & (rb->size - 1);

    if (idx == rb->start && rb->buf[idx].value <= value)
        ;
    else
        idx = (idx + 1) & (rb->size - 1);
    rb->buf[idx].index = index;
    rb->buf[idx].value = value;
    rb->end = (idx + 1) & (rb->size - 1);
}

void mono_del(struct rbuf *rb)
{
    rb->start = (rb->start + 1) & (rb->size - 1);
}

int maxResult(int* nums, int numsSize, int k)
{
    struct rbuf rb = {.start = 0, .end = 0, .size = roundup_power2(k)};
    rb.buf = (struct entry *) malloc(sizeof(struct entry) * rb.size);
    mono_add(&rb, 0, nums[0]);
    int index;
    for (index = 1 ; index < k && index < numsSize; index++)
        mono_add(&rb, index, rb.buf[rb.start].value + nums[index]);
    for (index = k; index < numsSize; index++) {
        mono_add(&rb, index, rb.buf[rb.start].value + nums[index]);
        if (rb.buf[rb.start].index == index - k)
            mono_del(&rb);
    }
    int ans = rb.buf[(rb.end - 1) & (rb.size - 1)].value;
    free(rb.buf);
    return ans;
}
