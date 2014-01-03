// Console.cpp : 定义控制台应用程序的入口点。
//

#include <vector>
#include <map>
#include <iostream>
using namespace std;

/*
http://oj.leetcode.com/submissions/detail/2427456/
Given an unsorted array of integers, find the length of the longest consecutive elements sequence.

For example,
Given [100, 4, 200, 1, 3, 2],
The longest consecutive elements sequence is [1, 2, 3, 4]. Return its length: 4.

Your algorithm should run in O(n) complexity. 

*/
class Solution {
	typedef map<unsigned int,unsigned int>  InfoItem;
	typedef vector<InfoItem > InfoList;
public:
     int longestConsecutive(vector<int> &num) {
		size_t size = num.size();
		if(size == 0)
		{
			return 0;
		}
		
		InfoList infoList;
		infoList.resize(size);

		for(size_t i = 0; i < size; ++i)
		{
			long long val = num[i] + 2147483648;	//确保数据都落在0以上的区间
			unsigned int  a = (unsigned int) val  / size;
			unsigned int b = (unsigned int) val  %  size;
			infoList[b].insert(make_pair(a,1));
		}
		return GetLCS(infoList);
    }
private:
	int GetLCS(InfoList & infoList)
	{
		size_t size = infoList.size();
		size_t ret = 1;

		//如果当前的商跟前一元素的商一致,则表示连续
		for(size_t i = 1; i < size; ++i)
		{
			InfoItem & itemPre = infoList[i -1];
			InfoItem & item = infoList[i];
			for(InfoItem::iterator it = item.begin(); it != item.end(); ++it)
			{
				unsigned int a = it->first;
				InfoItem::iterator itPre = itemPre.find(a);
				if(itPre != itemPre.end())
				{
					it->second =  itPre->second + 1;
					if(it->second > ret)
					{
						ret = it->second;
					}
				}				
			}
		}

		//对于最后元素,还要跟第一个元素比较,看它的商是否比最后元素的商多1,如果是,则为连续
		size_t iLastIndex = size -1;
		InfoItem & itemLast = infoList[ iLastIndex];
		for(InfoItem::iterator it = itemLast.begin(); it != itemLast.end(); ++it)
		{
			size_t a = it->first +1;
			size_t count = it->second;
			for(size_t i = 0; i < iLastIndex; ++i)
			{
				InfoItem::iterator itCur = infoList[i].find(a);
				if(itCur != infoList[i].end())
				{
					++count;
				}
				else
				{
					break;
				}
			}
			if(count > ret)
			{
				ret = count;
			}
		}
		
		return (int)ret ;
	}
};

int main(int argc, char * argv[])
{
	//int arr[] = {100,4,5,200,1,3, 7, 6,2};
	int arr[] = {-1,-2,-3,-4,-5};
	vector<int> vec;
	for(size_t i = 0; i < sizeof(arr)/sizeof(arr[0]); ++i)
	{
		vec.push_back(arr[i]);
	}

	Solution solution;
	cout<<solution.longestConsecutive(vec)<<endl;
	int i = 2147483648; 
	cout <<i<<endl;
	return 0;
}

