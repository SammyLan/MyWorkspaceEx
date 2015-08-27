#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
	vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
		sort(candidates.begin(), candidates.end());
		combinationSum(candidates, 0, target);
		return output_;
	}

	void combinationSum(vector<int>& candidates, int beg, int target)
	{
		int pre = -1;
		for (int i = beg; i < candidates.size(); ++i)
		{
			int val = candidates[i];
			if (val == pre)
			{
				continue;
			}
			pre = val;
			if (target < val)
			{
				break;
			}
			output.push_back(val);
			if (target == val)
			{
                output_.push_back(output);
				output.pop_back();
				break;
			}
			combinationSum(candidates, i + 1, target - val);
			output.pop_back();
		}
	}
	vector<vector<int>> output_;
	vector<int>  output;
};