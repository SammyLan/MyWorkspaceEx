#include "stdafx.h"
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;
/*
题目:
给你一个整数 list L,如 L=[2,-3,4,50],求L的一个非连续子序列,使其和最大,输出最大子序列的和.
这里非连续子序列的定义是,子序列中任意相邻的两个数在原序列都不相邻.
例如:对于L = [2 ,-2,3,50],输出52(分析:很明显,该列表最大非连续子序列为[2,50].
[-1,2,5,-3,7,9,15,10,-5,-20,30,70,50,-90]
分析:
d[i] = max(L[i],max(d[i-1],d[i-2] + L[i]) )
*/
int MaxSumSubArray(vector<int> & A)
{
	if(A.size() < 2)
	{
		return A[0];
	}
	int pre = A[0];
	int cur = max(A[1],pre);
	for(size_t i = 2; i < A.size(); ++i)
	{
		int tmp =cur;
		cur = max(A[i],max(cur,pre + A[i]));
		pre = tmp;
	}
	return cur;
}

void Test_MaxSumSubArray()
{
	int arr[] = 
	//{2,1};
	{-1,2,5,-3,7,9,15,10,-5,-20,30,70,50,-90,2,3,10,5};
	cout<<MaxSumSubArray(vector<int>(arr,arr +sizeof(arr)/sizeof(arr[0])));
}