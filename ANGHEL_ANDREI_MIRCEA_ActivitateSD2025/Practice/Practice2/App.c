#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#define main    SDL_main

//trebuie sa folositi fisierul masini.txt
//sau va creati un alt fisier cu alte date

struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;

void afisareMasina(Masina masina) {
	//afiseaza toate atributele unei masini
	printf("id: %d, nrUsi: %d, pret: %.2f, model: ", masina.id, masina.nrUsi, masina.pret);
	for (int i = 0; i < strlen(masina.model) + 1; i++) {
		printf("%c", masina.model[i]);
	}

	printf(", numeSofer: ");

	for (int i = 0; i < strlen(masina.numeSofer) + 1; i++) {
		printf("%c", masina.numeSofer[i]);
	}

	printf(", serie: %c;\n", masina.serie);
}

Masina citireMasinaFisier(FILE* file) {
	//functia citeste o masina dintr-un strceam deja deschis
	//masina citita este returnata;
	Masina masinaReturnata;
	char buffer[100];
	char separator[3] = ",\n";

	fgets(buffer, 100, file);
	int id = atoi(strtok(buffer, separator));
	masinaReturnata.id = id;

	masinaReturnata.nrUsi = atoi(strtok(NULL, separator));
	masinaReturnata.pret = atoi(strtok(NULL, separator));

	char* modelAux;
	modelAux = strtok(NULL, separator);
	masinaReturnata.model = (char*)malloc(strlen(modelAux) + 1);
	strcpy_s(masinaReturnata.model, strlen(modelAux) + 1, modelAux);

	char* numeSoferAux;
	numeSoferAux = strtok(NULL, separator);
	masinaReturnata.numeSofer = (char*)malloc(strlen(numeSoferAux) + 1);
	strcpy_s(masinaReturnata.numeSofer, strlen(numeSoferAux) + 1, numeSoferAux);

	masinaReturnata.serie = strtok(NULL, separator)[0];

	return masinaReturnata;
}

struct Nod {
	Masina masina;
	struct Nod* next;
};
typedef struct Nod Nod;

void adaugaMasinaInLista(Nod** cap, Masina masinaNoua) {
	//adauga la final in lista primita o noua masina pe care o primim ca parametru
	Nod* nodNou = (Nod*)malloc(sizeof(Nod));

	nodNou->masina = masinaNoua;

	nodNou->masina.model = (char*)malloc(strlen(masinaNoua.model) + 1);
	strcpy_s(nodNou->masina.model, strlen(masinaNoua.model) + 1, masinaNoua.model);

	nodNou->masina.numeSofer = (char*)malloc(strlen(masinaNoua.numeSofer) + 1);
	strcpy_s(nodNou->masina.numeSofer, strlen(masinaNoua.numeSofer) + 1, masinaNoua.numeSofer);

	free(masinaNoua.model);
	free(masinaNoua.numeSofer);

	nodNou->next = NULL;

	if (*cap) {
		Nod* aux = *cap;
		while (aux->next != NULL) {
			aux = aux->next;
		}
		aux->next = nodNou;
	}
	else {
		*cap = nodNou;
	}
}

Nod* citireListaMasiniDinFisier(const char* numeFisier) {
	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
	//prin apelul repetat al functiei citireMasinaDinFisier()
	//ATENTIE - la final inchidem fisierul/stream-ul
	FILE* file = fopen(numeFisier, "r");
	Nod* cap = NULL;

	if (file != NULL) {
		while (!feof(file)) {
			Masina masina = citireMasinaFisier(file);
			adaugaMasinaInLista(&cap, masina);
		}
	}

	fclose(file);
	return cap;
}

void afisareListaMasini(Nod* cap) {
	//afiseaza toate elemente de tip masina din lista simplu inlantuita
	//prin apelarea functiei afisareMasina()
	while (cap) {
		afisareMasina(cap->masina);
		cap = cap->next;
	}
}

void adaugaLaInceputInLista(Nod** cap, Masina masinaNoua) {
	//adauga la inceputul listei o noua masina pe care o primim ca parametru
	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
	nodNou->masina = masinaNoua;

	if (*cap) {
		Nod* aux = *cap;
		nodNou->next = aux;
		*cap = nodNou;
	}
	else {
		*cap = nodNou;
	}
}

void dezalocareListaMasini(Nod** cap) {
	//sunt dezalocate toate masinile si lista de elemente
	while (*cap) {
		Nod* aux = *cap;
		(*cap) = (*cap)->next;
		free(aux->masina.model);
		free(aux->masina.numeSofer);
		free(aux);
	}
}

float calculeazaPretMediu(Nod* cap) {
	//calculeaza pretul mediu al masinilor din lista.
	int sum = 0;
	int counter = 0;

	while (cap) {
		sum += cap->masina.pret;
		counter++;
		cap = cap->next;
	}

	return sum/counter;
}

void stergeMasiniDinSeria(Nod** cap, const char* serieCautata) {
	//sterge toate masinile din lista care au seria primita ca parametru.
	//tratati situatia ca masina se afla si pe prima pozitie, si pe ultima pozitie

	//Primul element
	if ((*cap)->masina.serie == (*serieCautata)) {
		Nod* secondAux = (*cap);
		(*cap) = (*cap)->next;
		free(secondAux->masina.model);
		free(secondAux->masina.numeSofer);
		free(secondAux);
	}

	int helper = 1;
	Nod* aux = *cap;
	while (aux->next != NULL) {
		if (aux->next->masina.serie == (*serieCautata)) {
			Nod* thirdAux = aux->next;
			if (aux->next->next == NULL) {
				aux->next = NULL;
				helper = 0;
			}
			else {
				aux->next = aux->next->next;
			}
			free(thirdAux->masina.model);
			free(thirdAux->masina.numeSofer);
			free(thirdAux);
		}

		if (helper == 1) {
			aux = aux->next;
		}
	}
}

float calculeazaPretulMasinilorUnuiSofer(Nod* cap, const char* numeSofer) {
	//calculeaza pretul tuturor masinilor unui sofer.
	float sum = 0;

	while (cap) {
		if (strcmp(cap->masina.numeSofer, numeSofer) == 0) {
			sum += cap->masina.pret;
		}
		cap = cap->next;
	}

	return sum;
}

#undef main
int main() {

	Nod* cap = NULL;
	cap = citireListaMasiniDinFisier("D:\\Coding\\ASE\\SD_C\\ANGHEL_ANDREI_MIRCEA_ActivitateSD2025\\ANGHEL_ANDREI_MIRCEA_ActivitateSD2025\\Practice\\Practice1\\masini.txt");

	printf("Citire lista din fisier si afisare:\n");
	afisareListaMasini(cap);

	printf("\n\n");
	printf("--------------------------------------------\n\n");

	printf("Pretul mediu: %.2f", calculeazaPretMediu(cap));

	printf("\n\n");
	printf("--------------------------------------------\n\n");

	printf("Stergere masini cu seria A:\n");
	stergeMasiniDinSeria(&cap, "A");
	afisareListaMasini(cap);

	printf("\nStergere masini cu seria B:\n");
	stergeMasiniDinSeria(&cap, "B");
	afisareListaMasini(cap);

	printf("\nStergere masini cu seria J:\n");
	stergeMasiniDinSeria(&cap, "J");
	afisareListaMasini(cap);

	printf("\n\n");
	printf("--------------------------------------------\n\n");

	printf("Adaugare la inceputul listei:\n");
	FILE* f = fopen("D:\\Coding\\ASE\\SD_C\\ANGHEL_ANDREI_MIRCEA_ActivitateSD2025\\ANGHEL_ANDREI_MIRCEA_ActivitateSD2025\\Practice\\Practice1\\masini.txt", "r");
	Masina masinaNoua = citireMasinaFisier(f);
	adaugaLaInceputInLista(&cap, masinaNoua);
	fclose(f);
	
	afisareListaMasini(cap);

	printf("\n\n");
	printf("--------------------------------------------\n\n");

	printf("Pretul mediu: %.2f", calculeazaPretMediu(cap));

	printf("\n\n");
	printf("--------------------------------------------\n\n");

	printf("Pretul masinilor soferului Ionescu: %.2f", calculeazaPretulMasinilorUnuiSofer(cap, "Ionescu"));

	printf("\n\n");
	printf("--------------------------------------------\n\n");

	dezalocareListaMasini(&cap);
	printf("Lista dezalocata:");

	afisareListaMasini(cap);

	return 0;
}