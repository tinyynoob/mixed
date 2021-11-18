
#define INT_MAX 2147483647

struct hashTable{
    int *table;
    int size;
};

void hash_insert(struct hashTable *hash, const int key);
int hash_function(int key, const int tableSize);
int hash_search(const struct hashTable *hash, const int key);
void hash_clear(struct hashTable *hash);

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum(int* nums, int numsSize, int target, int* returnSize){
    int i, j, toFind, n, *ans;
    struct hashTable *hash;
    hash = (struct hashTable*)malloc(sizeof(struct hashTable));
    hash->table = NULL;
    /*---to ensure tableSize = 2^k, that is, in this binary form 00..0010..00----*/
    n = numsSize<<1;
    for(i=0; n; n>>=1)
        i++;
    n = 1;
    for(; i; i--)
        n<<= 1;
    hash->size = n;
    /*----end set tableSize----*/
    hash->table = (int*)malloc(sizeof(int)*hash->size);
    for(i=0; i<hash->size; i++)  //initialize all the value in hashTable to INT_MAX
        hash->table[i] = INT_MAX;
    
    for(i=0; i<numsSize; i++){
        toFind = target-nums[i];
        if(hash_search(hash, toFind) != -1){  //if found answer
            ans = (int*)malloc(sizeof(int)*2);
            j = 0;
            while(nums[j] != toFind)    //find the number's index in nums[]
                j++;
            ans[0] = j;
            ans[1] = i;
            hash_clear(hash);
            *returnSize = 2;
            return ans;
        }
        hash_insert(hash, nums[i]); //if the numbers in hashTable can not form an answer with nums[i], insert num[i] to hashTable
    }
    hash_clear(hash);
    *returnSize = 0;
    return NULL;
}

void hash_insert(struct hashTable *hash, const int key){
    int value;
    value = hash_function(key, hash->size);
    while(hash->table[value] != INT_MAX){   //linear probing (modular addition)
        value++;
        value = value&((hash->size)-1);
    }
    hash->table[value] = key;
}

int hash_function(int key, const int size){
    if(key<0)
        key = ~key;
    key = key ^ (key >> 4);
    key = ~key + (key << 3);
    key = key ^ (key >> 7);
    return key&(size-1);    //since size-1=00...011...11, the bit operation & is equivalent to %
}

int hash_search(const struct hashTable *hash, const int key){   //if found, return its index in hashTable
    int value;
    value = hash_function(key, hash->size);
    while(hash->table[value]!=key){
        if(hash->table[value] == INT_MAX) //means that it is not in the table 
            return -1;
        value++;           //linear probing (modular addition)
        value = value&((hash->size)-1);
    }
    return value;
}

void hash_clear(struct hashTable *hash){
    free(hash->table);
    free(hash);
}


