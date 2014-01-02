#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <limits>
using namespace std;


/*
http://oj.leetcode.com/problems/max-points-on-a-line/
Given n points on a 2D plane, find the maximum number of points that lie on the same straight line.
*/


struct Point {
	int x;
	int y;
	Point() : x(0), y(0) {}
	Point(int a, int b) : x(a), y(b) {}
	friend bool operator < (Point const &pt1,Point const &pt2)
	{
		return (pt1.x == pt2.x)?(pt1.y < pt2.y):(pt1.x < pt2.x);
	}
};




/**
 * Definition for a point.
 * struct Point {
 *     int x;
 *     int y;
 *     Point() : x(0), y(0) {}
 *     Point(int a, int b) : x(a), y(b) {}
 * };
 */

class Solution {
	typedef double DOUBLE;
public:
    int maxPoints(vector<Point> &points) {
		int const size = (int)points.size();
		if(size <= 2)
		{
			return size;
		}

		int max = 2;
		typedef map<DOUBLE,int> MapD2Int;
		MapD2Int  * info = new MapD2Int[size];
		pair <MapD2Int::iterator, bool> pairInsert;
		for(int i = 1; i < size; ++i)
		{
			int tmpMax = 2;
			int ix = points[i].x;
			int iy = points[i].y;
			
			MapD2Int &itemInfo = info[i];
			for(int j = i -1; j >= 0;--j)
			{
				int jx = points[j].x;
				int jy = points[j].y;
				MapD2Int const &itemInfoPre = info[j];
				DOUBLE slope;
				if( ix == jx)
				{
					//相等
					if(iy == jy)
					{
						for(MapD2Int::const_iterator it = itemInfoPre.begin(); itemInfoPre.end() != it; ++it)
						{
							pairInsert = itemInfo.insert(make_pair(it->first,it->second +1));
							if(pairInsert.second && pairInsert.first->second > tmpMax)
							{
								tmpMax = pairInsert.first->second;
							}
						}
						itemInfo.insert(make_pair(numeric_limits<DOUBLE>::min(),2));
						break;
					}
					//垂直
					else
					{
						slope =  numeric_limits<DOUBLE>::max();
					}
					
				}
				//水平
				else if(iy == jy)
				{
					slope = 0.0;					
				}
				//其他
				else
				{
					slope = (DOUBLE) (ix- jx)/(iy- jy);
				}
				
				MapD2Int::const_iterator it = itemInfo.find(slope);
				if(it != itemInfo.end())
					continue;
				it = itemInfoPre.find(slope);
				if(it != itemInfoPre.end())
				{
					pairInsert = itemInfo.insert(make_pair(slope,it->second + 1));
					tmpMax = std::max(tmpMax,pairInsert.first->second);
				}
				else
				{
					it = itemInfoPre.find(numeric_limits<DOUBLE>::min());
					if(it != itemInfoPre.end())
					{
						pairInsert = itemInfo.insert(make_pair(slope,it->second + 1));
						tmpMax = std::max(tmpMax,pairInsert.first->second);
					}
					else
					{
						itemInfo.insert(make_pair(slope,2));
					}
				}
			}
			if(tmpMax > max)
			{
				max = tmpMax;
			}
		}
		delete []info;
		return max;
    }
};

/*
test case:
[(1,1),(1,1),(1,1)]
3
[(1,1),(1,1),(2,2),(2,2)]
4
[(3,10),(0,2),(0,2),(3,10)]
4
[(-4,1),(-7,7),(-1,5),(9,-25)]

*/
int main()
{
	vector<Point> points;	
	char ch;	
	Point pt;
	cin>>ch;
	while(cin>>ch)
	{
		if(ch != '(')
			break;
		cin>>pt.x;
		cin>>ch;
		cin>>pt.y;
		cin>>ch;
		cin>>ch;
		points.push_back(pt);
		if(ch != ',')
		{
			break;
		}
	}
	Solution solution;
	cout<<solution.maxPoints(points);
	return 0;
}