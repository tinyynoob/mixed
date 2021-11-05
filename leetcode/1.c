
void hash_insert(int *hashTable, int key, const int numsSize);
int hash_function(int key, const int size);
int hash_search(int *hashTable, int key, const int numsSize);

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum(int* nums, int numsSize, int target, int* returnSize){
    int i, gap, *ans;
    int *hashTable, tableSize;
    
    tableSize = 2.3*numsSize;   //the last 0.2 is the space for collision
    hashTable = (int*)malloc(sizeof(int)*tableSize);
    for(i=0; i<tableSize; i++)
        hashTable[i] = numsSize+1;
    for(i=0; i<numsSize; i++)
        hash_insert(hashTable, nums[i], numsSize);
    for(i=0; i<numsSize; i++){
        gap = target-nums[i];
        if(hash_search(hashTable, gap, numsSize)!=-1){
            ans = (int*)malloc(sizeof(int)*2);
            ans[0] = i;
            ans[1] = hash_search(hashTable, gap, numsSize);
            free(hashTable);
            *returnSize = 2;
            return ans;
        }
    }
    free(hashTable);
    *returnSize = 0;
    return NULL;
}

void hash_insert(int *hashTable, int key, const int numsSize){
    int value, i;
    value = hash_function(key, 2*numsSize);
    if(hashTable[value]==numsSize+1)
        hashTable[value] = key;
    else{
        i = 2*numsSize+1;   //where is reserved for collisions
        while(hashTable[i]!=numsSize+1) //find a place not occupied
            i++;
        hashTable[i] = key;
    }
}

int hash_function(int key, const int size){
    /* the hash function is from https://ppt.cc/fO5Jrx */
    key = ~key + (key << 15); // key = (key << 15) - key - 1;
    key = key ^ (key >> 12);
    key = key + (key << 2);
    key = key ^ (key >> 4);
    key = (key + (key << 3)) + (key << 7);
    key = key ^ (key >> 16);
    return key & size;    //key & (2*numsSize)
}

int hash_search(int *hashTable, int key, const int numsSize){
    int value, i;
    value = hash_function(value, 2*numsSize);
    if(hashTable[value]==numsSize+1)    //not found
        return -1;
    else{
        if(hashTable[value]==key)
            return value;
        else
            for(i=2*numsSize+1; hashTable[i]==key; i++)
                return i;
    }
    return 0; //useless
}


