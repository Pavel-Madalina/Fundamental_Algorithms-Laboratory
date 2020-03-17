// lab1.cpp
// Nume: Pavel Madalina
// Grupa: 30224

// Din punctul de vedere al implementarii, niciun algoritm nu mi-a creat dificultati.

// In cazul mediu statistic, bubble sort este cel mai ineficient.
// Din punctul de vedere al asignarilor, selection face cele mai putine asignari, in timp ce bubble necesita un numar extrem de mare de asignari.
// Insa din punctul de vedere al comparatiilor, selection si bubble au acelasi numar de comparatii, iar numarul cel mai mic de comparatii se gaseste la insertion.

// In cazul defavorabil, selection este cel mai eficient algoritm, iar bubble cel mai ineficient din cauza numarului extrem de mare de operatii.
// In acest caz, algoritmii fac aproximativ acelasi numar de comparatii, deci numarul asignarilor este cel care face diferenta.

// In cazul favorabil, insertion este cel mai eficient algoritm.
// Din punctul de vedere al asignarilor, cel mai eficient este bubble deoarece nu face nicio asignare daca vectorul este deja sortat.
// Din punctul de vedere al comparatiilor, insertion face cele mai putine comparatii, iar selection si bubble fac acelasi numar de comparatii.

#include <stdio.h>
#include <string.h>
#include "Profiler.h"

Profiler p("lab1");

void bubble(int *v, int n)
{
	Operation op1 = p.createOperation("bubble_comp", n);
	Operation op2 = p.createOperation("bubble_asign", n);
	int aux;
	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			op1.count();
			if (v[i] > v[j])
			{
				op2.count(3);
				aux = v[i];
				v[i] = v[j];
				v[j] = aux;
			}
		}
	}
}

void insertion(int *v, int n)
{
	Operation op3 = p.createOperation("insertion_comp", n);
	Operation op4 = p.createOperation("insertion_asign", n);
	for (int j = 1; j < n - 1; j++)
	{
		op4.count();
		int key = v[j];
		int i = j - 1;
		op3.count();
		while (i >= 0 && v[i] > key)
		{
			op4.count();
			v[i + 1] = v[i];
			i = i - 1;
			op3.count();
		}
		op4.count();
		v[i + 1] = key;
	}
}

void selection(int *v, int n)
{
	Operation op5 = p.createOperation("selection_comp", n);
	Operation op6 = p.createOperation("selection_asign", n);
	for (int i = 0; i < n - 1; i++)
	{
		int min = i;
		for (int j = i + 1; j < n; j++)
		{
			op5.count();
			if (v[j] < v[min])
			{
				min = j;
			}
		}
		op6.count(3);
		int aux = v[i];
		v[i] = v[min];
		v[min] = aux;
	}
}

void afisare(int v[], int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("%d ", v[i]);
	}
	printf("\n");
}

void demo()
{
	int v[] = { 7, 5, 1, 2, 6, 4, 9 };
	int n = sizeof(v) / sizeof(v[0]);
	int u[100];
	memcpy(u, v, sizeof(v));
	printf("Vectorul nesortat este:");
	afisare(u, n);  
	bubble(u, n);
	printf("Bubble Sort:");
	afisare(u, n);
	memcpy(u, v, sizeof(v));
	insertion(u, n);
	printf("Insertion Sort:");
	afisare(u, n);
	selection(v,n);
	printf("Selection Sort:");
	afisare(v,n);
}

void perform_avg()
{
	int v[10000], u[10000];
	           
	for (int n = 100; n <= 1000; n += 100)
	{
		FillRandomArray(v, n); 
		memcpy(u, v, n*sizeof(v[0]));
		bubble(u, n);
		memcpy(u, v, n * sizeof(v[0]));
		insertion(u, n);
		selection(v, n);
	}
	p.addSeries("bubble", "bubble_comp", "bubble_asign"); 
	p.addSeries("insertion", "insertion_comp", "insertion_asign");
	p.addSeries("selection", "selection_comp", "selection_asign");
	p.createGroup("comparatii_avg", "bubble_comp", "insertion_comp", "selection_comp");
	p.createGroup("asignari_avg", "bubble_asign", "insertion_asign", "selection_asign");
	p.createGroup("algoritmi_sortare_avg", "bubble", "insertion", "selection"); 
	p.showReport(); 
}

void perform_worst()
{
	int v[10000], u[10000];
					
	for (int n = 100; n <= 1000; n += 100)
	{
		FillRandomArray(v, n, 10, 50000, false, 2); 
		memcpy(u, v, n*sizeof(v[0]));
		bubble(u, n);
		memcpy(u, v, n * sizeof(v[0]));
		insertion(u, n);
		selection(v, n);
	}
	p.addSeries("bubble", "bubble_comp", "bubble_asign"); 
	p.addSeries("insertion", "insertion_comp", "insertion_asign");
	p.addSeries("selection", "selection_comp", "selection_asign");
	p.createGroup("comparatii_worst", "bubble_comp", "insertion_comp", "selection_comp");
	p.createGroup("asignari_worst", "bubble_asign", "insertion_asign", "selection_asign");
	p.createGroup("algoritmi_sortare_worst", "bubble", "insertion", "selection"); 
	p.showReport(); 
}

void perform_best()
{
	int v[10000], u[10000];
					
	for (int n = 100; n <= 1000; n += 100)
	{
		FillRandomArray(v, n, 10, 50000, false, 1); 
		memcpy(u, v, n*sizeof(v[0]));
		bubble(u, n);
		memcpy(u, v, n * sizeof(v[0]));
		insertion(u, n);
		selection(v, n);
	}
	p.addSeries("bubble", "bubble_comp", "bubble_asign");
    p.addSeries("insertion", "insertion_comp", "insertion_asign");
	p.addSeries("selection", "selection_comp", "selection_asign");
	p.createGroup("comparatii_best", "bubble_comp", "insertion_comp", "selection_comp");
	p.createGroup("asignari_best", "bubble_asign", "insertion_asign", "selection_asign");
	p.createGroup("algoritmi_sortare_best", "bubble", "insertion", "selection"); 
	p.showReport(); 
}

int main()
{
	demo();
	//perform_avg();
	//perform_worst();
	//perform_best();
	return 0;
}