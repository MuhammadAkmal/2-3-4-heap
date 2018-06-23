#include "stdafx.h"
#include <iostream>
#include<stdlib.h>
using namespace std;

struct node
{
	int		key;
	int		degree;
	node*	parent;
	node*	child1;
	node*	child2;
	node*	child3;
	node*	child4;
	node(int key_ = 0, int degree_ = 0, node* parent_ = 0, node* child1_ = 0, node* child2_ = 0, node* child3_ = 0, node* child4_ = 0) :
		key(key_), degree(degree_), parent(parent_), child1(child1_), child2(child2_), child3(child3_), child4(child4_) {}
};

struct node1
{
	int height;
	node* root;
	node1(int height_ = -1, node * root_ = 0) :height(height_), root(root_) {}
};

node1	makeHeap()
{
	node1 head;
	return head;
}
node* 	minimum(node1& head)
{
	node* p = head.root;
	for (int i = 0; i < head.height; ++i)
	{
		if (p->child1->key == p->key)
			p = p->child1;
		else if (p->child2->key == p->key)
			p = p->child2;
		else if (p->child3->key == p->key)
			p = p->child3;
		else if (p->child4->key == p->key)
			p = p->child4;
	}
	return p;
}
int max(int a, int b) {
	if (a > b) {
		return a;
	}
	else if (a == b) {
		return a;
	}
	else {
		return b;
	}
}
int min(int a, int b) {
	if (a > b) {
		return b;
	}
	else if (a == b) {
		return a;
	}
	else {
		return a;
	}
}

void   	decreaseKey(node1& head, node* x, int k)
{
	if (k > x->key)
		cout << "error";
	else
	{
		x->key = k;
		node* p = x;
		while (p->parent&&p->parent->key > k)
		{
			p->parent->key = k;
			p = p->parent;
		}
	}
}

node* 	extractMin(node1& head)//extracts a leaf with the smallest key; returns the node with the smallest key
{
	node* mini = minimum(head);
	if (mini == head.root || !mini->parent)
	{
		head.root = NULL;
		head.height--;
		return NULL;
	}
	if (mini->parent == head.root && head.root->degree == 2)
	{
		head.root = new node(max(head.root->child1->key, head.root->child2->key), 0);
		head.height--;
		return head.root;
	}											//simplest cases
	node* p = mini;
	node* q = p;
	if (mini->parent->degree > 2)				//not so complicated case: we can delete it and then aligne
	{
		if (mini == mini->parent->child1)
			swap(mini->parent->child1, mini->parent->child2);
		if (mini == mini->parent->child2)
			swap(mini->parent->child2, mini->parent->child3);
		if (mini == mini->parent->child3 && mini->parent->child4)
			swap(mini->parent->child3, mini->parent->child4);
		mini->parent->degree--;
		if (mini->parent->child4)
			mini->parent->child4 = NULL;
		else
			mini->parent->child3 = NULL;
	}
	else										//its parent has only 2 childs	
	{
		node* p = mini->parent;
		mini = NULL;
		if (p->child1 == NULL)
			swap(p->child1, p->child2);
		p->key = p->child1->key;
		p->degree--;
		node* q;
		while (1)								//we can get til the root
		{
			if (!p->parent)						//it got to the root
			{
				q = head.root = p->child1;
				head.height--;
				break;
			}
			else
			{
				if (p->parent->degree>2)			//we can fix it with 1 step
				{
					if (p->parent->child1->degree != 1)		// we can get him a sibling form here
					{
						if (p->parent->child1->degree == 2) // we move the single leaf
						{
							p->parent->child1->child3 = p->child1;
							p->parent->child1->degree++;
							p->parent->degree--;
							p->parent->child1->key = min(p->parent->child1->key, p->parent->child1->child3->key);
							if (p == p->parent->child1)							// we gotta align
								swap(p->parent->child1, p->parent->child2);
							if (p == p->parent->child2)
								swap(p->parent->child2, p->parent->child3);
							if (p == p->parent->child3 && p->parent->child4)
								swap(p->parent->child3, p->parent->child4);
							if (p->parent->child4)
								p->parent->child4 = NULL;
							else
								p->parent->child3 = NULL;
							p->parent->key = min(p->parent->child1->key, p->parent->child2->key);		//refreshing the keys
							if (p->parent->child3)
								p->parent->key = min(p->parent->child3->key, p->parent->key);
						}
						else										// we get a sibling for him from his uncle
						{
							if (p->parent->child1->child4)
							{
								p->child2 = p->parent->child1->child4;
								p->parent->child1->child4 = NULL;
								p->parent->child1->degree--;
								p->degree++;
							}
							else
							{
								p->child2 = p->parent->child1->child3;
								p->parent->child1->child3 = NULL;
								p->parent->child1->degree--;
								p->degree++;
							}
							p->parent->child1->key = min(p->parent->child1->child1->key, p->parent->child1->child2->key);			//key refreshing
							if (p->parent->child1->child3)
								p->parent->child1->key = min(p->parent->child1->key, p->parent->child1->child3->key);
							if (p->parent->child1->child4)
								p->parent->child1->key = min(p->parent->child1->key, p->parent->child1->child4->key);
							p->key = min(p->child1->key, p->child2->key);
							p->parent->key = min(p->parent->child1->key, p->parent->child2->key);
							if (p->parent->child3)
								p->parent->key = min(p->parent->child3->key, p->parent->key);
							if (p->parent->child4)
								p->parent->key = min(p->parent->child4->key, p->parent->key);
						}
					}
					else if (p->parent->child2->degree != 1)						// we can get him a sibling form here
					{
						if (p->parent->child2->degree == 2)						// we move teh single leaf
						{
							p->parent->child2->child3 = p->child1;
							p->parent->child2->degree++;
							p->parent->degree--;
							p->parent->child2->key = min(p->parent->child2->key, p->parent->child2->child3->key);
							if (p == p->parent->child1)								//aligning
								swap(p->parent->child2, p->parent->child2);
							if (p == p->parent->child2)
								swap(p->parent->child2, p->parent->child3);
							if (p == p->parent->child3 && p->parent->child4)
								swap(p->parent->child3, p->parent->child4);
							if (p->parent->child4)
								p->parent->child4 = NULL;
							else
								p->parent->child3 = NULL;
							p->parent->key = min(p->parent->child1->key, p->parent->child2->key);	//refreshing the keys
							if (p->parent->child3)
								p->parent->key = min(p->parent->child3->key, p->parent->key);
						}
						else											//we get him a siblin gfrom his uncle
						{
							if (p->parent->child2->child4)
							{
								p->child2 = p->parent->child2->child4;
								p->parent->child2->child4 = NULL;
								p->parent->child2->degree--;
								p->degree++;
							}
							else
							{
								p->child2 = p->parent->child2->child3;
								p->parent->child2->child3 = NULL;
								p->parent->child2->degree--;
								p->degree++;
							}
							p->parent->child2->key = min(p->parent->child2->child1->key, p->parent->child2->child2->key);
							if (p->parent->child1->child3)
								p->parent->child2->key = min(p->parent->child2->key, p->parent->child2->child3->key);
							if (p->parent->child2->child4)
								p->parent->child2->key = min(p->parent->child2->key, p->parent->child2->child4->key);
							p->key = min(p->child1->key, p->child2->key);
							p->parent->key = min(p->parent->child1->key, p->parent->child2->key);
							if (p->parent->child3)
								p->parent->key = min(p->parent->child3->key, p->parent->key);
							if (p->parent->child4)
								p->parent->key = min(p->parent->child4->key, p->parent->key);				//keys resfreshed
						}
					}
					q = p;
					break;
				}
				else
				{
					if (p->parent->child1->degree != 1)
					{
						if (p->parent->child1->degree>2)				//getting him a sibling from his uncle
						{
							if (p->parent->child1->child4)
							{
								p->child2 = p->parent->child1->child4;
								p->parent->child1->child4 = NULL;
							}
							else
							{
								p->child2 = p->parent->child1->child3;
								p->parent->child1->child3 = NULL;
							}
							p->parent->child1->degree--;
							p->parent->key = min(p->parent->child1->key, p->parent->child2->key);	//surely refreshing the keys
							if (p->parent->child3)
								p->parent->key = min(p->parent->key, p->parent->child3->key);
							p->degree++;
							q = p;
							break;
						}
						else															// the megaworst case
						{
							p->parent->child1->child3 = p->child1;
							p->parent->child1->degree++;
							p->parent->degree--;
							p->child1 = NULL;
							p = p->parent;
							p->child1->key = min(p->child1->key, p->child1->child3->key);
							p->key = p->child1->key;
							p->child2 = NULL;
						}
					}
					else if (p->parent->child2->degree != 1)
					{
						if (p->parent->child2->degree>2)			//getting him a sibling from his uncle
						{
							if (p->parent->child2->child4)
							{
								p->child2 = p->parent->child2->child4;
								p->parent->child2->child4 = NULL;
							}
							else
							{
								p->child2 = p->parent->child2->child3;
								p->parent->child2->child3 = NULL;
							}
							p->parent->child2->degree--;
							p->parent->key = min(p->parent->child1->key, p->parent->child2->key);	//surely refreshing the keys
							if (p->parent->child3)
								p->parent->key = min(p->parent->key, p->parent->child3->key);
							p->degree++;
						}
						else									// the meagworst case
						{
							p->parent->child2->child3 = p->child1;
							p->parent->child2->degree++;
							swap(p->parent->child2, p);
							p->parent->degree--;
							p->child1 = NULL;
							p = p->parent;
							p->child2 = NULL;
						}
					}
				}
			}
		}
	}
	while (q->parent) // refreshing the minimum of the whole heap 
	{
		q = q->parent;
		q->key = min(q->child1->key, q->child2->key);
		if (q->child3)
			q->key = min(q->key, q->child3->key);
		if (q->child4)
			q->key = min(q->key, q->child4->key);
	}
	return minimum(head);
}
void   	remove(node1& head, node*& x) //deletes a given leaf x
{
	decreaseKey(head, x, -1);
	extractMin(head);
}
node1 	union234(node1& heap1, node1& heap2)
{
	if (heap1.height == heap2.height)
	{
		node* root = new node(min(heap1.root->key, heap2.root->key), 2, NULL, heap1.root, heap2.root);
		node1 head(heap1.height + 1, root);
		return head;
	}
	if (heap2.height>heap1.height)
		swap(heap1, heap2);
	node * p = heap1.root;
	if (p->degree == 4)
	{
		node* l = new node(min(p->child1->key, p->child2->key), 2, NULL, p->child1, p->child2);
		node* r = new node(min(p->child3->key, p->child4->key), 2, NULL, p->child3, p->child4);
		node* pr = new node(min(l->key, r->key), 2, NULL, l, r);
		l->parent = pr;
		r->parent = pr;
		heap1.root = pr;
		heap1.height++;
	}
	p = heap1.root;
	for (int i = 0; i<heap1.height - heap2.height - 1; ++i)
	{
		if (p->degree < 4)
		{
			if (p->child3&&p->child3->degree < 4)
				p = p->child3;
			else if (p->child2&&p->child2->degree < 4)
				p = p->child2;
			else
				p = p->child1;
		}
		else
		{
			if (!p->parent->child3)
			{
				p->parent->child3 = new node(min(p->child3->key, p->child4->key), 2, p->child3, p->child4);
				--i;
			}
			else
			{
				p->parent->child4 = new node(min(p->child3->key, p->child4->key), 2, p->child3, p->child4);
				--i;
			}
			p->parent->degree++;
			p->degree -= 2;
		}
	}
	if (p->degree<4)
	{
		if (!p->child3)
		{
			p->child3 = heap2.root;
			p->child3->parent = p;
			p->child3->degree = heap2.root->degree;
			p->child3->child1 = heap2.root->child1;
			p->child3->child2 = heap2.root->child2;
			p->child3->child3 = heap2.root->child3;
			p->child3->child4 = heap2.root->child4;
			p->degree++;
		}
		else
		{
			p->child4 = heap2.root;
			p->child4->parent = p;
			p->child4->degree = heap2.root->degree;
			p->child4->child1 = heap2.root->child1;
			p->child4->child2 = heap2.root->child2;
			p->child4->child3 = heap2.root->child3;
			p->child4->child4 = heap2.root->child4;
			p->degree++;
		}
	}
	else
	{
		if (!p->parent->child3)
			p->parent->child3 = new node(min(p->child3->key, p->child4->key), 2, p->child3, p->child4);
		else
			p->parent->child4 = new node(min(p->child3->key, p->child4->key), 2, p->child3, p->child4);
		p->parent->degree++;
		p->degree -= 2;
		p->parent->child3->child3 = heap2.root;
		p->parent->child3->child3->degree++;
	}
	p = heap2.root;
	while (p->parent)
	{
		if (p->parent->key>p->key)
			p->parent->key = p->key;
		else
			break;
	}
	return heap1;
}

void  	insert(node1& head1, node* x)
{
	if (head1.height == -1)
	{
		head1.root = x;
		head1.height = 0;
	}
	else
	{
		node1 head2(0, x);
		head1 = union234(head1, head2);
	}
}
void print(node* root)
{
	if (root)
	{
		cout << root->key << ' ';
		if (root->child1)
		{
			cout << " c1 ";
			print(root->child1);
		}
		if (root->child2)
		{
			cout << " c2 ";
			print(root->child2);
		}
		if (root->child3)
		{
			cout << " c3 ";
			print(root->child3);
		}
		if (root->child4)
		{
			cout << " c4 ";
			print(root->child4);
		}
		cout << endl;
	}
}

/*
Node1	makeHeap();
Node* 	minimum(Node1& head);
void   	decreaseKey(Node1& head, Node* x, int k);
void  	insert(Node1& head1, Node* x);
void   	delete(Node1& head, Node* x);
Node* 	extractMin(Node1& head);
Node1 	union(Node1& heap1, Node1& heap2);
*/

int main()
{
	node1 head = makeHeap();
	node* ex1 = new node(1);
	insert(head, ex1);
	for (int i = 0; i<10; i++)
	{
		node* ex2 = new node(i + 2);
		insert(head, ex2);
	}
	//remove(head,ex2);
	print(head.root);
	return 0;
}