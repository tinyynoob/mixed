

double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size){
    int idx, idx1, idx2, size;
    int *merged;
    double ans;
    size = nums1Size+nums2Size;
    merged = (int*)malloc(sizeof(int)*size);
    idx1 = 0;
    idx2 = 0;
    for(idx=0; idx<size; idx++)  //merged
    {
        if(idx1>=nums1Size)
            merged[idx] = nums2[idx2++];
        else if(idx2>=nums2Size)
            merged[idx] = nums1[idx1++];
        else if(nums1[idx1]<nums2[idx2])
            merged[idx] = nums1[idx1++];
        else
            merged[idx] = nums2[idx2++];
    }
    if(size==1)
        ans = (double)merged[0];
    else if(size%2)
        ans = (double)merged[size/2];
    else
        ans = (double)(merged[size/2-1]+merged[size/2])/2;
    free(merged);
    return ans;
}