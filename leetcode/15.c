
/*-----use the result of 1 and 912-----*/
#define INT_MAX 2147483647
#define swap(a,b,temp) {temp=a; a=b; b=temp;}

struct hashTable{
    int *table;
    int size;
};

void hash_insert(struct hashTable *hash, const int key);
int hash_function(int key, const int tableSize);
int hash_search(const struct hashTable *hash, const int key);
void hash_clear(struct hashTable *hash);
int* sortArray(int* nums, int numsSize);
void quicksort(int *nums, const int left, const int right);
void insertionSort(int *nums, const int left, const int right);

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** threeSum(int* nums, int numsSize, int* returnSize, int** returnColumnSizes){
    struct hashTable *hash;
    int i, n, mid, right, target;
    int **ans;
    
    *returnSize = 0;
    if(!numsSize)
        return nums;
    
    nums = sortArray(nums, numsSize);
    
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
    
    ans = (int**)malloc(sizeof(int*)*2000);  //guess a max size
    *returnColumnSizes = (int*)malloc(sizeof(int)*2000);
    
    
    for(right=numsSize-1; right; right--){
        for(i=0; i<hash->size; i++) //reset hash table
            hash->table[i] = INT_MAX;
        for(mid=0; mid<right; mid++){
            target = 0-nums[right]-nums[mid];
            if(hash_search(hash, target) != -1){  //if found an answer
                n = 0;
                for(i=0; i<*returnSize; i++)   //if this triplet is duplicate, skip it
                    if(target==ans[i][0] && nums[mid]==ans[i][1] && nums[right]==ans[i][2]){
                        n = 1;
                        break;
                    }
                if(n)
                    continue;
                
                (*returnColumnSizes)[*returnSize] =  3;
                ans[*returnSize] = (int*)malloc(sizeof(int)*3);
                ans[*returnSize][0] = target;
                ans[*returnSize][1] = nums[mid];
                ans[*returnSize][2] = nums[right];
                (*returnSize)++;
            }
            hash_insert(hash, nums[mid]);
        }
    }
    hash_clear(hash);
    return ans;
}


/*-----the contents below is copied from 2sum--------*/

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


/*-----the contents below is copied from 912 and modify a little-----*/

int* sortArray(int* nums, int numsSize){
    if(nums)
        quicksort(nums, 0, numsSize-1);
    return nums;
}

void quicksort(int *nums, const int left, const int right){
    int temp, i, j, mid, pivotIndex;
    if(left>=right)
        return;
    else if(right-left <= 20)   //if too few elements, change to insertion sort
        insertionSort(nums, left, right);
    else{
        /*select the median of {nums[left], nums[mid], nums[right]} as pivot*/
        mid = (left+right)/2;
        if(nums[left]>nums[mid]&&nums[mid]>nums[right])
            pivotIndex = mid;
        else if(nums[right]>nums[mid]&&nums[mid]>nums[left])
            pivotIndex = mid;
        else if(nums[right]>nums[left]&&nums[left]>nums[mid])
            pivotIndex = left;
        else if(nums[mid]>nums[left]&&nums[left]>nums[right])
            pivotIndex = left;
        else
            pivotIndex = right;
        swap(nums[pivotIndex], nums[right], temp);     //put pivot on right
        /*end selecting pivot*/
        
        /*
        i<=j always
        i will stay at bigger num, and j keeps moving right to find a smaller num, if find, swap(nums[i],nums[j])
        At the end, swap(nums[i],nums[right])
        */
        i = left;
        for(j=left; j<right; j++){
            if(nums[j]<=nums[right]){
                swap(nums[i], nums[j], temp);
                i++;
            }
        }
        swap(nums[i], nums[right], temp);
        quicksort(nums, left, i-1);
        quicksort(nums, i+1, right);
    }
}

void insertionSort(int *nums, const int left, const int right){
    int i, j, smallerNum;
    if(left>=right)
        return;
    for(i=left+1; i<=right; i++){
        if(nums[i]<nums[i-1]){
            smallerNum = nums[i];
            for(j=i-1; j>=left&&smallerNum<nums[j]; j--)
                nums[j+1] = nums[j];
            nums[j+1] = smallerNum;
        }
    }
}
