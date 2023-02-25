#include <string.h>

char *removeDuplicates(char *s, int k)
{
    for (int flag = 1; flag;) {
        flag = 0;
        int newidx = 0;
        for (int i = 0; i < strlen(s);) {
            const char c = s[i];
            int count = 0;  // duplicate count
            do {
                count++;
                i++;
            } while (i < strlen(s) && s[i] == c);
            const int remain = count % k;
            flag |= count >= k ? 1 : 0;
            memset(s + newidx, c, remain);
            newidx += remain;
        }
        s[newidx] = '\0';
    }
    return s;
}
