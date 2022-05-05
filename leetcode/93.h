#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

struct sep {
    int start;
    int width;  // \in \{1, 2, 3\}
};

struct valid {
    int width[4];
    struct valid *next;
};

/* @pos \in \{0, 1, 2, 3\} is the current position. 
 * 
 */
static void restore_ip(const char *s, struct sep *const record, struct valid **list, int pos)
{
    if (pos == 4) {
        // if it is valid, push to valid list and return
        if (s[record[3].start + record[3].width] != '\0')   // digits remained
            return;
        struct valid *node = (struct valid *) malloc(sizeof(struct valid));
        for (int i = 0; i < 4; i++)
            node->width[i] = record[i].width;
        node->next = *list;
        *list = node;
        return;
    }

    if (pos == 0)
        record[0].start = 0;
    else
        record[pos].start = record[pos - 1].start + record[pos - 1].width;

    if (s[record[pos].start] == '\0')
        return;
    record[pos].width = 1;
    restore_ip(s, record, list, pos + 1);
    
    if (s[record[pos].start + 1] == '\0')
        return;
    record[pos].width = 2;
    if (s[record[pos].start] == '0')    // first digit 0 is not valid
        return;
    restore_ip(s, record, list, pos + 1);
    
    if (s[record[pos].start + 2] == '\0')
        return;
    record[pos].width = 3;
    char numstr[4] = {s[record[pos].start], s[record[pos].start + 1], 
                      s[record[pos].start + 2], '\0'};
    int n = atoi(numstr);
    if (n > 255)
        return;
    restore_ip(s, record, list, pos + 1);
    return;
}

char **restoreIpAddresses(char *s, int* returnSize)
{
    struct sep record[4];
    struct valid *list = NULL;
    restore_ip((const char *) s, record, &list, 0);
    *returnSize = 0;
    for (struct valid *it = list; it; it = it->next)
        (*returnSize)++;
    char **ans = (char **) malloc(sizeof(char *) * (*returnSize));
    for (int i = 0; i < *returnSize; i++) {
        ans[i] = (char *) malloc(sizeof(char) * (strlen(s) + 3 + 1));
        int sidx = 0, ansidx = 0;
        for (int pos = 0; pos < 4; pos++) {
            for (int j = 0; j < list->width[pos]; j++)
                ans[i][ansidx++] = s[sidx++];
            ans[i][ansidx++] = '.';
        }
        ans[i][ansidx - 1] = '\0';
        
        struct valid *temp = list;
        list = list->next;
        free(temp);
    }
    return ans;
}