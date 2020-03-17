//Nume : Pavel Madalina
//Grupa : 30224

#include <iostream>
#include <stdlib.h>
#include "Profiler.h"

Profiler p("lab_8");

typedef struct edge
{
	int u, v;
	int weight;
}EDGE;

void MakeSet(int *parent, int *rank, int x)
{
	parent[x] = x;
	rank[x] = 0;
}

int FindSet(int *parent, int x,Operation op)
{
	op.count();
	if (x != parent[x])
	{
		parent[x] = FindSet(parent, parent[x],op);
	}
	return parent[x];
}

void Link(int *parent, int *rank, int x, int y,Operation op)
{
	op.count();
	if (rank[x] > rank[y])
	{
		parent[y] = x;
	}
	else
	{
		parent[x] = y;
		op.count();
		if (rank[x] == rank[y])
		{
			rank[y]++;
		}
	}
}

void Union(int *parent, int *rank, int x, int y,Operation op)
{
	Link(parent, rank, FindSet(parent, x,op), FindSet(parent, y,op),op);
}

int Partition(EDGE *muchii, int p, int r, int n)
{
	int x = muchii[r].weight;
	int i = p - 1;
	for (int j = p; j <= r - 1; j++)
	{
		if (muchii[j].weight <= x)
		{
			i++;
			EDGE aux = muchii[j];
			muchii[j] = muchii[i];
			muchii[i] = aux;
		}
	}
	EDGE temp = muchii[i + 1];
	muchii[i + 1] = muchii[r];
	muchii[r] = temp;
	return i + 1;
}

void QuickSort(EDGE *muchii, int p, int r, int n)
{
	if (p < r)
	{
		int q = Partition(muchii, p, r, n);
		QuickSort(muchii, p, q - 1, n);
		QuickSort(muchii, q + 1, r, n);
	}
}

void MST_Kruskal(int *parent, int *rank, EDGE *muchii, int n, int m, Operation op)
{
	EDGE muchii_k[10000];
	for (int i = 0; i < n; i++)
	{
		MakeSet(parent, rank, i);
	}
	QuickSort(muchii, 0, m - 1, m);
	int k = 0;
	for (int i = 0; i < m; i++)
	{
		op.count();
		if (FindSet(parent, muchii[i].u,op) != FindSet(parent, muchii[i].v,op))
		{
			muchii_k[k].u = muchii[i].u;
			muchii_k[k].v = muchii[i].v;
			muchii_k[k].weight = muchii[i].weight;
			Union(parent, rank, muchii[i].u, muchii[i].v,op);
			printf("(%d,%d) - %d\n", muchii_k[k].u, muchii_k[k].v, muchii_k[k].weight);
			k++;
		}
	}
}

void demo()
{
	int n = 10;
	Operation dummy = p.createOperation("Ignore", n);
	int *parent = (int *)calloc(n, sizeof(int));
	int *rank = (int *)calloc(n, sizeof(int));
	for (int i = 0; i < n; i++)
	{
		MakeSet(parent, rank, i);
	}
	Union(parent, rank, 0, 1, dummy);
	Union(parent, rank, 2, 1, dummy);
	Union(parent, rank, 3, 2, dummy);
	Union(parent, rank, 7, 0, dummy);
	Union(parent, rank, 4, 1, dummy);
	Union(parent, rank, 0, 6, dummy);
	if (FindSet(parent, 0, dummy) == FindSet(parent, 1, dummy)) //1
	{
		printf("Nodurile 0 si 1 fac parte din aceeasi multime.\n");
	}
	else
	{
		printf("Nodurile 0 si 1 nu fac parte din aceeasi multime.\n");
	}
	if (FindSet(parent, 1, dummy) == FindSet(parent, 5, dummy)) //2
	{
		printf("Nodurile 1 si 5 fac parte din aceeasi multime.\n");
	}
	else
	{
		printf("Nodurile 1 si 5 nu fac parte din aceeasi multime.\n");
	}
	if (FindSet(parent, 3, dummy) == FindSet(parent, 7, dummy)) //3
	{
		printf("Nodurile 3 si 7 fac parte din aceeasi multime.\n");
	}
	else
	{
		printf("Nodurile 3 si 7 nu fac parte din aceeasi multime.\n");
	}
	if (FindSet(parent, 6, dummy) == FindSet(parent, 7, dummy)) //4 
	{
		printf("Nodurile 6 si 7 fac parte din aceeasi multime.\n");
	}
	else
	{
		printf("Nodurile 6 si 7 nu fac parte din aceeasi multime.\n");
	}
	if (FindSet(parent, 0, dummy) == FindSet(parent, 9, dummy)) //5
	{
		printf("Nodurile 0 si 9 fac parte din aceeasi multime.\n");
	}
	else
	{
		printf("Nodurile 0 si 9 nu fac parte din aceeasi multime.\n");
	}
	free(parent);
	free(rank);
	EDGE m[8];
	m[0].u = 0;
	m[0].v = 1;
	m[0].weight = 4;
	m[1].u = 1;
	m[1].v = 2;
	m[1].weight = 8;
	m[2].u = 1;
	m[2].v = 4;
	m[2].weight = 11;
	m[3].u = 2;
	m[3].v = 4;
	m[3].weight = 2;
	m[4].u = 0;
	m[4].v = 6;
	m[4].weight = 7;
	m[5].u = 2;
	m[5].v = 6;
	m[5].weight = 5;
	m[6].u = 2;
	m[6].v = 3;
	m[6].weight = 6;
	m[7].u = 6;
	m[7].v = 7;
	m[7].weight = 9;
	printf("\nMuchiile initiale:\n");
	for (int i = 0; i < 8; i++)
	{
		printf("(%d,%d) - %d\n", m[i].u, m[i].v, m[i].weight);
	}
	parent = (int *)calloc(n, sizeof(int));
	rank = (int *)calloc(n, sizeof(int));
	printf("\nArborele de acoperire minim:\n");
	MST_Kruskal(parent, rank, m, n, 8, dummy);
	free(parent);
	free(rank);
}

void perform()
{
	srand(time(0));
	for (int n = 100; n <= 10000; n += 100)
	{
		Operation op = p.createOperation("Multimi_disjuncte", n);
		int weight[40000];
		FillRandomArray(weight, 4 * n, 1, 500, false, 0);
		int parent[10000];
		int rank[10000];
		EDGE muchii[40000];
		for (int i = 0; i < n; i++)
		{
			muchii[i].u = i;
			muchii[i].v = n - i;
			muchii[i].weight = weight[i];
		}
		for (int i = n; i < 4 * n; i++)
		{
			muchii[i].u = rand() % n;
			muchii[i].v = rand() % n;
			muchii[i].weight = weight[i];
		}
		MST_Kruskal(parent, rank, muchii, n, 4 * n, op);
	}
	p.showReport();
}

int main()
{
	//demo();
	perform();
	return 0;
}