//Nume : Pavel Madalina
//Grupa : 30224

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Profiler.h"

#define M 10007 //10007 
#define FNV_PRIME 16777619
#define FNV_OFFSET_BASIS 2166136261
Profiler p("lab5");

typedef struct
{
	int id;
	char *name;
}HASH_ELEMENT;

HASH_ELEMENT hashTable[M];

int hashFunction(int id,int pozitie)
{
	return (id + pozitie + pozitie * pozitie) % M;
}

unsigned FNV1A_hash(char *name)
{
	unsigned hash = FNV_OFFSET_BASIS;
	for (int i = 0; i < strlen(name); i++)
	{
		hash = hash ^ name[i];
		hash = hash * FNV_PRIME;
	}
	return hash;
}

void insert(int id,char *name)
{
	int i=0, j;
	do
	{
		if (name != NULL)
		{
			unsigned new_id = FNV1A_hash(name);
			new_id = new_id >> 1;
			j = hashFunction(new_id, i);
		}
		else
		{
			j = hashFunction(id, i);
		}
		if (hashTable[j].id == -1)
		{
			hashTable[j].id = id;
			hashTable[j].name = name;
			return;
		}
		else
		{
			i++;
		}
	} while (i != M - 1);
}

HASH_ELEMENT* search(int id,char *name,int *accesari)
{
	int i = 0,j;
	do
	{
		if (name != NULL)
		{
			unsigned new_id = FNV1A_hash(name);
			new_id = new_id >> 1;
			j = hashFunction(new_id, i);
		}
		else
		{
			j = hashFunction(id, i);
		}
		(*accesari)++;
		if (hashTable[j].id == id)
		{
			return &hashTable[j];
		}
		i++;
	} while (hashTable[j].id != -1 && i != M - 1);
	return NULL;
}

void afisare()
{
	printf("Tabela de dispersie este: \n");
	for (int i = 0; i < M; i++)
	{
		if (hashTable[i].id != -1)
		{
			printf("hashTable[%d] -> id: %d, name: %s\n", i, hashTable[i].id, hashTable[i].name);
		}
		else
		{
			printf("hashTable[%d] -> id: _, name : _\n", i);
		}
	}
}

void demo()
{
	for (int i = 0; i < M; i++)
	{
		hashTable[i].id = -1;
		hashTable[i].name = NULL;
	}
	int v_id[] = { 1,3,5,7,9,12,23,34,45,56,67,78,89,90,19,28};
	char v_name[][8]={"name_1","name_3","name_5","name_7","name_9","name_12","name_23","name_34","name_45","name_56","name_67","name_78","name_89","name_90","name_19","name_28" };
	int n = sizeof(v_id)/sizeof(v_id[0]);
	for (int i = 0; i < n; i++)
	{
		insert(v_id[i], v_name[i]);
	}
	afisare();
	int accesari = 0;
	HASH_ELEMENT *gasit = search(v_id[0], v_name[0],&accesari);
	if (gasit != NULL)
	{
		printf("\nElementul cu id-ul %d si numele <%s> a fost gasit.", gasit->id,gasit->name );
	}
	else
	{
		printf("\nElementul nu a fost gasit.");
	}
}

void perform_avg()
{
	int v[M+10000];
	float factorDeUmplere[5] = { 0.8,0.85,0.9,0.95,0.99 };
	for (int i = 0; i < 5; i++)
	{
		int efort_total_gasite = 0, efort_total_negasite=0;
		int efortul_maxim_gasite = 0, efortul_maxim_negasite = 0;
		for (int i1 = 0; i1 < M; i1++)
		{
			hashTable[i1].id = -1;
			hashTable[i1].name = NULL;
		}
		FillRandomArray(v, factorDeUmplere[i]*M + 1500, 0, 50000, true, 0);
		for (int j = 0; j < factorDeUmplere[i] * M; j++)
		{
			insert(v[j], NULL);
		}
		for (int k1 = 0; k1 < 1500; k1++)
		{
			int accesari_gasite = 0;
			int indice = rand() % (int)(factorDeUmplere[i] * M);
			HASH_ELEMENT *gasit = search(v[indice], NULL, &accesari_gasite);
			efort_total_gasite += accesari_gasite;
			if (efortul_maxim_gasite < accesari_gasite)
			{
				efortul_maxim_gasite = accesari_gasite;
			}
		}
		for (int k2 = factorDeUmplere[i] * M ; k2 < factorDeUmplere[i] * M + 1500; k2++)
		{
			int accesari_negasite = 0;
			HASH_ELEMENT *negasit = search(v[k2], NULL, &accesari_negasite);
			efort_total_negasite += accesari_negasite;
			if (efortul_maxim_negasite < accesari_negasite)
			{
				efortul_maxim_negasite = accesari_negasite;
			}
		}
		printf("\nFactorul de umplere : %f\nEfortul mediu negasite : %f\nEfortul maxim negasite : %d\nEfortul mediu gasite : %f\nEfortul maxim gasite : %d\n",
			factorDeUmplere[i], (double)efort_total_negasite / 1500, efortul_maxim_negasite, (double)efort_total_gasite / 1500, efortul_maxim_gasite);
	}
}

int main()
{
	//demo(); // M -> 17
	srand(time(0));
	perform_avg();
	return 0;
}