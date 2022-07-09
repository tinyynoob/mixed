
struct listnode {
    int index;
    int value;
    struct listnode *next;
    struct listnode *prev;
};

void mono_enqueue(struct listnode **head, struct listnode **tail, int index, int value)
{
    struct listnode *new = (struct listnode *) malloc(sizeof(struct listnode));
    new->index = index;
    new->value = value;
    struct listnode *it = *tail;
    while (it && it->value <= new->value) {
        struct listnode *tmp = it;
        it = it->prev;
        free(tmp);
    }
    new->prev = it;
    if (it)
        it->next = new;
    else
        *head = new;
    new->next = NULL;
    *tail = new;
}

void mono_dequeue(struct listnode **head, struct listnode **tail)
{
    struct listnode *tmp = *head;
    *head = (*head)->next;
    free(tmp);
    if (*head)
        (*head)->prev = NULL;
    else
        *tail = NULL;
}


int maxResult_dp(int *nums, int numsSize, int k);

int maxResult(int* nums, int numsSize, int k)
{
    int ans = nums[0], curr = 0;
loop:;
    while (curr < numsSize - 1) {
        int next = curr + 1;
        printf("curr = %d, ans = %d\n", curr, ans);
        for (; next <= curr + k; next++) {
            if (next >= numsSize) {
                ans += nums[numsSize - 1];
                goto end;
            } else if (nums[next] >= 0) {
                ans += nums[next];
                curr = next;
                goto loop;
            }
        }
        while (next < numsSize && nums[next] < 0)
            next++;
        if (next >= numsSize) {
            ans += maxResult_dp(nums + curr, next - curr, k) - nums[curr];
            goto end;
        } else {
            ans += maxResult_dp(nums + curr, next - curr + 1, k) - nums[curr];
            curr = next;
            goto loop;
        }
    }
end:
    return ans;
}

int maxResult_dp(int *nums, int numsSize, int k)
{
    struct listnode *head = NULL, *tail = NULL;
    mono_enqueue(&head, &tail, 0, nums[0]);
    int index = 1;
    for (index = 1 ; index < k && index < numsSize; index++)
        mono_enqueue(&head, &tail, index, head->value + nums[index]);
    for (index = k; index < numsSize; index++) {
        mono_enqueue(&head, &tail, index, head->value + nums[index]);
        if (head->index == index - k)
            mono_dequeue(&head, &tail);
    }
    int ans = tail->value;
    while (head) {
        struct listnode *tmp = head;
        head = head->next;
        free(tmp);
    }
    return ans;
}
