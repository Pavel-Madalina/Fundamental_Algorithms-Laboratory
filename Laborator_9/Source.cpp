//Nume : Pavel Madalina
//Grupa : 30224

#include <iostream>
#include "Profiler.h"
#define CAPACITY 10000

Profiler p("lab_9");

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

typedef struct queue
{
	int array[CAPACITY];
	int size;
	int head, tail;
}QUEUE;

typedef struct graph
{
	int n;
	NODE **adj;
	int *parent;
	int *color;
	int *d;
}GRAPH;

enum {WHITE,GRAY,BLACK};

void init(QUEUE *Q)
{
	Q->size = 0;
	Q->head = 0;
	Q->tail = 0;
}

void enqueue(QUEUE *Q, int x)
{
	Q->array[Q->tail] = x;
	Q->size++;
	Q->tail++;
	if (Q->tail == CAPACITY)
	{
		Q->tail = 0;
	}
}

int dequeue(QUEUE *Q)
{
	int x = Q->array[Q->head];
	Q->head++;
	Q->size--;
	if (Q->head == CAPACITY)
	{
		Q->head = 0;
	}
	return x;
}

void BFS(GRAPH *G, int s,Operation op)
{
	QUEUE Q;
	op.count(3);
	G->color[s] = GRAY;
	G->d[s] = 0;
	G->parent[s] = -1;
	init(&Q);
	enqueue(&Q, s);
	while (Q.size != 0)
	{
		int u = dequeue(&Q);
		printf("%d ", u);
		NODE *v = G->adj[u];
		while (v != NULL)
		{
			op.count();
			if (G->color[v->key] == WHITE)
			{
				op.count(3);
				G->color[v->key] = GRAY;
				G->d[v->key] = G->d[u] + 1;
				G->parent[v->key] = u;
				enqueue(&Q, v->key);
			}
			v = v->next;
		}
		op.count();
		G->color[u] = BLACK;
	}
}

void BFSvisit(GRAPH *G,Operation op)
{
	for (int i = 0; i < G->n; i++)
	{
		op.count(3);
		G->color[i] = WHITE;
		G->d[i] = -1;
		G->parent[i] = -1;
	}
	printf("\nBFS:\n");
	for (int i = 0; i < G->n; i++)
	{
		op.count();
		if (G->color[i] == WHITE)
		{
			BFS(G, i, op);
			printf("\n");
		}
	}
	printf("\n");
}

void insertList(NODE **first,int *v,int m)
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
	NOD2 **root = (NOD2 **)calloc(n,sizeof(NOD2 *));
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
	int v[10][3] = { {9,1},{9,0},{8,5},{4},{3},{6,2},{8,7,5},{8,6},{7,6,2},{1,0} };
	int m[10] = { 2,2,2,1,1,2,3,2,3,2 };
	for (int i = 0; i < G.n; i++)
	{
		insertList(&G.adj[i], v[i],m[i]);
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
	BFSvisit(&G,dummy);
	buildTree_T1(G.parent, G.n);
}

void perform_E()
{
	srand(time(0));
	int V = 100;
	GRAPH G;
	G.n = V;
	for (int E = 1000; E <= 4500; E += 100)
	{
		Operation op = p.createOperation("BFS_E", E);
		G.adj = (NODE **)malloc(G.n * sizeof(NODE *));
		for (int i = 0; i < G.n; i++)
		{
			G.adj[i] = NULL;
		}
		G.parent = (int *)calloc(G.n, sizeof(int));
		G.color = (int *)calloc(G.n, sizeof(int));
		G.d = (int *)calloc(G.n, sizeof(int));
		for (int i = 0; i < E; i++)
		{
			int key = rand() % V;
			int key2 = rand() % V;
			insertList(&G.adj[key], key2);
			insertList(&G.adj[key2], key);
		}
		BFSvisit(&G, op);
	}
	p.showReport();
}

void perform_V()
{
	srand(time(0));
	int E = 4500;
	GRAPH G;
	for (int V = 100; V <= 200; V += 10)
	{
		Operation op = p.createOperation("BFS_V", V);
		G.n = V;
		G.adj = (NODE **)malloc(G.n * sizeof(NODE *));
		for (int i = 0; i < G.n; i++)
		{
			G.adj[i] = NULL;
		}
		G.parent = (int *)calloc(G.n, sizeof(int));
		G.color = (int *)calloc(G.n, sizeof(int));
		G.d = (int *)calloc(G.n, sizeof(int));
		for (int i = 0; i < E; i++)
		{
			int key = rand() % V;
			int key2 = rand() % V;
			insertList(&G.adj[key], key2);
			insertList(&G.adj[key2], key);
		}
		BFSvisit(&G, op);
	}
	p.showReport();
}

int main()
{
	//demo();
	//perform_E();
	perform_V();
	return 0;
}