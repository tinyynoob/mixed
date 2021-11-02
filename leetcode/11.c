#define min(a,b) (a<b?a:b)

int maxArea(int* height, int heightSize){
    int left, right, ans, temp;
    ans = 0;
    left = 0;
    right = heightSize-1;
    while(left<right)
    {
        temp = (right-left)*min(height[left],height[right]);
        if(temp>ans)
            ans = temp;
        
        if(height[left]<height[right])  //keep the taller one and move another
            left++;
        else
            right--;
    }
    return ans;
}