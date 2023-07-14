#include<stdio.h>
#include<stdlib.h>
#define br_kol 8

int unos(int* ukBrCl, int* trenutno) {
	scanf_s("%d %d", ukBrCl, trenutno);
	if (*ukBrCl < 1 || *trenutno < 1) return 1;
	else return 0;
}
int alociraj1(int ukBrCl, int*** matrica) {
	int i;
	*matrica = malloc(ukBrCl * sizeof(int*));
	if (*matrica == NULL) { printf("MEM_GRESKA"); return 1; }
	for (i = 0; i < ukBrCl; i++) {
		*(*matrica + i) = malloc(br_kol * sizeof(int));
		if (*(*matrica + i) == NULL) { printf("MEM_GRESKA"); return 1; }
	}
	return 0;
}
int alocirajPomocnu(int trenutno, int*** termini) {
	int i;
	*termini = malloc(br_kol * sizeof(int*));
	if (*termini == NULL) { printf("MEM_GRESKA"); return 1; }
	for (i = 0; i < br_kol; i++) {
		*(*termini + i) = malloc(trenutno * sizeof(int));
		if (*(*termini + i) == NULL) { printf("MEM_GRESKA"); return 1; }
	}
	return 0;
}

void ucitaj(int ukBrCl, int*** matrica) {
	int i, ind=0;
	for (i = 0; i < ukBrCl; i++) {
		for (int j = 0; j < br_kol; j++) {
			scanf_s("%d", *(*matrica+i)+j);
			getchar();
		}
	}
}
int proveri(int ukBrCl, int*** matrica) {
	int i, tek;
	for (i = 0; i < ukBrCl; i++) {
		for (int j = 0; j < br_kol; j++) {
			tek = *(*(*matrica + i) + j);
			if (tek != 0 && tek != 1) return 1;
		}
	}
	return 0;
}

void ispisi(int uk, int*** mat) {
	char c;
	int i;
	for (i = 0; i < uk; i++) {
		for (int j = 0; j < br_kol; j++) {
			c = j != br_kol - 1 ? ' ' : '\n';
			printf("%d%c", *(*(*mat + i) + j), c);
		}
	}
}
void dodela(int uk, int tr, int ***mat, int ***term) {
	int y, i;
	for (int j = 0; j < br_kol; j++) {
		y = 0;
		for (int n = 0; n < uk; n++) {
			if (y < tr) {
				if (*(*(*mat+n)+j) == 1) {
					*(*(*term+j)+y) = n;
					y++;
				}
			}
		}
		if (y != tr) *(*(*term+j)) = -1;
	}
}
void drugiIspis(int tr, int *** term) {
	char s;
	int i;
	for (i = 0; i < br_kol; i++) {
		if (i == 0) printf("Termin 08-09: ");
		else if (i == 1) printf("Termin 09-10: ");
		else printf("Termin %d-%d: ", i + 8, i + 9);

		if (*(*(*term + i)) == -1) { printf("NIJE POPUNJEN\n"); continue; }
		else {
			for (int j = 0; j < tr; j++) {
				s = j == tr - 1 ? '\n' : ' ';
				(printf("%d%c", *(*(*term + i) + j), s));
			}
		}
	}
}
void dealociraj(int uk, int*** mat, int*** term) {
	int i;
	for (i = 0; i < uk; i++)
		free(*(*mat + i));
	free(*mat);

	for (i = 0; i < br_kol; i++)
		free(*(*term + i));
	free(*term);
}

int main(){
	int uk, tr, i;
	int** mat;
	int** term;

	if (unos(&uk, &tr) !=0) return 0;

	if (alociraj1(uk, &mat) != 0) return 0;

	if (alocirajPomocnu(tr, &term) != 0) return 0;

	ucitaj(uk, &mat);
	if (proveri(uk, &mat) == 1) goto kraj;
	printf("\n");

	ispisi(uk, &mat);
	dodela(uk, tr, &mat, &term);
	drugiIspis(tr, &term);

	kraj:dealociraj(uk, &mat, &term);
	return 0;
}
