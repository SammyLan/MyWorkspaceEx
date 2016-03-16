#include <limits>
#include<iostream>
#include <algorithm> 
using namespace std;
/*
https://oj.leetcode.com/problems/maximum-product-subarray/submissions/
Find the contiguous subarray within an array (containing at least one number) which has the largest product.

For example, given the array [2,3,-2,4],
the contiguous subarray [2,3] has the largest product = 6.
����:
��0Ϊ�ָ��ָ�sub array
��ÿ��sub array�������(Product)
1.����˻�Ϊ����sub array������Ϊ
	1)�Ե�һ������Ϊ�ֽ�,�ֳ���������,ȡ���˻�
	2)�����һ������Ϊ�ּ�,�ֳ�����,ȡ���˻�
	3)ȡǰ���������˻�
2.����sub array��ΪProduct
����sub array��������Ϊ����
*/
class Solution {
public:
    int maxProduct(int A[], int n) {
        int beg = 0;
        int product = 1;
        int ret = numeric_limits<int>::min();
		int end = 0;
        for(; end < n; ++end )
        {
            if(A[end] == 0)
            {
				if(ret < 0)
				{
					ret = 0;
				}
				if(beg == end)
				{
					beg = end +1;
					continue;
				}
                if(product < 0)
                {
                    product = maxProduct(A, beg,end,product);
                }
                if(product > ret)
                {
                    ret = product;
                }
                product = 1;
                beg = end + 1;
            }
            else
            {
                product *= A[end];
            }
        }
		if(beg < end)
		{
			if(product < 0)
			{
				product = product = maxProduct(A, beg,end,product);
			}
			if(product > ret)
			{
				ret = product;
			}
		}
		return ret;
    }
private:
    int maxProduct(int A[], int beg,int end,int product)
    {
        if((end - beg) == 1)
        {
            return product;
        }
        int left = 1;
        int right =1;
        int i = beg;
        for(; i < end; ++i)
        {
            if(A[i] < 0 )
            {
                break;
            }
            left*= A[i];
        }
        right = (product/left)/A[i];
        int temp_max1 = max(left,right);
        int j = end - 1;
        left = 1;
        right =1;
        for(; j > i; --j)
        {
            if(A[j] < 0 )
            {
                break;
            }
            right*= A[j];
        }
        left =  (product/right)/A[j];
        int temp_max2 = max(left,right);
        return max(temp_max1,temp_max2);
        
    }
};
int main()
{
	int A[] = {2,-1,-2};

	Solution sln;
	std::cout<<sln.maxProduct(A, sizeof(A)/sizeof(A[0]));
}
/*
public int maxProduct(int[] A){
        int curMax = A[0], curMin = A[0], ans = A[0];
        for(int i =1; i < A.length; i++){
            int temp = curMin * A[i];
            curMin = Math.min(A[i], Math.min(curMax * A[i], temp));
            curMax = Math.max(A[i], Math.max(curMax * A[i], temp));
            ans = Math.max(ans, curMax);
        }
        return ans;
    }
*/