// lab_2.cpp
// Nume: Pavel Madalina
// Grupa: 30224

//Bottom-Up
//Complexitate : O(n)
//Algoritmul nu face deplasari pt frunze, in schimb pt nodurile cele mai apropiate de varf face cele mai multe deplasari. 

//Top-Down
//Complexitate : O(n*logn)
//Spre deosebire de Bottom-Up, pt frunze acest algortim face cele mai multe deplasari.

//Heap-urile rezultate in urma apelarii celor 2 algoritmi nu sunt identice.
//In cazul defavorabil, adica atunci cand sirul este ordonat crescator, ambii algoritmi prezinta un grafic liniar, Bottom-Up fiind mai eficient decat Top-Down.
//In cazul mediu statistic, algoritmii tind sa creasca aproape liniar.

//Heap Sort
//Complexitate : O(n*logn)
//Algoritmul este instabil.

#include <stdio.h>
#include <string.h>
#include "Profiler.h"

Profiler p("lab_2");
int heap_size;

void MaxHeapify(int *v, int i,int n)
{
	Operation op1 = p.createOperation("BottomUp", n);
	int largest=i;
	int left = 2 * i + 1;
	int right =2 * i + 2;
	if (left<n) 
	{
		op1.count();
		if (v[left] > v[i])
		{
			largest = left;
		}
	}
	if (right<n)
	{
		op1.count();
		if (v[right] > v[largest])
		{
			largest = right;
		}
	}
	if (largest != i)
	{
		op1.count(3);
		int aux = v[i];
		v[i] = v[largest];
		v[largest] = aux;
		MaxHeapify(v, largest, n);
	}
}

void BuildAHeap_BU(int *v, int n)
{
	for (int i = n / 2 - 1; i >= 0; i--)
	{
		MaxHeapify(v, i, n);
	}
}

int Parent(int i)
{
	return (i - 1) / 2;
}

void HeapPush(int *v,int key,int n)
{
	Operation op2 = p.createOperation("TopDown", n);
	heap_size = heap_size + 1;
	int i = heap_size - 1;
	op2.count();
	v[i] = key;
	op2.count();
	while (i > 0 && v[Parent(i)] < v[i])
	{
		op2.count(3);
		int aux = v[Parent(i)];
		v[Parent(i)] = v[i];
		v[i] = aux;
		i = Parent(i);
		op2.count();
	}
}

void BuildAHeap_TD(int *v, int n)
{
	heap_size = 1;
	for (int i = 1; i < n; i++)
	{
		HeapPush(v, v[i], n);
	}
}

void HeapSort(int *v, int n)
{
	BuildAHeap_BU(v, n);
	for (int i = n - 1; i > 0; i--)
	{
		int aux = v[0];
		v[0] = v[i];
		v[i] = aux;
		n--;
		MaxHeapify(v, 0, n);
	}
}

void afisare(int *v, int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("%d ", v[i]);
	}
	printf("\n");
}

void demo()
{
	int v[] = { 4,1,3,2,16,9,10,14,8,7 };
	int n = sizeof(v) / sizeof(v[0]);
	int u[100];
	memcpy(u, v, sizeof(v));
	BuildAHeap_BU(u, n);
	printf("BU:");
	afisare(u, n);
	memcpy(u, v, sizeof(v));
	HeapSort(u, n);
	printf("Sirul sortat este:");
	afisare(u, n);
	BuildAHeap_TD(v, n);
	printf("TD:");
	afisare(v, n);
}

void perform_avg()
{
	int v[10000], u[10000];

	for (int n = 100; n <= 10000; n += 100)
	{
		FillRandomArray(v, n);
		memcpy(u, v, n * sizeof(v[0]));
		BuildAHeap_BU(u, n);
		BuildAHeap_TD(v, n);
	}
	p.createGroup("Constructii_Heap_avg", "BottomUp", "TopDown");
	p.showReport();
}

void perform_worst()
{
	int v[10000], u[10000];

	for (int n = 100; n <= 10000; n += 100)
	{
		FillRandomArray(v, n, 10,50000,false,1);
		memcpy(u, v, n * sizeof(v[0]));
		BuildAHeap_BU(u, n);
		BuildAHeap_TD(v, n);
	}
	p.createGroup("Constructii_Heap_worst", "BottomUp", "TopDown");
	p.showReport();
}

int main()
{
	//demo();
	//perform_avg();
	perform_worst();
	return 0;
}