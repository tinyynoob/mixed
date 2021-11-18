#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define INT_MAX 2147483647

int* twoSum(int* nums, int numsSize, int target, int* returnSize);
void hash_insert(int *hashTable, int key, const int tableSize);
int hash_function(int key, const int tableSize);
int hash_search(int *hashTable, int key, const int tableSize);

int main()
{
    int i, *p;
    int a[10]={3,2,4};
    twoSum(a, 3, 6, p);
    system("pause");
    return 0;
}

int* twoSum(int* nums, int numsSize, int target, int* returnSize){
    int i, j, gap, n, *ans;
    int *hashTable, tableSize;
    
    /*---to ensure tableSize = 2^n-1, that is, in this form 00..0011..11----*/
    tableSize = numsSize<<1;
    for(i=0; tableSize; tableSize>>=1)
        i++;
    tableSize = 1;
    for(; i; i--)
        tableSize<<= 1;
    tableSize--;
    
    hashTable = (int*)malloc(sizeof(int)*tableSize);
    for(i=0; i<tableSize; i++)  //init hashTable
        hashTable[i] = INT_MAX;
    
    for(i=0; i<numsSize; i++){
        gap = target-nums[i];
        n = hash_search(hashTable, gap, tableSize);
        if(n != -1){  //if found
            ans = (int*)malloc(sizeof(int)*2);
            for(j=0; nums[j]!=gap; j++)
                ;
            ans[0] = j;
            ans[1] = i;
            free(hashTable);
            //*returnSize = 2;
            return ans;
        }
        hash_insert(hashTable, nums[i], tableSize); //if num[i] can not form an answer, insert it to hashTable
    }
    free(hashTable);
    //*returnSize = 0;
    return NULL;
}

void hash_insert(int *hashTable, int key, const int tableSize){
    int value;
    value = hash_function(key, tableSize);
    while(hashTable[value] != INT_MAX){ //linear probing
        value++;
        value = value&tableSize; //modular add
    }
    hashTable[value] = key;
}

int hash_function(int key, const int size){
    /* the hash function is from https://ppt.cc/fO5Jrx */
    if(key<0)
        key = ~key;
    key = key ^ (key >> 4);
    key = (key + (key << 3)) + (key << 7);
    key = key ^ (key >> 5);
    return key&size;
}

int hash_search(int *hashTable, int key, const int tableSize){
    int value;
    value = hash_function(key, tableSize);
    while(hashTable[value]!=key){
        if(hashTable[value] == INT_MAX) //not found
            return -1;
        value++;
        value = value&tableSize;
    }
    return value;
}



