
void hash_insert(int *hashTable, int key, const int tableSize);
int hash_function(int key, const int tableSize);
int hash_search(int *hashTable, int key, const int tableSize);

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum(int* nums, int numsSize, int target, int* returnSize){
    int i, j, gap, value, *ans;
    int *hashTable, tableSize;
    
    tableSize = numsSize<<1;
    for(i=0; tableSize; tableSize>>1)
        i++;
    tableSize = 1;
    for(; i; i--)
        tableSize<<1;
        
    hashTable = (int*)malloc(sizeof(int)*tableSize);
    for(i=0; i<tableSize; i++)
        hashTable[i] = -1;
    for(i=0; i<numsSize; i++)
        hash_insert(hashTable, nums[i], tableSize);
    
    for(i=0; i<numsSize; i++){
        gap = target-nums[i];
        value = hash_function(gap, tableSize);
        if(hashTable[value]!=-1){
            for(j=0; j<numsSize; j++){
                if(nums[j]==gap && j!=i){
                    ans = (int*)malloc(sizeof(int)*2);
                    ans[0] = i;
                    ans[1] = j;
                    free(hashTable);
                    *returnSize = 2;
                    return ans;
                }
            }
        }
    }
    free(hashTable);
    *returnSize = 0;
    return NULL;
}

void hash_insert(int *hashTable, int key, const int tableSize){
    int value;
    value = hash_function(key, tableSize);
    while(hashTable[value]!=-1) //keep hashing to find an empty position
        value = hash_function(value, tableSize);
    hashTable[value] = key;
}

int hash_function(int key, const int size){
    /* the hash function is from https://ppt.cc/fO5Jrx */

    return (key*7)%size;
}

int hash_search(int *hashTable, int key, const int tableSize){
    int value;
    value = hash_function(key, tableSize);
    if(hashTable[value]==-1)    //not found
        return -1;
    else{
        while(hashTable[value]!=key)
            value = hash_function(value, tableSize);
        return value;
    }
    return -1; //useless
}


