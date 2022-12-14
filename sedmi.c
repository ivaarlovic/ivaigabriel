#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_DULJINA 256 

typedef struct CvorStabla* Stablo;

struct CvorStabla {
	char ime[MAX_DULJINA];
	Stablo PrvoDijete;
	Stablo NextBrat;
};

typedef struct Stog* pozicija;

struct Stog {
	pozicija next;
	Stablo direktorij;

};


Stablo Unesi(Stablo, Stablo);
Stablo novi(char*);
Stablo Trazi(Stablo, char*);
pozicija promijeni(Stablo);
int Push(pozicija, pozicija);
Stablo izlaz(pozicija, Stablo);
int ispis(Stablo);
int oslobodiD(Stablo);
int oslobodiS(pozicija);


int main()
{
	struct CvorStabla root = {.NextBrat = NULL, .PrvoDijete = NULL};
	strcpy(root.ime, "C:");

	struct Stog head={.direktorij=NULL, .next=NULL};
	pozicija p = &head;

	Stablo sadasnji = &root;
	int x = 0;
	char ime[MAX_DULJINA] = {0};
	Stablo noviDir = NULL;

	while (1)
	{
		
		printf("\n\tIzbornik:\n");
		printf("1-praviti novi direktorij(md)\n");
		printf("\n2-promjena direktorija(cd dir)\n");
		printf("\n3-vratiti na prethodni direktorij(cd..)\n");
		printf("\n4-ispis pod-direktorija(dir)\n");
		printf("\n5-izlaz(exit)\n");
		scanf(" %d", &x);

		if (x == 1)
		{
			printf("Unesi ime direktorija:\n");
			scanf(" %s", ime);

			noviDir = novi(ime);
			sadasnji->PrvoDijete = Unesi(sadasnji->PrvoDijete, noviDir);
			
		}
		else if (x == 2)
		{
			printf("\nIzaberi direktorij u koji zelis uci:\n");
			scanf(" %s", ime);

			Stablo temp = Trazi(sadasnji, ime);
			if (temp == NULL)
			{
				return NULL;
			}
			else
			{
				pozicija noviEl = promijeni(sadasnji);
				Push(p, noviEl);
			}
			sadasnji = temp;

		}
		else if (x == 3)
		{
			sadasnji = izlaz(p, sadasnji);
		}

		else if (x == 4)
		{
			ispis(sadasnji);
		}
		else if (x == 5)
		{
			oslobodiD(&root);
			oslobodiS(&head);

		}
		else
		{
			printf("Kriv unos broja!Pokusaj ponovno!\n");
		}
	}

	return 0;


}

Stablo novi(char* ime)
{
	Stablo novi;
	novi = (Stablo)malloc(sizeof(struct CvorStabla));

	if (novi == NULL)
	{
		printf("Greska s alokacijom memorije.\n");
		return NULL;
	}

	if (novi != NULL)
	{
		strcpy(novi->ime, ime);
		novi->NextBrat = NULL;
		novi->PrvoDijete = NULL;
	}

	return novi;
}

Stablo Unesi(Stablo sad, Stablo novi)
{
	if (sad == NULL)
	{
		return novi;
	}

	if (strcmp(sad->ime, novi->ime) < 0)
	{
		sad->NextBrat = Unesi(sad->NextBrat, novi);

	}
	else if (strcmp(sad->ime, novi->ime) > 0)
	{
		novi->NextBrat = sad;
		return novi;
	}

	return sad;
}

Stablo Trazi(Stablo sadasnji, char* ime)
{
	Stablo dijete = sadasnji->PrvoDijete;
	if (sadasnji == NULL)
	{
		printf("\nDirektorij je prazan!\n");
		return NULL;
	}

	while (dijete != NULL && strcmp(dijete->ime, ime) != 0)
	{
		dijete = dijete->NextBrat;
	}

	return dijete;
}

pozicija promijeni(Stablo sadasnji)
{
	pozicija novi = NULL;
	novi = (pozicija)malloc(sizeof(struct Stog));

	if (novi == NULL)
	{
		printf("Greska pri alokaciji memorije.\n");
		return NULL;
	}

	novi->direktorij = sadasnji;
	novi->next = NULL;

	return novi;
}

int Push(pozicija p, pozicija novi)
{
	novi->next = p->next;
	p->next = novi;

	return EXIT_SUCCESS;
}

Stablo izlaz(pozicija p, Stablo sadasnji)
{
	pozicija prvi = NULL;
	prvi = p->next;

	if (prvi == NULL)
	{
		return sadasnji;
	}

	Stablo pom = NULL;
	pom = prvi->direktorij;
	p->next = prvi->next;
	free(prvi);
	return pom;
	
	
}

int ispis(Stablo sadasnji)
{
	int i = 0;
	Stablo p;
	p = sadasnji->PrvoDijete;
	while (p != NULL)
	{
		printf("%d.:", i + 1);
		printf("%s\t\n", p->ime);
		p = p->NextBrat;
		i++;
	}


	return 0;
}

int oslobodiD(Stablo sadasnji)
{
	Stablo tempBrat= NULL;
	Stablo tempDijete = NULL;

	tempDijete = sadasnji->PrvoDijete;
	while (tempDijete->NextBrat != NULL)
	{
		tempBrat = tempDijete->NextBrat;
		tempDijete->NextBrat = tempBrat->NextBrat;
		free(tempBrat);
	}
	sadasnji->PrvoDijete = tempDijete->PrvoDijete;
	free(tempDijete);

	while (sadasnji->NextBrat != NULL)
	{
		
		sadasnji->NextBrat = sadasnji->NextBrat->NextBrat;
		free(sadasnji);
	}
	free(sadasnji);
	return 0;

}

int oslobodiS(pozicija p)
{
	pozicija temp=NULL;
	while (p!=NULL)
	{
		temp = p->next;
		p->next = temp->next;
		free(temp);
	}

	return 0;
}