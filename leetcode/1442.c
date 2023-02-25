
int countTriplets(int* arr, int arrSize)
{
    int ans = 0;
    for (int i = 0; i < arrSize - 1; i++) {
        int axorb = arr[i];
        for (int k = i + 1; k < arrSize; k++) {
            axorb ^= arr[k];
            if (axorb == 0)   // implies a == b
                ans += k - i;
        }
    }
    return ans;
}

