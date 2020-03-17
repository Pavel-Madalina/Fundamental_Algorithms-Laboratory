//Nume: Pavel Madalina
//Grupa: 30224

#include <stdio.h>
#include <stdlib.h>

typedef struct _NOD2
{
	int key;
	int nrChildren;
	struct _NOD2 **children;
}NOD2;

typedef struct _NOD3
{
	int key;
	struct _NOD3 *child, *brother;
}NOD3;

NOD2* buildTree_T1(int *p, int n)
{
	NOD2 *root = NULL;
	NOD2 *vector = (NOD2 *)calloc(n, sizeof(NOD2));
	for (int i = 1; i <= n; i++)
	{
		vector[i].children = NULL;
	}
	int *c = (int *)malloc(n * sizeof(int));
	for (int i = 1; i <= n; i++)
	{
		c[i] = 0;
	}
	for (int i = 1; i <= n; i++)
	{
		vector[i].key = i;
		if (p[i-1] != -1)
		{
			c[p[i-1]]++;
		}
	}
	for (int i = 1; i <= n; i++)
	{
		vector[i].nrChildren = c[i];
		vector[i].children = (NOD2 **)malloc(vector[i].nrChildren * sizeof(NOD2 *)); 
	}
	for (int i = 1; i <= n; i++)
	{
		if (p[i-1] == -1)
		{
			root = &vector[i];
		}
		else 
		{
			int j = vector[p[i-1]].nrChildren - c[p[i-1]];
			vector[p[i-1]].children[j] = &vector[i];
			c[p[i-1]]--;
		}
	}
	return root;
}

NOD3 *buildTree_T2(NOD2 *root2,NOD2 *root,NOD2 *father,int i)
{
	NOD3 *node = (NOD3 *)malloc(sizeof(NOD3));
	node->key = root2->key;
	if (root2->nrChildren != 0)
	{
		node->child = buildTree_T2(root2->children[0], root, root2,0);
	}
	else
	{
		node->child = NULL;
	}
	if (node->key == root->key)
	{
		node->brother = NULL;
	}
	else if(i+1 < father->nrChildren)
	{
		node->brother = buildTree_T2(father->children[i+1], root,father,i+1);
	}
	else
	{
		node->brother = NULL;
	}
	return node;
}

void prettyPrint(NOD3 *root,int level)
{
	if (root != NULL)
	{
		for (int i = 0; i < level; i++)
		{
			printf("    ");
		}
		printf("%d\n", root->key);
		prettyPrint(root->child, level + 1);
		prettyPrint(root->brother, level);
	}
}

int main()
{
	int p[] = { 2, 7, 5, 2, 7, 7, -1, 5, 2 };
	int n = sizeof(p) / sizeof(p[0]);
	NOD2 *root2 = buildTree_T1(p, n);
	NOD3 *root3 = buildTree_T2(root2,root2,NULL,0);
	prettyPrint(root3, 0);
	return 0;
}