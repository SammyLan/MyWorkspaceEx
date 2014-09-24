#include "stdafx.h"
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

/*
You are given a grid of numbers. A snake sequence is made up of adjacent numbers such that for each number, 
the number on the right or the number below it is +1 or -1 its value. For example, 

1 3 2 6 8 
-9 7 1 -1 2 
1 5 0 1 9 

In this grid, (3, 2, 1, 0, 1) is a snake sequence. 

F(i,j) = 1 + max(f(i-1,j),f(i,j-1)) 	如果P(i,j) 跟P(i-1,j),P(i,j-1)都相连
       = 1 + f(i-1,j)   	 如果P(i,j)跟P(i-1,j)相连
       = 1 + f(i,j - 1) 	 如果P(i,j) 跟P(i,j-1)都相连
       = 1 	 如果P(i,j) 跟P(i-1,j),P(i,j-1)都不相连

*/
bool IsConnect(int a,int b)
{
	return a == (b +1) || a == (b -1);
}

void DFSGenResult(int i,int j,vector<vector<int> > const & grid,vector<vector<int> > const & flags,vector<vector<int> > & result,vector<int> &arr)
{
	arr.push_back(grid[i][j]);
	if(flags[i][j] == 1)
	{
		result.push_back(vector<int>(arr.rbegin(),arr.rend()));
		arr.resize(arr.size() -1);
		return;
	}
	int left_j = j -1;
	int up_i = i - 1;
	if(left_j >= 0 && IsConnect(grid[i][j] , grid[i][left_j]) && (flags[i][j] == flags[i][left_j]+1))
	{
		DFSGenResult(i,left_j,grid,flags,result,arr);
	}
	if (up_i >= 0 && IsConnect(grid[i][j], grid[up_i][j]) && (flags[i][j] == flags[up_i][j]+1))
	{
		DFSGenResult(up_i,j,grid,flags,result,arr);
	}
	arr.resize(arr.size() -1);
}
vector<vector<int> > SnakeSequence(vector<vector<int> > const & grid)
{
	size_t size_n = grid.size();
	size_t size_m = grid[0].size();
	int max_len = 1;

	vector<vector<int> > flags;
	flags.resize(size_n);
	for(size_t i =0; i < size_n; ++i)
	{
		flags[i].resize(size_m);
	}

	flags[0][0] = 1;
	for( size_t i = 1; i < size_m; ++i)
	{
		flags[0][i] = 1;
		if(IsConnect(grid[0][i],grid[0][i-1]))
		{
			flags[0][i] = flags[0][i-1] + 1;
		}
	}
	for( size_t i = 1; i < size_n; ++i)
	{
		flags[i][0] = 1;
		if(IsConnect(grid[i][0],grid[i -1][0]))
		{
			flags[i][0] = flags[i-1][0] + 1;
		}
	}

	for(size_t i = 1; i < size_n; ++i)
	{
		for(size_t j = 2; j < size_m; ++j)
		{
			int & val = flags[i][j];
			val = 1;
			if(IsConnect(grid[i][j],grid[i-1][j]))
			{
				if(IsConnect(grid[i][j],grid[i][j -1]))
				{
					val = max(flags[i][j-1],flags[i-1][j]) + 1;
				}
				else
				{
					val = flags[i -1][j] +1;
				}
				if(val > max_len)
				{
					max_len = val;
				}
			}
			else if(IsConnect(grid[i][j],grid[i][j -1]))
			{
				val = flags[i][j -1] +1;
				if(val > max_len)
				{
					max_len = val;
				}
			}
		}
	}
	vector<vector<int> > arrResult;
	for(size_t i = 1; i < size_n; ++i)
	{
		for(size_t j = 2; j < size_m; ++j)
		{
			if(flags[i][j] == max_len)
			{
				vector<int> arr;
				DFSGenResult(i,j,grid,flags,arrResult,arr);
			}
		}
	}	
	return arrResult;
}

void Test_SnakeSequence()
{
	size_t n = 0,m =0;
	cin >>n>>m;
	vector<vector<int> > grid;
	grid.reserve(n);
	for(size_t i = 0; i < n; ++i)
	{
		vector<int> input;
		input.reserve(m);
		for(size_t j = 0; j < m; ++j)
		{
			int val = 0;
			cin>>val;
			input.push_back(val);
		}
		grid.push_back(input);
	}
	vector<vector<int> > result = SnakeSequence(grid);
	for(vector<vector<int> >::iterator it = result.begin(); it != result.end(); ++it)
	{
		cout<<endl;
		for(vector<int>::iterator itItem = it->begin(); itItem != it->end(); ++ itItem)
		{
			cout<< *itItem<<"  ";
		}
	}
}