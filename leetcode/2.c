/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */


struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {

	int overflow = 0;
	struct ListNode* newNode, * sum, * p, * p1, * p2;

	sum = NULL;
	p = NULL;
	p1 = l1;
	p2 = l2;

	while (p1 || p2)  //compute and build a stack
	{
		newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
		newNode->next = NULL;
		if (!p1)
		{
			newNode->val = p2->val;
			p2 = p2->next;
		}
		else if (!p2)
		{
			newNode->val = p1->val;
			p1 = p1->next;
		}
		else   //both nonempty
		{
			newNode->val = p1->val + p2->val;
			p1 = p1->next;
			p2 = p2->next;
		}

		newNode->val += overflow;
		overflow = 0;
		if (newNode->val > 9)
		{
			overflow = 1;
			newNode->val -= 10;
		}

		if (!p)
		{
			sum = newNode;
			p = sum;
		}
		else
		{
			p->next = newNode;
			p = p->next;
		}
	}

	if (overflow)  // check last overflow
	{
		newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
		newNode->next = NULL;
		newNode->val = 1;
		p->next = newNode;
	}

	return sum;
}