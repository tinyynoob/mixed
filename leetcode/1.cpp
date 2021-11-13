class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int i, gap;
        vector <int> ans;
        unordered_map<int,int> hash;
        for(i=0; i<nums.size(); i++){
            gap = target-nums[i];
            if(hash.count(gap)){       //if found
                ans.push_back(hash[gap]);
                ans.push_back(i);
                break;
            }
            else
                hash[nums[i]] = i;
        }
        hash.clear();
        return ans;
    }
};