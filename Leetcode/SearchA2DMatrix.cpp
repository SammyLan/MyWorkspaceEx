#include <iostream>
#include <vector>
using namespace std;

/*
http://oj.leetcode.com/problems/search-a-2d-matrix/
Write an efficient algorithm that searches for a value in an m x n matrix. This matrix has the following properties:

Integers in each row are sorted from left to right.
The first integer of each row is greater than the last integer of the previous row.

For example,

Consider the following matrix: 

test case
[
[1,   3,  5,  7],
[10, 11, 16, 20],
[23, 30, 34, 50]
]
*/
class Solution {
public:
	bool searchMatrix(vector<vector<int> > &matrix, int target) {		
		int sizeX = (int)matrix.size();
		if (0 == sizeX)
		{
			return false;
		}
		int sizeY = (int)matrix[0].size();
		return searchMatrix(matrix,target,0,0,sizeX , sizeY);
	}
private:
	bool searchMatrix(vector<vector<int> > &matrix, int target,int begX,int begY,int sizeX,int sizeY) 
	{
		if (begX >= sizeX
			||begY >= sizeY)
		{
			return false;
		}
		int midX = ((begX + sizeX )>>1);
		int midY = ((begY +sizeY)>>1);
		
		int val = matrix[midX][midY];
		if ( val == target)
		{
			return true;
		}

		if (searchMatrix(matrix,target,begX,midY + 1 ,midX,sizeY)) //右上
		{
			return true;
		}
		if(searchMatrix(matrix,target,midX + 1,begY,sizeX,midY))//左下
		{
			return true;
		}
		if (target < val)
		{
			if (searchMatrix(matrix,target,begX,begY,midX,midY))//左上
			{
				return true;
			}

			if (BinarySearchH(matrix,target,begY,midY,midX))
			{
				return true;
			}
			if (BinarySearchV(matrix,target,begX,midX,midY))
			{
				return true;
			}					
		}
		if (searchMatrix(matrix,target,midX + 1,midY + 1,sizeX,sizeY)) //右下
		{
			return true;
		}
		if (BinarySearchH(matrix,target,midY + 1,sizeY,midX))
		{
			return true;
		}
		if (BinarySearchV(matrix,target,midX + 1,sizeX,midY))
		{
			return true;
		}

		
	}
private:
	//行查找
	bool BinarySearchH(vector<vector<int> > &matrix, int target,int beg, int end,int  i)
	{
		if (beg >= end)
		{
			return false;
		}
		int mid = 0;
		vector<int> & vec  = matrix[i];
		while(beg < end)
		{
			mid = (beg + end)>>1;
			if (vec[mid] ==  target)
			{
				return true;
			}
			if (vec[mid] >  target)
			{
				end = mid;
			}
			else
			{
				beg = mid +1;
			}
		}
		return false;
	}
	//列查找
	bool BinarySearchV(vector<vector<int> > &matrix, int target,int beg, int end,int j)
	{
		if (beg >= end)
		{
			return false;
		}
		int mid = 0;
		while(beg < end)
		{
			mid = (beg + end)>>1;
			if (matrix[mid][j] ==  target)
			{
				return true;
			}

			if (matrix[mid][j] >  target)
			{
				end = mid;
			}
			else
			{
				beg = mid +1;
			}
		}
		return false;
	}
};

int main()
{
	vector<vector<int> > matrix;
	char ch;
	cin>>ch;
	int val;
	while (cin>>ch)
	{
		if (ch != '[')
		{
			break;
		}
		
		vector<int> vec;
		while(cin>>val)
		{
			vec.push_back(val);
			cin >> ch;
			if (ch != ',')
			{
				break;
			}
		}
		matrix.push_back(vec);
		cin>>ch;
		if (ch != ',')
		{
			break;
		}
	}
	Solution solution;
	while (cin>>val)
	{
		cout<<solution.searchMatrix(matrix,val)<<endl;
	}
	return 0;
}