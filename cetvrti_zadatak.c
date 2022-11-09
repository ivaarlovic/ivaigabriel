#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR -1

typedef struct broj* pozicija;

struct broj
{
	int koef;
	int eksp;
	pozicija next;
};

int citanje(pozicija, char*);
int ispis(pozicija);
int zbrajanje(pozicija, pozicija, pozicija);
int mnozenje(pozicija, pozicija, pozicija);

int main()
{
	struct broj prvi, drugi, zbrajanje, mnozenje;

	prvi.next = NULL;
	drugi.next = NULL;
	zbrajanje.next = NULL;
	mnozenje.next = NULL;

	citanje(&prvi, "prva.lista.txt");
	ispis(&prvi);

	citanje(&drugi, "druga.lista.txt");
	ispis(&drugi);

	return 0;
}

int citanje(pozicija p, char* ime_dat)
{
	pozicija temp, prev;
	pozicija q = NULL;
	FILE* dat;
	dat = fopen(ime_dat, "r");

	if (dat == NULL)
	{
		printf("Greska!Datoteka ne postoji.\n");
	}
	else
	{
		while (feof(dat) == 0)
		{
			q = (pozicija)malloc(sizeof(struct broj));
			fscanf(dat, "%d %d", &q->koef, &q->eksp);

			temp = p->next;
			prev = p;
			while ((temp != NULL) && (temp->eksp > q->eksp))
			{
				prev = temp;
				temp = temp->next;
			}

			prev->next = q;
			if (temp != NULL)
			{
				q->next = temp;
			}

			else
			{
				q->next = NULL;
			}


		}
		
	}
	return 0;
}

	int ispis(pozicija p)
	{
		p = p->next;
		printf("\n");

		while (p->next != NULL)
		{
			if (p->koef > 0)
			{
				printf("\t%d*x^%d\n", p->koef, p->eksp);
				p = p->next;
			}
		}
		return 0;


	}
