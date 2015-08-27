#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int n  = nums.size();
        k = k%n;
        if(k == 0)
        {
            return;
        }
        reverse(nums,0,n);
        reverse(nums,0,k);
        reverse(nums,k,n);
    }
    void reverse(vector<int>& nums, int beg,int end)
    {
        --end;
        while(beg < end)
        {
            swap(nums[beg],nums[end]);
            ++beg;
            --end;
        }
    }
};