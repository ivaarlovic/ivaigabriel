
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR -1
#define MAX_LINE 1024 


struct _broj;
typedef struct _broj* pozicija;

typedef struct _broj
{
	int koef;
	int eksp;
	pozicija next;
}broj;

int citanje(pozicija,pozicija, char*);
int ispis(pozicija);
int zbrajanje(pozicija, pozicija, pozicija);
int mnozenje(pozicija, pozicija, pozicija);
int unesiPolinom(char*, pozicija);
pozicija stvori(int, int);
int sortiraniUnos(pozicija, pozicija);
int izbrisi(pozicija, pozicija);
pozicija NadiPrije(pozicija, pozicija);
int UnesiIza(pozicija, pozicija);

int main()
{
	broj Head1 = { .koef = 0, .eksp = 0, .next = NULL };
	pozicija pol1 = &Head1;
	broj Head2 = { .koef = 0, .eksp = 0, .next = NULL };
	pozicija pol2 = &Head2;
	

	char nazivDat[] = "prva.lista.txt";
	citanje(pol1, pol2, nazivDat);

	printf("Prvi polinom:\n");
	ispis(pol1->next);

	printf("Drugi polinom:\n");
	ispis(pol2->next);

	broj Head3 = { .koef = 0, .eksp = 0, .next = NULL };
	pozicija pol3 = &Head3;

	broj Head4 = { .koef = 0, .eksp = 0, .next = NULL };
	pozicija pol4 = &Head4;

	zbrajanje(pol1, pol2, pol3);
	printf("\nZbroj polinoma:\n");
	ispis(pol3->next);


	return 0;

	
}

int citanje(pozicija p1, pozicija p2, char* naziv)
{
	char buffer1[MAX_LINE] = { 0 };
	char buffer2[MAX_LINE] = { 0 };

	FILE* dat = NULL;
	dat = fopen(naziv, "r");

	if (!dat) {
		printf("Datoteka s imenom %s ne postoji\r\n", naziv);
		return ERROR;
	}

	fgets(buffer1, MAX_LINE, dat);
	unesiPolinom(buffer1, p1);

	fgets(buffer2, MAX_LINE, dat);
	unesiPolinom(buffer2, p2);

	fclose(dat);

	return EXIT_SUCCESS;

}

int unesiPolinom(char* buff, pozicija head)
{
	int pomak = 0, koef = 0, eksp = 0, n = 0;
	pozicija temp = NULL;

	while (buff[pomak]!='\0')
	{
		int result = sscanf(buff+pomak, " %d %d %n", &koef, &eksp, &n);
		pomak += n;
		

		temp = stvori(koef, eksp);
		if (!temp)
		{
			return ERROR;
		}

		sortiraniUnos(temp, head);
	}
	return EXIT_SUCCESS;

}

pozicija stvori(int koef, int eksp)
{
	pozicija polinom = NULL;
	polinom = (pozicija)malloc(sizeof(pozicija));

	if (!polinom)
	{
		return ERROR;
	}

	polinom->eksp = eksp;
	polinom->koef = koef;
	polinom->next = NULL;

	return polinom;
}

int sortiraniUnos(pozicija element, pozicija head)
{
	pozicija temp = head->next;
	pozicija prethodni = NULL;

	while ((temp != NULL) && (element->eksp) < (temp->eksp))
	{
		temp = temp->next;
	}

	if ((temp != NULL) && (element->eksp == temp->eksp))
	{
		if (temp->koef + element->koef)
		{
			temp->koef = temp->koef + element->koef;
		}
		else
		{
			izbrisi(temp, head);
			free(element);
		}
	}
	else {
		prethodni = NadiPrije(head, temp);
		UnesiIza(prethodni, element);
	}

	return EXIT_SUCCESS;
}

int izbrisi(pozicija tmp, pozicija head)
{
	pozicija temp = NULL;
	temp = NadiPrije(head, tmp);
	temp->next = tmp->next;
	free(tmp);

	return EXIT_SUCCESS;
}

pozicija NadiPrije(pozicija head, pozicija tmp)
{
	pozicija temp = head;
	while (temp->next != tmp)
	{
		temp = temp->next;
	}

	return temp;
}

int UnesiIza(pozicija prev, pozicija tmp)
{
	tmp->next = prev->next;
	prev->next = tmp;

	return EXIT_SUCCESS;
}

int ispis(pozicija head)
{
	pozicija temp = head;
	printf("\n");
	while (temp != NULL)
	{
		printf("\t%dX^%d\n", temp->koef, temp->eksp);
		temp = temp->next;
	}

	return EXIT_SUCCESS;
}

int zbrajanje(pozicija p1, pozicija p2, pozicija zbroj)
{
	pozicija temp = NULL;
	pozicija ostali = NULL;
	while (p1 && p2)
	{
		if (p1->eksp == p2->eksp)
		{
			temp = stvori(p1->koef + p2->koef, p1->eksp);
			sortiraniUnos(temp, zbroj);
			p1 = p1->next;
			p2 = p2->next;
		}
		else if ((p1->eksp) > (p2->eksp))
		{
			temp = stvori(p1->koef, p1->eksp);
			sortiraniUnos(temp, zbroj);
			p1 = p1->next;
		}
		else if ((p1->eksp) < (p2->eksp))
		{
			temp = stvori(p2->koef, p2->eksp);
			sortiraniUnos(temp, zbroj);
			p2 = p2->next;
		}



	}
	if (p1 && p2 == NULL)
	{
		while (p1->next)
		{
			
			ostali = stvori(p1->koef, p1->eksp);
			sortiraniUnos(ostali, zbroj);
			p1 = p1->next;

		}
	}
	else if (p2 && p1 == NULL)
	{
		while (p2->next)
		{
			ostali = stvori(p2->koef, p2->eksp);
			sortiraniUnos(ostali, zbroj);
			p2 = p2->next;
		}
	}
	return EXIT_SUCCESS;
}
