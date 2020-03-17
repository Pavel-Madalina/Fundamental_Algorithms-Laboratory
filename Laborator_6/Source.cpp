//Nume : Pavel Madalina
//Grupa : 30224

#include <stdio.h>
#include "Profiler.h"

Profiler p("lab_6");

typedef struct node
{
	int key;
	int size;
	struct node *parent;
	struct node *left,*right;
}Node;

Node* BuildTree(int *v,int p,int q)
{
	if (p > q)
	{
		return NULL;
	}
	int mijloc = (p + q) / 2;
	Node *node = (Node *)malloc(sizeof(Node));
	node->key = v[mijloc];
	node->left = BuildTree(v, p, mijloc - 1);
	if (node->left != NULL)
	{
		node->left->parent = node;
	}
	node->right = BuildTree(v, mijloc + 1, q);
	if (node->right != NULL)
	{
		node->right->parent = node;
	}
	if (node->left != NULL && node->right != NULL)
	{
		node->size = node->left->size + node->right->size + 1;
	}
	else if (node->left == NULL && node->right == NULL)
	{
		node->size = 1;
	}
	else
	{
		if (node->left == NULL)
		{
			node->size = node->right->size + 1;
		}
		else
		{
			node->size = node->left->size + 1;
		}
	}
	return node;
}

Node* OS_select(Node *node, int i,Operation op)
{
	op.count();
	int r;
	if (node == NULL)
	{
		return NULL;
	}
	if (node->size < i)
	{
		return NULL;
	}
	if (node->left != NULL)
	{
		r = node->left->size + 1;
	}
	else
	{
		r = 1;
	}
	if (i == r)
	{
		return node;
	}
	else if (i < r)
	{
		return OS_select(node->left, i,op);
	}
	else
	{
		return OS_select(node->right, i - r,op);
	}
}

Node* maxim(Node *root)
{
	if (root->right == NULL)
	{
		return root;
	}
	return maxim(root->right);
}

void restabilireSize(Node *root, Node *p, Operation op)
{
	Node *parent = p->parent;
	if (p != root)
	{
		while (parent != root)
		{
			op.count();
			parent->size--;
			parent = parent->parent;
		}
		root->size--;
	}
}

void OS_delete(Node *root,Node *p,Operation op)
{
	if (p == NULL)
	{
		return;
	}
	Node *temp = NULL;
	if (p->left == NULL)
	{
		if (p == p->parent->right)
		{
			p->parent->right = p->right;
		}
		else
		{
			p->parent->left = p->right;
		}
		restabilireSize(root, p,op);
	}
	else if (p->right == NULL)
	{
		if (p == p->parent->left)
		{
			p->parent->left = p->left;
		}
		else
		{
			p->parent->right = p->left;
		}
		restabilireSize(root, p,op);
	}
	else
	{
		temp = maxim(p->left);
		p->key = temp->key;
		OS_delete(root, temp, op);
	}
	return;
}

void pprint(Node *root,int level)
{
	if (root->left != NULL)
	{
		pprint(root->left, level + 1);
	}
	for (int i = 0; i < level; i++)
	{
		printf("     ");
	}
	printf("%d, %d\n", root->key, root->size);
	if (root->right != NULL)
	{
		pprint(root->right, level + 1);
	}
}

void demo()
{
	int i = 3;
	int v[] = { 2,3,5,6,10,13,14,18,20,22,31 };
	int n = sizeof(v) / sizeof(v[0]);
	Node *root = BuildTree(v, 0, n - 1);
	pprint(root, 0);
	Operation dummy = p.createOperation("Ignore", n);
	Node *gasit = OS_select(root, i,dummy);
	printf("Elementul care contine a %d-a cea mai mica cheie este: %d.\n", i, gasit->key);
	OS_delete(root, gasit, dummy);
	pprint(root, 0);
}

void perform()
{
	int v[10000];
	srand(time(0));
	for (int n = 100; n <= 10000; n += 100)
	{
		Operation op = p.createOperation("OS_delete", n);
		FillRandomArray(v, n, 10, 50000, true, 1);
		Node *root = BuildTree(v, 0, n - 1);
		root->parent = NULL;
		for (int j = 0; j < n; j++)
		{
			int index = rand() % (root->size) +1;
			Node *gasit = OS_select(root, index,op);
			OS_delete(root,gasit , op);
		}
		free(root);
		}
	p.showReport();
}

int main()
{
	//demo();
	perform();
	return 0;
}