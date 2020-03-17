//Nume : Pavel Madalina
//Grupa : 30224

#include <iostream>
#include <stack>
#include "Profiler.h"

Profiler p("lab_10");

std::stack<int> Stack;
std::stack<int> StackT;

typedef struct node
{
	int key;
	struct node *next;
}NODE;

typedef struct _NOD2
{
	int key;
	int nrChildren;
	struct _NOD2 **children;
}NOD2;

typedef struct nodeT
{
	int index;
	int lowlink;
	int onStack;
}NODET;

typedef struct graph
{
	int n;
	NODE **adj;
	int *parent;
	int *color;
	int *d;
	int *f;
}GRAPH;

enum {WHITE,GRAY,BLACK};

void prettyPrint(NOD2 *root, int level)
{
	if (root != NULL)
	{
		for (int i = 0; i < level; i++)
		{
			printf("    ");
		}
		printf("%d\n", root->key);
		if (root->nrChildren != 0)
		{
			for (int i = 0; i < root->nrChildren; i++)
			{
				prettyPrint(root->children[i], level + 1);
			}
		}
	}
}

void buildTree_T1(int *p, int n)
{
	NOD2 **root = (NOD2 **)calloc(n, sizeof(NOD2 *));
	NOD2 *vector = (NOD2 *)calloc(n, sizeof(NOD2));
	for (int i = 0; i < n; i++)
	{
		vector[i].children = NULL;
	}
	int *c = (int *)calloc(n, sizeof(int));
	for (int i = 0; i < n; i++)
	{
		vector[i].key = i;
		if (p[i] != -1)
		{
			c[p[i]]++;
		}
	}
	for (int i = 0; i < n; i++)
	{
		vector[i].nrChildren = c[i];
		vector[i].children = (NOD2 **)malloc(vector[i].nrChildren * sizeof(NOD2 *));
	}
	int k = 0;
	for (int i = 0; i < n; i++)
	{
		if (p[i] == -1)
		{
			root[k] = &vector[i];
			k++;
		}
		else
		{
			int j = vector[p[i]].nrChildren - c[p[i]];
			vector[p[i]].children[j] = &vector[i];
			c[p[i]]--;
		}
	}
	for (int i = 0; i < k; i++)
	{
		printf("Tree #%d:\n", i + 1);
		prettyPrint(root[i], 0);
		printf("\n");
	}
}

void DFSvisit(GRAPH *G, int u, int *time, int *ok, Operation op)
{
 	*time = (*time) + 1;
	op.count(2);
	G->d[u] = *time;
	G->color[u] = GRAY;
	printf("%d ", u);
	op.count();
	NODE *v = G->adj[u];
	while (v != NULL)
	{
		op.count();
		if (G->color[v->key] == WHITE)
		{
			op.count();
			G->parent[v->key] = u;
			DFSvisit(G, v->key, time,ok,op);
		}
		else if(*ok)
		{
			op.count();
			if (G->color[v->key] == GRAY)
			{
				*ok = 0; //are cicluri
			}
		}
		v = v->next;
	}
	op.count(2);
	Stack.push(u);
	G->color[u] = BLACK;
	*time = (*time) + 1;
	G->f[u] = *time;
}

void DFS(GRAPH *G, int *ok, Operation op)
{
	for (int i = 0; i < G->n; i++)
	{
		op.count(2);
		G->color[i] = WHITE;
		G->parent[i] = -1;
	}
	int time = 0;
	printf("\nDFS:\n");
	for (int i = 0; i < G->n; i++)
	{
		op.count();
		if (G->color[i] == WHITE)
		{
			DFSvisit(G, i, &time,ok,op);
			printf("\n");
		}
	}
	printf("\n");
}

void StrongConnect(GRAPH *G, NODET *v, int i, int *index)
{
	v[i].index = *index;
	v[i].lowlink = *index;
	(*index)++;
	StackT.push(i);
	v[i].onStack = 1;
	NODE *w = G->adj[i];
	while (w != NULL)
	{
		if (v[w->key].index == -1)
		{
			StrongConnect(G, v, w->key, index);
			v[i].lowlink = min(v[i].lowlink, v[w->key].lowlink);
		}
		else if(v[w->key].onStack == 1)
		{
			v[i].lowlink = min(v[i].lowlink, v[w->key].index);
		}
		w = w->next;
	}
	if (v[i].lowlink == v[i].index)
	{
		int u;
		do
		{
			u = StackT.top();
			printf("%d ", u);
			StackT.pop();
			v[u].onStack = 0;
		} while (u != i);
		printf("\n");
	}
}

void Tarjan(GRAPH *G)
{
	int index = 0;
	NODET *v = (NODET *)calloc(G->n, sizeof(NODET));
	for (int i = 0; i < G->n; i++)
	{
		v[i].index = -1;
	}
	printf("\nTarjan:\n");
	for (int i = 0; i < G->n; i++)
	{
		if (v[i].index == -1)
		{
			StrongConnect(G, v, i, &index);
		}
	}
}

void topologicalSort(GRAPH *G)
{
	while (!Stack.empty())
	{
		printf("%d - d=%d, f=%d\n", Stack.top(), G->d[Stack.top()], G->f[Stack.top()]);
		Stack.pop();
	}
}

void insertList(NODE **first, int *v, int m)
{
	for (int i = 0; i < m; i++)
	{
		NODE *node = (NODE *)malloc(sizeof(NODE));
		node->key = v[i];
		node->next = NULL;
		if (*first == NULL)
		{
			*first = node;
		}
		else
		{
			node->next = *first;
			*first = node;
		}
	}
}

void insertList(NODE **first, int key)
{
	NODE *node = (NODE *)malloc(sizeof(NODE));
	node->key = key;
	node->next = NULL;
	if (*first == NULL)
	{
		*first = node;
	}
	else
	{
		node->next = *first;
		*first = node;
	}
}

void demo()
{
	GRAPH G;
	G.n = 10;
	G.adj = (NODE **)malloc(G.n * sizeof(NODE *));
	for (int i = 0; i < G.n; i++)
	{
		G.adj[i] = NULL;
	}
	G.parent = (int *)calloc(G.n, sizeof(int));
	G.color = (int *)calloc(G.n, sizeof(int));
	G.d = (int *)calloc(G.n, sizeof(int));
	G.f = (int *)calloc(G.n, sizeof(int));
	int v[10][3] = { {1},{9},{8,5},{4},{},{},{8,7,5},{},{7},{0} };
	int m[10] = { 1,1,2,1,0,0,3,0,1,1 };
	for (int i = 0; i < G.n; i++)
	{
		insertList(&G.adj[i], v[i], m[i]);
	}
	for (int i = 0; i < G.n; i++)
	{
		printf("%d :", i);
		NODE *p = G.adj[i];
		while (p != NULL)
		{
			printf("%d ", p->key);
			p = p->next;
		}
		printf("\n");
	}
	Operation dummy = p.createOperation("Ignore", G.n);
	int ok = 1;
	DFS(&G,&ok,dummy);
	buildTree_T1(G.parent, G.n);
	if (ok == 0)
	{
		printf("Graful are cicluri.Nu se poate face sortarea topologica.\n");
		Tarjan(&G);
	}
	else
	{
		topologicalSort(&G);
	}
}

void demo_ST()
{
	GRAPH G;
	G.n = 10;
	G.adj = (NODE **)malloc(G.n * sizeof(NODE *));
	for (int i = 0; i < G.n; i++)
	{
		G.adj[i] = NULL;
	}
	G.parent = (int *)calloc(G.n, sizeof(int));
	G.color = (int *)calloc(G.n, sizeof(int));
	G.d = (int *)calloc(G.n, sizeof(int));
	G.f = (int *)calloc(G.n, sizeof(int));
	int v[10][3] = { {1},{9},{8,5},{4},{},{},{8,7,5},{},{},{} };
	int m[10] = { 1,1,2,1,0,0,3,0,0,0 };
	for (int i = 0; i < G.n; i++)
	{
		insertList(&G.adj[i], v[i], m[i]);
	}
	for (int i = 0; i < G.n; i++)
	{
		printf("%d :", i);
		NODE *p = G.adj[i];
		while (p != NULL)
		{
			printf("%d ", p->key);
			p = p->next;
		}
		printf("\n");
	}
	Operation dummy = p.createOperation("Ignore", G.n);
	int ok = 1;
	DFS(&G, &ok, dummy);
	buildTree_T1(G.parent, G.n);
	if (ok == 0)
	{
		printf("Graful are cicluri.Nu se poate face sortarea topologica.\n");
	}
	else
	{
		topologicalSort(&G);
	}
}

void perform_E()
{
	srand(time(0));
	GRAPH G;
	int ok = 1;
	for (int E = 1000; E <= 4500; E += 100)
	{
		Operation op = p.createOperation("DFS_E", E);
		G.n = 100;
		G.adj = (NODE **)malloc(G.n * sizeof(NODE *));
		for (int i = 0; i < G.n; i++)
		{
			G.adj[i] = NULL;
		}
		G.parent = (int *)calloc(G.n, sizeof(int));
		G.color = (int *)calloc(G.n, sizeof(int));
		G.d = (int *)calloc(G.n, sizeof(int));
		G.f = (int *)calloc(G.n, sizeof(int));
		for (int i = 0; i < E; i++)
		{
			int key = rand() % G.n;
			int key2 = rand() % G.n;
			insertList(&G.adj[key], key2);
		}
		DFS(&G, &ok, op);
	}
	p.showReport();
}

void perform_V()
{
	srand(time(0));
	int E = 4500;
	int ok = 1;
	GRAPH G;
	for (int V = 100; V <= 200; V += 10)
	{
		Operation op = p.createOperation("DFS_V", V);
		G.n = V;
		G.adj = (NODE **)malloc(G.n * sizeof(NODE *));
		for (int i = 0; i < G.n; i++)
		{
			G.adj[i] = NULL;
		}
		G.parent = (int *)calloc(G.n, sizeof(int));
		G.color = (int *)calloc(G.n, sizeof(int));
		G.d = (int *)calloc(G.n, sizeof(int));
		G.f = (int *)calloc(G.n, sizeof(int));
		for (int i = 0; i < E; i++)
		{
			int key = rand() % V;
			int key2 = rand() % V;
			insertList(&G.adj[key], key2);
		}
		DFS(&G, &ok, op);
	}
	p.showReport();
}

int main()
{
	//demo();
	//demo_ST();
	//perform_E();
	perform_V();
	return 0;
}