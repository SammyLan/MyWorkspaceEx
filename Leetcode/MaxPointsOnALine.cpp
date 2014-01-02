#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
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

class Solution {
	static double make_double(int x,int y)
	{
		struct pt
		{
			int a;
			int b;
		};
		static union
		{
			long double d;
			pt p;
		};
		d = 0;
		p.a =x;
		p.b =y;
		return d;
	};

	enum
	{
		E_Vertical = 1,
		E_Horizontal,
		E_Same,
		E_None
	};
	struct slopeInfo {
		int type;
		int count;
		double slope;
		slopeInfo() : type(E_None),count(0),slope(0.0){}

		bool operator ==(slopeInfo const & item) 
		{

			return (item.type == type)&&(item.slope == slope) ;
		}
	};
public:
    int maxPoints(vector<Point> &points) {
		int const size = (int)points.size();
		if(size <=2)
		{
			return size;
		}
		int max = 2;
		vector<vector<slopeInfo> > info;
		info.resize(size);
		slopeInfo item;
		for(int i = 1; i < size; ++i)
		{
			int tmpMax = 2;
			vector<slopeInfo> &itemInfo = info[i];
			itemInfo.reserve(i);
			for(int j = i -1; j >= 0;--j)
			{
				if( points[i].x == points[j].x)
				{				
					if(points[i].y == points[j].y)
					{
						vector<slopeInfo> &preItemInfo = info[j];
						for(vector<slopeInfo>::iterator itPre = preItemInfo.begin(); itPre != preItemInfo.end(); ++itPre)
						{
							vector<slopeInfo>::iterator it = find(itemInfo.begin(),itemInfo.end(),*itPre);
							if(it == itemInfo.end())
							{
								slopeInfo curitem = *itPre;
								curitem.count = itPre->count + 1;
								itemInfo.push_back(curitem);
								if(tmpMax < curitem.count)
								{
									tmpMax = curitem.count;
								}
							}
						}
						item.type = E_Same;
						item.slope = make_double(points[i].x,points[i].y);
						vector<slopeInfo>::iterator it = find(itemInfo.begin(),itemInfo.end(),item);
						if(it == itemInfo.end())
						{
							item.count =2;
							itemInfo.push_back(item);
							if(tmpMax < item.count)
							{
								tmpMax = item.count;
							}
						}
						continue;
					}
					else
					{
						item.slope = points[i].x;
						item.type = E_Vertical;
					}
					
				}
				else if(points[i].y == points[j].y)
				{					
					item.slope = points[i].y;
					item.type = E_Horizontal;
				}
				else
				{
					item.type = E_None;
					item.slope = (long double)(points[i].x- points[j].x)/(points[i].y- points[j].y);
				}
				
				vector<slopeInfo>::iterator iteri = find(itemInfo.begin(),itemInfo.end(),item);
				if(iteri == itemInfo.end())
				{
					vector<slopeInfo> &preItemInfo = info[j];
					vector<slopeInfo>::iterator iterj  = find(preItemInfo.begin(),preItemInfo.end(),item);
					if(iterj != preItemInfo.end())
					{
						item.count = iterj->count +1;						
					}
					else
					{
						slopeInfo itemTmp;
						itemTmp.slope = make_double(points[j].x,points[j].y);
						itemTmp.type = E_Same;
						vector<slopeInfo>::iterator iterTmp  = find(preItemInfo.begin(),preItemInfo.end(),itemTmp);
						if(iterTmp != preItemInfo.end())
						{
							item.count = 1 + iterTmp->count;
						}
						else
						{
							item.count = 2;
						}
					}
					itemInfo.push_back(item);
					if(item.count > tmpMax)
					{
						tmpMax = item.count;
					}
				}
			}
			if(tmpMax > max)
			{
				if(tmpMax > max)
				{
					max = tmpMax;
				}
			}
		}
		return max;
    }
};

/*
test case:
[(0,0),(-1,-1),(2,2)]


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