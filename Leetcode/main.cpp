#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;


struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};


struct Info
{
	int len;
	int index;
};

struct Compare 
{
	bool operator()(Info const & item1,Info const & item2)
	{
		return item1.len < item2.len;
	}
};


/**
* Definition for singly-linked list.
* struct ListNode {
*     int val;
*     ListNode *next;
*     ListNode(int x) : val(x), next(NULL) {}
* };
*/
class Solution {
public:
	ListNode *mergeKLists(vector<ListNode *> &lists) {
		if(lists.empty())
		{
			return NULL;		}
		
		vector<ListNode *> tmpList = lists;		
		vector<Info> vecInfo;
		vecInfo.reserve(lists.size());
		Info info;
		for(int i = 0; i < (int)tmpList.size(); ++i)
		{
			int len = GetLen(tmpList[i]);
			if (len != 0)
			{
				info.len = len;
				info.index = i;
				vecInfo.push_back(info);
			}
		}

		Compare comp;
		make_heap(vecInfo.begin(),vecInfo.end(),comp);
		while (vecInfo.size() >= 2)
		{
			Info info1 = vecInfo[0];
			pop_heap(vecInfo.begin(),vecInfo.end(),comp);
			vecInfo.pop_back();

			Info info2 = vecInfo[0];
			pop_heap(vecInfo.begin(),vecInfo.end(),comp);
			vecInfo.pop_back();
			
			info1.len = info1.len + info2.len;
			tmpList[info1.index] = Merge(tmpList[info1.index],tmpList[info2.index]);
			vecInfo.push_back(info1);
			push_heap(vecInfo.begin(),vecInfo.end(),comp);

		}
		ListNode *head = NULL;
		if (vecInfo.size() > 0)
		{
			head = tmpList[vecInfo[0].index] ;
		}
		return head;
	}
	static ListNode  * Merge(ListNode * head1,ListNode* head2)
	{
		if(head1->val > head2->val)
		{
			swap(head1,head2);
		}
		ListNode * head = head1;
		ListNode * pre1 = NULL;
		while(head1 != NULL && head2 != NULL)
		{
			int val2 = head2->val;
			while( head1!= NULL && head1->val <= val2)
			{
				pre1 = head1;
				head1 = head1->next;
			}
			pre1->next = head2;
			if(head1 == NULL)
			{
				break;
			}
			head2 = head1;
			head1 = pre1->next;
		}
		return head;
	}
	static int GetLen(ListNode * head)
	{
		int len = 0;
		while(head != NULL)
		{
			head = head->next;
			++len;
		}
		return len;
	}
};

int main()
{
	int arr[] = {10,20,30,40,50,60,70};
	vector<int> vec(arr,arr + sizeof(arr)/sizeof(int));
	make_heap(vec.begin(),vec.end());
	vec.push_back(90);
	push_heap(vec.begin(),vec.end());
	vec.push_back(100);
	push_heap(vec.begin(),vec.end());

	while (!vec.empty())
	{
		int val = vec[0];
		pop_heap(vec.begin(),vec.end());
		vec.pop_back();
		cout<<val<<endl;;
	}
	return 0;
}