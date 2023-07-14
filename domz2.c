#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>

typedef struct elem {
	char ime[11];
	int dd, mm;
	struct elem* sledeci;

}Elem;


char* ucitajIme() {
	char* pom;
	char c;
	int i = 0;
	pom = calloc(20, sizeof(char));

	while (1) {
		c = getchar(); if (c == '\n') break;
		pom[i++] = c;
	}
	pom[i] = '\0';
	pom = realloc(pom, (i + 1) * sizeof(char));
	if (!pom) {
		printf("MEM_GRESKA\n");
		exit(0);
	}


	//oslobodi posle
	return pom;
}

Elem* formirajListu() {
	Elem* prvi = NULL, * poslednji = NULL, * trenutni = NULL;
	FILE* in = fopen("ispiti.txt", "r");
	char pom[13], c;
	//pom = calloc(200, sizeof(char));
	int dd, mm, j = 0;
	if (!in) {
		printf("DAT_GRESKA");
		exit(0);
	}
	//fscanf( in , "%[^,] %d.%d\n", pom, &dd, &mm) == 3
	while (1) {
		j = 0;
		while (1) {
			c = fgetc(in);
			if (c == ' ' || c == EOF) break;
			pom[j++] = c;
		}
		pom[j] = '\0';
		if (c == EOF) break;
		//pom = realloc(pom, j * sizeof(char));
		/*if (!pom) {
			printf("MEM_GRESKA\n");
			exit(0);
		}*/
		fscanf(in, "%d.%d\n", &dd, &mm);
		trenutni = malloc(sizeof(Elem));
		strcpy(trenutni->ime, pom);
		trenutni->dd = dd;
		trenutni->mm = mm;
		trenutni->sledeci = NULL;
		if (poslednji == NULL) {
			prvi = trenutni;

		}
		else {
			poslednji->sledeci = trenutni;

		}
		poslednji = trenutni;

	}
	//free(pom);
	fclose(in);
	return prvi;
}

Elem* sortirajPotrebno(Elem * head, char* ime, int dd1, int mm1, int dd2, int mm2) {
	char pom[11];
	int trmin = 0, ukmin = 999;
	Elem* trenutni = NULL, * prvi = NULL, * poslednji = NULL;
	for (Elem* k = head; k != NULL; k = k->sledeci) {
		//	printf("%s %s\n mm2->%d %d %d<-mm1\n", k->ime, ime, mm2,k->mm ,mm1);
		if (!strcmp(k->ime, ime) && mm2 > k->mm && k->mm > mm1) {
		opet:trenutni = calloc(1, sizeof(Elem));
			strcpy(trenutni->ime, k->ime);
			trenutni->dd = k->dd;
			trenutni->mm = k->mm;
			trenutni->sledeci = NULL;
			if (poslednji == NULL) {
				prvi = trenutni;

			}
			else {
				poslednji->sledeci = trenutni;

			}
			poslednji = trenutni;
			continue;
		}
		if (!strcmp(k->ime, ime) && mm1 == k->mm && k->dd >= dd1) goto opet;
		if (!strcmp(k->ime, ime) && mm2 == k->mm && k->dd <= dd2) goto opet;


	}

	for (Elem* i = prvi; i != NULL; i = i->sledeci) {
		ukmin = i->dd + i->mm * 31;
		for (Elem* j = i; j != NULL; j = j->sledeci) {
			trmin = j->mm * 31 + j->dd;
			if (trmin < ukmin) {
				ukmin = trmin;
				int pom1 = i->dd, pom2 = i->mm;
				i->dd = j->dd;
				i->mm = j->mm;
				j->mm = pom2;
				j->dd = pom1;
			}
		}
	}

	return prvi;
}

void oslobodi(Elem* prvi) {
	Elem* trenutni = prvi;
	while (trenutni != NULL) {
		Elem* stari = trenutni;
		trenutni = trenutni->sledeci;
		free(stari);
	}

}

void ispisi(Elem* prvi) {

	FILE* out = fopen("ispiti_filtrirano.txt", "w");
	for (Elem* i = prvi; i != NULL; i = i->sledeci) {
		fprintf(out, "%02d.%02d\n", i->dd, i->mm);
	}
	fclose(out);
}


int main() {
	char* ime=NULL;
	int dd1, mm1, dd2, mm2;
	ime = ucitajIme();
	scanf("%d.%d", &dd1, &mm1);
	scanf("%d.%d", &dd2, &mm2);

	Elem* prvi, *prviSort;
	prvi = formirajListu();
	prviSort = sortirajPotrebno(prvi, ime, dd1, mm1, dd2, mm2);
	ispisi(prviSort);
	oslobodi(prvi);
	oslobodi(prviSort);
	free(ime);

	return 0;
}
