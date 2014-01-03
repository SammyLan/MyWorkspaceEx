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
#include <algorithm>
#include <limits>
using namespace std;
inline bool operator < (Point const &pt1,Point const &pt2)
{
	return (pt1.x == pt2.x)?(pt1.y < pt2.y):(pt1.x < pt2.x);
}
inline bool operator == (Point const &pt1,Point const &pt2)
{
	return (pt1.x == pt2.x) && (pt1.y == pt2.y);
}
#define s_min numeric_limits<double>::min()
#define s_max numeric_limits<double>::max()
#define s_zero 0.0;

class Solution {
	typedef double DOUBLE;
	typedef map<DOUBLE,int> MapD2Int;
public:
    int maxPoints(vector<Point> &points) {
		int const size = (int)points.size();
		if(size <= 2)
		{
			return size;
		}
		std::sort(points.begin(),points.end());
		int max = 2;		
		MapD2Int  * info = new MapD2Int[size];
		DOUBLE slope;
		for(int i = 1; i < size; ++i)
		{
			MapD2Int &itemInfo = info[i];
			Point curPt = points[i];
			if (curPt == points[i - 1])
			{
				int tmpMax = CopyInfo(itemInfo,info[i-1]);
				if (max < tmpMax)
				{
					max = tmpMax;
				}
				continue;
			}
			
			int ix = curPt.x;
			int iy = curPt.y;
			for(int j = i -1; j >= 0;--j)
			{
				Point ptj = points[j];
				/*if (ptj == points[j + 1])
				{
					++itemInfo[slope];
					continue;
				}*/
				int jx = ptj.x;
				int jy = ptj.y;
				MapD2Int const &itemInfoPre = info[j];				

				if( ix == jx) //垂直
				{
					slope =  s_max;					
				}				
				else if(iy == jy) //水平
				{
					slope = s_zero;					
				}
				else //其他
				{
					slope = (DOUBLE) (ix- jx)/(iy- jy);
				}
				pair <MapD2Int::iterator, bool> pairInsert = itemInfo.insert(make_pair(slope,2));
				if(!pairInsert.second)
				{
					++pairInsert.first->second;
				}				
			}
			for (MapD2Int::iterator it = itemInfo.begin(); it != itemInfo.end();++it)
			{
				if(max < it->second)
				{
					max = it->second;
				}
			}			
		}
		delete []info;
		return max;
    }
private:
	int CopyInfo(MapD2Int &itemInfo,MapD2Int const &itemInfoPre)
	{
		int max = 2;
		itemInfo = itemInfoPre;
		for(MapD2Int::iterator it = itemInfo.begin(); itemInfo.end() != it; ++it)
		{
			++it->second;
			if (max < it->second)
			{
				max = it->second;
			}
		}
		itemInfo.insert(make_pair(s_min,2));
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