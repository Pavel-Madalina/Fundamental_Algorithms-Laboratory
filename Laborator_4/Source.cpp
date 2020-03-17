//lab_4
//Nume : Pavel Madalina
//Grupa : 30224

#include <stdio.h>
#include "Profiler.h"

Profiler p("lab4");

typedef struct node
{
	int key;
	int index;
	struct node *next;
} Node;

void inserareLista(Node **first, int key, int index)
{
	Node *node = (Node *)malloc(sizeof(Node));
	node->key = key;
	node->index = index;
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

void afisareLista(Node *first)
{
	while (first != NULL)
	{
		printf("%d/%d ", first->key, first->index);
		first = first->next;
	}
}

void MinHeapify(Node **v_minime, int i, int k, Operation op)
{
	int min = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;
	op.count();
	if (v_minime[i] == NULL)
	{
		return;
	}
	if (left < k)
	{
		op.count();
		if ((v_minime[left])->key < (v_minime[i])->key)
		{
			min = left;
		}
	}
	if (right < k)
	{
		op.count();
		if ((v_minime[right])->key < (v_minime[min])->key)
		{
			min = right;
		}
	}
	if (min != i)
	{
		op.count(3);
		Node *aux = v_minime[i];
		v_minime[i] = v_minime[min];
		v_minime[min] = aux;
		MinHeapify(v_minime, min, k, op);
	}
}

void BuildAHeap_BU(Node **v_minime, int k, Operation op)
{
	for (int i = k / 2 - 1; i >= 0; i--)
	{
		MinHeapify(v_minime, i, k, op);
	}
}

void interclasareListe(Node **lista, Node **first_rezultat, Node **last_rezultat, int k, int n, Operation op)
{
	Node **v_minime = (Node **)malloc(k * sizeof(Node*));
	for (int i = 0; i < k; i++)
	{
		op.count(3);
		v_minime[i] = lista[i];
		if (lista[i] != NULL)
		{
			lista[i] = (lista[i])->next;
		}
		v_minime[i]->next = NULL;
	}
	BuildAHeap_BU(v_minime, k, op);
	while (k)
	{
		if (v_minime[0] != NULL)
		{
			op.count(2);
			Node *aux = v_minime[0];
			int indice = aux->index;
			if (*first_rezultat == NULL)
			{
				*first_rezultat = *last_rezultat = aux;
			}
			else
			{
				(*last_rezultat)->next = aux;
				*last_rezultat = aux;
			}
			op.count();
			if (lista[indice] != NULL)
			{
				op.count(3);
				v_minime[0] = lista[indice];
				lista[indice] = lista[indice]->next;
				v_minime[0]->next = NULL;
				MinHeapify(v_minime, 0, k, op);
			}
			else
			{
				op.count();
				v_minime[0] = v_minime[k - 1];
				k--;
				MinHeapify(v_minime, 0, k, op);
			}
		}
	}
}

Node* creareListe(int k, int n, int index)
{
	Node* lista = NULL;
	int *v = (int*)malloc((n / k) * sizeof(int));
	FillRandomArray(v, n / k, 10, 50000, false, 2);
	for (int i = 0; i < n / k; i++)
	{
		inserareLista(&lista, v[i], index);
	}
	return lista;
}

void demo()
{
	int k = 4;
	int n = 20;
	Node *first_rezultat = NULL;
	Node *last_rezultat = NULL;
	Node** lista = (Node**)malloc(k * sizeof(Node*));
	for (int i = 0; i < k; i++)
	{
		lista[i] = NULL;
	}
	for (int i = 0; i < k; i++)
	{
		lista[i] = creareListe(k, n, i);
	}
	for (int i = 0; i < k; i++)
	{
		printf("Lista %d :", i);
		afisareLista(lista[i]);
		printf("\n");
	}
	Operation dummy = p.createOperation("Ignore", n);
	interclasareListe(lista, &first_rezultat, &last_rezultat, k, n, dummy);
	afisareLista(first_rezultat);
}

void perform_avg_k1()
{
	for (int n = 100; n <= 10000; n += 100)
	{
		Operation op1 = p.createOperation("Interclasare_k1", n);
		Node *first_rezultat1 = NULL;
		Node *last_rezultat1 = NULL;
		Node** lista = (Node**)malloc(5 * sizeof(Node*));
		for (int i = 0; i < 5; i++)
		{
			lista[i] = NULL;
		}
		for (int i = 0; i < 5; i++)
		{
			lista[i] = creareListe(5, n, i);
		}
		interclasareListe(lista, &first_rezultat1, &last_rezultat1, 5, n, op1);
		while (first_rezultat1 != NULL)
		{
			Node*aux = first_rezultat1;
			first_rezultat1 = first_rezultat1->next;
			free(aux);
		}
	}
}

void perform_avg_k2()
{
	for (int n = 100; n <= 10000; n += 100)
	{
		Operation op1 = p.createOperation("Interclasare_k2", n);
		Node *first_rezultat1 = NULL;
		Node *last_rezultat1 = NULL;
		Node** lista = (Node**)malloc(10 * sizeof(Node*));
		for (int i = 0; i < 10; i++)
		{
			lista[i] = NULL;
		}
		for (int i = 0; i < 10; i++)
		{
			lista[i] = creareListe(10, n, i);
		}
		interclasareListe(lista, &first_rezultat1, &last_rezultat1, 10, n, op1);
		while (first_rezultat1 != NULL)
		{
			Node*aux = first_rezultat1;
			first_rezultat1 = first_rezultat1->next; 
			free(aux);
		}
	}
}

void perform_avg_k3()
{
	for (int n = 100; n <= 10000; n += 100)
	{
		Operation op1 = p.createOperation("Interclasare_k3", n);
		Node *first_rezultat1 = NULL;
		Node *last_rezultat1 = NULL;
		Node** lista = (Node**)malloc(100 * sizeof(Node*));
		for (int i = 0; i < 100; i++)
		{
			lista[i] = NULL;
		}
		for (int i = 0; i < 100; i++)
		{
			lista[i] = creareListe(100, n, i);
		}
		interclasareListe(lista, &first_rezultat1, &last_rezultat1, 100, n, op1);
		while (first_rezultat1 != NULL)
		{
			Node*aux = first_rezultat1;
			first_rezultat1 = first_rezultat1->next; 
			free(aux);
		}
	}
}

void perform_avg()
{
	perform_avg_k1();
	perform_avg_k2();
	perform_avg_k3();
	p.createGroup("Interclasare_k_liste", "Interclasare_k1", "Interclasare_k2", "Interclasare_k3");
	p.showReport();
}

void perform_avg_n()
{
	int n = 10000;
	for (int k = 10; k <= 500; k += 10)
	{
		Operation op1 = p.createOperation("Interclasare_n", k);
		Node *first_rezultat1 = NULL;
		Node *last_rezultat1 = NULL;
		Node** lista = (Node**)malloc(k * sizeof(Node*));
		for (int i = 0; i < k; i++)
		{
			lista[i] = NULL;
		}
		for (int i = 0; i < k; i++)
		{
			lista[i] = creareListe(k, n, i);
		}
		interclasareListe(lista, &first_rezultat1, &last_rezultat1, k, n, op1);
		while (first_rezultat1 != NULL)
		{
			Node*aux = first_rezultat1;
			first_rezultat1 = first_rezultat1->next; 
			free(aux);
		}
		free(lista);
	}
	p.showReport();
}

int main()
{
	//demo();
	//perform_avg();
	perform_avg_n();
	return 0;
}