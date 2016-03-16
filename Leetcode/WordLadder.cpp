#include <limits> 
#include <vector>
#include <unordered_set>
#include <string>

using namespace std;
/*class Solution {
public:
    int ladderLength(string start, string end, unordered_set<string> &dict) {
        int size = dict.size();
        
        unordered_set<string> dictEx;
        dictEx.insert(start);
		vector<unordered_set<string>::iterator> arrStart;
		arrStart.push_back(dictEx.begin());
		
		vector<unordered_set<string>::iterator> newDict;
		newDict.reserve(size);
		for(unordered_set<string>::iterator it = dict.begin(); it != dict.end(); ++it)
		{
		    newDict.push_back(it);
		}
		
        return BFS(arrStart,end,newDict,0);
    }
    int BFS(vector<unordered_set<string>::iterator> & start, string const & end, vector<unordered_set<string>::iterator> &  dict,int step)
    {
		if(start.size() == 0)
			return 0;
		vector<unordered_set<string>::iterator> newStart;
		newStart.reserve(dict.size());

		for(vector<unordered_set<string>::iterator>::iterator it = start.begin(); it != start.end(); ++it)
		{
			if(canBeTransformed(*(*it) , end) )
				return step + 2;
		}
		int size =dict.size();
		for(vector<unordered_set<string>::iterator>::iterator it = start.begin(); it != start.end(); ++it)
		{
			for(int i = size -1; i >= 0; --i)
			{
				if(canBeTransformed(*(*it),*(dict[i])))
				{
					newStart.push_back(dict[i]);
					--size;
					dict[i]=dict[size];
				}
			}
		}
		
		dict.resize(size);
		return BFS(newStart,end,dict,step+1);
    }
    bool canBeTransformed(string const & str1,string const &str2)
    {
        char ch = str1[0];
        int count = 0;
        for(size_t i = 0; ch!='\0'; ++i,ch =str1[i])
        {
            if(ch!= str2[i])
            {
                ++count;
            }
            if(count > 1)
            {
                break;
            }
        }
        return count ==1;
    }
};
*/

class Solution {
public:
	int ladderLength(string start, string end, unordered_set<string> &dict)
	{


	}
};
int main()
{
	return 0;
}