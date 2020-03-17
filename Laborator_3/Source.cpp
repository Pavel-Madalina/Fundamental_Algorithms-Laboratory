//lab_3.cpp
//Nume : Pavel Madalina
//Grupa : 30224

//QuickSort
//Complexitate : cazul defavorabil -> O(n^2), cazul mediu statistic si favorabil -> O(nlogn)
//Algoritmul este instabil.

//HeapSort
//Complexitate : O(nlogn)
//Algoritmul este instabil.

//In cazul mediu statistic, QuickSort este mai eficient decat HeapSort. (QuickSort implementat cu pivotul la final)
//In cazul defavorabil, HeapSort este mai eficient, QuickSort avand o complexitate patratica. (QuickSort implementat cu pivotul la final)
//In cazul favorabil, QuickSort este mai eficient decat Heapsort. (QuickSort implementat cu pivotul ales random)

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Profiler.h"

Profiler pr("lab3");


int Partition(int *v, int p, int r,int n)
{
	Operation op1 = pr.createOperation("QuickSort", n);
	op1.count();
	int x = v[r];
	int i = p - 1;
	for (int j = p; j <= r - 1; j++)
	{
		op1.count();
		if (v[j] <= x)
		{
			i++;
			int aux = v[j];
			v[j] = v[i];
			v[i] = aux;
			op1.count(3);
		}
	}
	int temp = v[i + 1];
	v[i + 1] = v[r];
	v[r] = temp;
	op1.count(3);
	return i + 1;
}

void QuickSort(int *v, int p, int r, int n)
{
	if (p < r)
	{
		int q = Partition(v, p, r,n);
		QuickSort(v, p, q - 1,n);
		QuickSort(v, q + 1, r,n);
	}
}

void MaxHeapify(int *v, int i, int n,Operation *op2)
{
	int largest;
	int left = 2 * i + 1;
	int right = 2 * i + 2;
	(*op2).count();
	if (left<n && v[left]>v[i])
	{
		largest = left;
	}
	else
	{
		largest = i;
	}
	(*op2).count();
	if (right<n && v[right]>v[largest])
	{
		largest = right;
	}
	if (largest != i)
	{
		(*op2).count(3);
		int aux = v[i];
		v[i] = v[largest];
		v[largest] = aux;
		MaxHeapify(v, largest, n, op2);
	}
}

void BuildAHeap_BU(int *v, int n, Operation *op2)
{
	for (int i = n / 2 - 1; i >= 0; i--)
	{
		MaxHeapify(v, i, n, op2);
	}
}

void HeapSort(int *v,int n)
{
	Operation op2 = pr.createOperation("HeapSort", n);
	BuildAHeap_BU(v, n, &op2);
	for (int i = n - 1; i > 0; i--)
	{
		op2.count(3);
		int aux = v[0];
		v[0] = v[i];
		v[i] = aux;
		n--;
		MaxHeapify(v, 0, n, &op2);
	}
}

int Partition_forRandom(int *v, int p, int r, int n, Operation *op3)
{
	(*op3).count();
	int x = v[r];
	int i = p - 1;
	for (int j = p; j <= r - 1; j++)
	{
		(*op3).count();
		if (v[j] <= x)
		{
			i++;
			int aux = v[j];
			v[j] = v[i];
			v[i] = aux;
			(*op3).count(3);
		}
	}
	int temp = v[i + 1];
	v[i + 1] = v[r];
	v[r] = temp;
	(*op3).count(3);
	return i + 1;
}

int RandomizedPartition(int *v, int p, int r,int n)
{
	Operation op3 = pr.createOperation("QuickSort_Random", n);
	srand(time(0));
	int i = rand() % (r - p) + p;
	op3.count(3);
	int aux = v[r];
	v[r] = v[i];
	v[i] = aux;
	return Partition_forRandom(v, p, r, n,&op3);
}

int RandomizedSelect(int *v,int p,int r,int i,int n)
{
	if (p == r)
	{
		return v[p];
	}
	int q=RandomizedPartition(v,p,r,n);
	int k = q - p + 1;
	if (i == k)
	{
		return v[q];
	}
	else if(i<k)
	{
		return RandomizedSelect(v, p, q - 1, i, n);
	}
	else
	{
		return RandomizedSelect(v, q + 1, r, i - k, n);
	}
}

void QuickSort_Random(int *v, int p, int r, int n)
{
	if (p < r)
	{
		int q = RandomizedPartition(v, p, r, n);
		QuickSort_Random(v, p, q - 1, n);
		QuickSort_Random(v, q + 1, r, n);
	}
}

void afisare(int *v,int n)
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
	QuickSort(u, 0, n - 1,n);
	printf("QuickSort:");
	afisare(u,n);
	memcpy(u, v, sizeof(v));
	HeapSort(u,n);
	printf("HeapSort:");
	afisare(u,n);
	memcpy(u, v, sizeof(v));
	QuickSort_Random(u, 0, n - 1,n);
	printf("QuickSort_Random:");
	afisare(u,n);
	int element=RandomizedSelect(v, 0, n - 1, 6, n);
	printf("Al 6-lea element este: %d", element);
}

void perform_avg()
{
	int v[10000], u[10000];

	for (int n = 100; n <= 10000; n += 100)
	{
		FillRandomArray(v, n);
		memcpy(u, v, n * sizeof(v[0]));
		QuickSort(u, 0, n - 1,n);
		HeapSort(v,n);
	}
	pr.createGroup("QuickSort_vs_HeapSort_avg", "QuickSort", "HeapSort");
	pr.showReport();
}

void perform_worst()
{
	int v[10000], u[10000];

	for (int n = 100; n <= 1000; n += 100)
	{
		FillRandomArray(v, n, 10, 50000, false, 2);
		memcpy(u, v, n * sizeof(v[0]));
		QuickSort(u, 0, n - 1,n);
		HeapSort(v,n);
	}
	pr.createGroup("QuickSort_vs_HeapSort_worst", "QuickSort", "HeapSort");
	pr.showReport();
}

void perform_best()
{
	int v[10000], u[10000];

	for (int n = 100; n <= 10000; n += 100)
	{
		FillRandomArray(v, n, 10, 50000, false, 1);
		memcpy(u, v, n * sizeof(v[0]));
		QuickSort_Random(u, 0, n - 1, n);
		HeapSort(v, n);
	}
	pr.createGroup("QuickSort_Random_vs_HeapSort_best", "QuickSort_Random", "HeapSort");
	pr.showReport();
}

int main()
{
	//demo();
	//perform_avg();
	//perform_worst();
	perform_best();
	return 0;
}