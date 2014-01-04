#include <iostream>
using namespace std;
/*
http://oj.leetcode.com/problems/palindrome-number/
Determine whether an integer is a palindrome. Do this without extra space.

click to show spoilers.
Some hints:

Could negative integers be palindromes? (ie, -1)

If you are thinking of converting the integer to string, note the restriction of using extra space.

You could also try reversing an integer. However, if you have solved the problem "Reverse Integer", you know that the reversed integer might overflow. How would you handle such case?

There is a more generic way of solving this problem.

*/


/*
思路:将数字逆转后,跟原数字比较是否相等,负数直接返回false
*/
class Solution {
public:
	bool isPalindrome(int x) {
		if(x<0)
		{
			return false;
		}
		long long val =0; //避免溢出
		long long tmp =x;
		while(x)
		{
			val = val*10 + x%10;
			x/=10;
		}
		return val ==tmp;
	}
};

int main()
{
	int x;
	Solution solution;
	while(cin>>x)
	{
		cout<<solution.isPalindrome(x)<<endl;
	}
}