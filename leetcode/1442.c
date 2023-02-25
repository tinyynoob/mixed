
int countTriplets(int* arr, int arrSize)
{
    int ans = 0;
    for (int i = 0; i < arrSize - 1; i++) {
        int a = arr[i];
        for (int j = i + 1; j < arrSize; j++) {
            int b = arr[j];
            for (int k = j; k < arrSize; k++) {
                if (a == b)
                    ans++;
                if (k + 1 < arrSize)
                    b ^= arr[k + 1];
            }
            a ^= arr[j];
        }
    }
    return ans;
}

