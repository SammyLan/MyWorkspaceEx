#include <iostream>
using namespace std;

/*http://oj.leetcode.com/problems/sort-list/
Sort a linked list in O(n log n) time using constant space complexity.
*/
//Definition for singly-linked list.
struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
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
	ListNode *sortList(ListNode *head) {
		int const len = GetLen(head);
		int step = 1;
		while (step < len)
		{
			ListNode * preNode = NULL;
			
			ListNode * cur = head;
			int i = 0;
			head = NULL;
			while (i < len)
			{
				ListNode * head1 = cur;
				cur = GetNextList(cur,step,i,len);
				if (cur == NULL)
				{
					if (head == NULL)
					{
						head = head1;
					}
					if (preNode != NULL)
					{
						preNode->next = head1;
					}
					break;
				}

				ListNode *head2= cur;
				cur = GetNextList(cur,step,i,len);
				pair<ListNode *,ListNode*> nodePair = Merge(head1,head2);
				if (preNode)
				{
					preNode->next = nodePair.first;
				}
				if (head == NULL)
				{
					head = nodePair.first;
					
				}
				preNode = nodePair.second;

			}
			step = (step <<1);
		}
		return head;
	}
private:
	int GetLen(ListNode * head)
	{
		int len = 0;		
		while (head)
		{
			++len;
			head = head->next;
		}
		return len;
	}
	pair<ListNode *,ListNode*> Merge(ListNode * head1,ListNode* head2)
	{
		ListNode *  head;
		if (head1->val < head2->val)
		{
			head = head1;
			head1 = head1->next;
		}	
		else
		{
			head = head2;
			head2 = head2->next;
		}
		ListNode *pNode = head;
		while(head1 != NULL
			&& head2 != NULL)
		{
			if (head1->val < head2->val)
			{
				pNode->next = head1;
				pNode = head1;
				head1 = head1->next;
			}	
			else
			{
				pNode->next = head2;
				pNode = head2;
				head2 = head2->next;
			}
		}
		if (head1 != NULL)
		{
			pNode->next = head1;
		}
		else
		{
			pNode->next = head2;
		}
		while (pNode->next != NULL)
		{
			pNode = pNode->next;
		}
		return pair<ListNode*,ListNode*>(head,pNode);
	}

	ListNode * GetNextList(ListNode * head,int step,int & i, int len)
	{
		i += step;
		if (i >= len)
		{
			return NULL;
		}
		for (int j = 1; j < step; ++j)
		{
			head = head->next;
		}
		ListNode * tmp = head;
		head = head->next;
		tmp->next = NULL;
		return head;
	}
};

/*
test case
[1,5,6,347,5,2,99,200,30,12,66,4]
*/
int main()
{
	ListNode * head = NULL;
	ListNode * cur = NULL;
	char ch;
	cin>>ch;
	int val;
	while (cin>>val)
	{
		ListNode * pNode = new ListNode(val);
		if (NULL != cur)
		{
			cur->next = pNode;
			cur = pNode;

		}
		else
		{
			head = cur = pNode;
		}
		cin>>ch;
		if (ch != ',')
		{
			break;
		}
	}
	Solution solution;
	solution.sortList(head);
};