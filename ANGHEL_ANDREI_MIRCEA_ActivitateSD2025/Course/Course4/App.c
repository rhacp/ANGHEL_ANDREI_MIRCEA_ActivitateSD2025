#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

//creare structura pentru un nod dintr-o lista dublu inlantuita

struct Nod {
	Masina info;
	struct Nod* prev;
	struct Nod* next;
};
typedef struct Nod Nod;

struct ListaDubla {
	Nod* prim;
	Nod* ultim;
};
typedef struct ListaDubla LD;

//creare structura pentru Lista Dubla 

Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Masina m1;
	aux = strtok(buffer, sep);
	m1.id = atoi(aux);
	m1.nrUsi = atoi(strtok(NULL, sep));
	m1.pret = atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	m1.model = malloc(strlen(aux) + 1);
	strcpy_s(m1.model, strlen(aux) + 1, aux);

	aux = strtok(NULL, sep);
	m1.numeSofer = malloc(strlen(aux) + 1);
	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);

	m1.serie = *strtok(NULL, sep);
	return m1;
}

void afisareMasina(Masina masina) {
	printf("Id: %d\n", masina.id);
	printf("Nr. usi : %d\n", masina.nrUsi);
	printf("Pret: %.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume sofer: %s\n", masina.numeSofer);
	printf("Serie: %c\n\n", masina.serie);
}

void afisareListaMasiniDeLaInceput(LD lista) {
	//afiseaza toate elemente de tip masina din lista dublu inlantuita
	//prin apelarea functiei afisareMasina()
	Nod* p = lista.prim;
	while (p) {
		afisareMasina(p->info);
		p = p->next;
	}
}

void afisareListaMasiniDeLaSfarsit(LD lista) {
	//afiseaza toate elemente de tip masina din lista dublu inlantuita
	//prin apelarea functiei afisareMasina()
	Nod* p = lista.ultim;
	while (p) {
		afisareMasina(p->info);
		p = p->prev;
	}
}

void adaugaMasinaInLista(LD* lista, Masina masinaNoua) {
	//adauga la final in lista primita o noua masina pe care o primim ca parametru
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = masinaNoua;
	nou->prev = NULL;
	nou->next = NULL;

	if (lista->prim != NULL) {
		nou->prev = lista->ultim;
		lista->ultim->next = nou;
	}
	else {
		lista->prim = nou;
	}

	lista->ultim = nou;
}

void adaugaLaInceputInLista(/*lista dubla de masini*/ Masina masinaNoua) {
	//adauga la inceputul listei dublu inlantuite o noua masina pe care o primim ca parametru
}

LD citireLDMasiniDinFisier(const char* numeFisier) {
	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
	//prin apelul repetat al functiei citireMasinaDinFisier()
	//ATENTIE - la final inchidem fisierul/stream-ul
	FILE* f = fopen(numeFisier, "r");
	LD lista;
	lista.prim = NULL;
	lista.ultim = NULL;

	while (!feof(f)) {
		Masina m = citireMasinaDinFisier(f);
		adaugaMasinaInLista(&lista, m);
		// shallow copy; cauzeaza probleme daca de exemplu copiez dintr-un vector de masini, ca pe ala il dezaolc si face probleme aici ca ambii pointeri arata catre aceeasi;
	}

	return lista;
}

void dezalocareLDMasini(LD* lista) {
	//sunt dezalocate toate masinile si lista dublu inlantuita de elemente
	while (lista->prim->next) {
		lista->prim = lista->prim->next;
		free(lista->prim->prev->info.model);
		free(lista->prim->prev->info.numeSofer);
		free(lista->prim->prev);
	}
	free(lista->ultim->info.numeSofer);
	free(lista->ultim->info.model);
	free(lista->ultim);
	lista->ultim = NULL;
	lista->prim = NULL;
}

float calculeazaPretMediu(LD lista) {
	//calculeaza pretul mediu al masinilor din lista.
	float suma = 0;
	int contor = 0;

	Nod* p = lista.prim;
	while (p) {
		suma += p->info.pret;
		contor++;
		p = p->next;
	}

	if (contor > 0) {
		return suma / contor;
	}

	return 0;
}

void stergeMasinaDupaID(/*lista masini*/ int id) {
	//sterge masina cu id-ul primit.
	//tratati situatia ca masina se afla si pe prima pozitie, si pe ultima pozitie
}

char* getNumeSoferMasinaScumpa(/*lista dublu inlantuita*/) {
	//cauta masina cea mai scumpa si 
	//returneaza numele soferului acestei maasini.
	return NULL;
}

int main() {

	LD lista = citireLDMasiniDinFisier("D:\\Coding\\ASE\\SD_C\\ANGHEL_ANDREI_MIRCEA_ActivitateSD2025\\ANGHEL_ANDREI_MIRCEA_ActivitateSD2025\\Practice\\Practice1\\masini.txt");
	afisareListaMasiniDeLaInceput(lista);

	printf("\n\n");
	printf("--------------------------------------------\n\n");

	printf("\n\nInvers:\n");
	afisareListaMasiniDeLaSfarsit(lista);

	printf("\n\n");
	printf("--------------------------------------------\n\n");

	printf("Pretul mediu este: %.2f", calculeazaPretMediu(lista));

	printf("\n\n");
	printf("--------------------------------------------\n\n");

	printf("Dezaloare:");
	dezalocareLDMasini(&lista);
	return 0;
}