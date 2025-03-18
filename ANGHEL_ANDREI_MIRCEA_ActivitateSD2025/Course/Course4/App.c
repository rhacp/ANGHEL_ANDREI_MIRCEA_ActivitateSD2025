#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
	printf("Nr. usi: %d\n", masina.nrUsi);
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

void adaugaLaInceputInLista(LD* lista, Masina masinaNoua) {
	//adauga la inceputul listei dublu inlantuite o noua masina pe care o primim ca parametru
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = masinaNoua;
	nou->prev = NULL;
	nou->next = NULL;

	if (lista->prim != NULL) {
		nou->next = lista->prim;
		lista->prim->prev = nou;
	}
	else {
		lista->ultim = nou;
	}

	lista->prim = nou;
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

	fclose(f);
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

void stergeMasinaDupaID(LD* lista, int id) {
	//sterge masina cu id-ul primit.
	//tratati situatia ca masina se afla si pe prima pozitie, si pe ultima pozitie
	Nod* p = lista->prim;
	int aux = 1;

	//Lista cu un singur nod
	if (p->prev == NULL && p->next == NULL) {
		aux = 0;
		free(p->info.model);
		free(p->info.numeSofer);
		free(p);
		p = NULL;
		lista->prim = NULL;
		lista->ultim = NULL;
	}

	while (p != NULL && aux == 1) {
		if (p->info.id == id) {
			if (p->prev == NULL) {
				p->next->prev = NULL;
				lista->prim = p->next;
			}
			else if (p->next == NULL) {
				p->prev->next = NULL;
				lista->ultim = p->prev;
			}
			else {
				p->prev->next = p->next;
				p->next->prev = p->prev;
			}
			aux = 0;
		}

		if (aux != 0) {
			p = p->next;
		}
		else {
			free(p->info.model);
			free(p->info.numeSofer);
			p->next = NULL;
			p->prev = NULL;
			free(p);
			p = NULL;
		}
	}
}

char* getNumeSoferMasinaScumpa(LD lista) {
	//cauta masina cea mai scumpa si 
	//returneaza numele soferului acestei maasini.
	char* result = NULL;
	float max = 0;

	Nod* p = lista.prim;
	while (p) {
		if (max < p->info.pret) {
			result = p->info.numeSofer;
			max = p->info.pret;
		}
		p = p->next;
	}

	char* returnString = (char*)malloc(strlen(result) + 1);
	strcpy_s(returnString, strlen(result) + 1, result);

	return returnString;
}

#undef main
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

	printf("Stergere masina dupa ID:\n");

	FILE* f = fopen("D:\\Coding\\ASE\\SD_C\\ANGHEL_ANDREI_MIRCEA_ActivitateSD2025\\ANGHEL_ANDREI_MIRCEA_ActivitateSD2025\\Practice\\Practice1\\masini.txt", "r");
	Masina firstMasina = citireMasinaDinFisier(f);
	Masina secondMasina = citireMasinaDinFisier(f);
	fclose(f);
	int id = 1;

	printf("\nPrima masina:\n");
	stergeMasinaDupaID(&lista, id);
	afisareListaMasiniDeLaInceput(lista);

	printf("\nUltima masina:\n");

	id = 10;
	stergeMasinaDupaID(&lista, id);
	afisareListaMasiniDeLaInceput(lista);

	printf("\nLista cu o singura masina:\n");
	id = 1;
	LD listaCuOSinguraMasina;
	Nod* p = (Nod*)malloc(sizeof(Nod));
	p->info = firstMasina;
	p->next = NULL;
	p->prev = NULL;
	listaCuOSinguraMasina.prim = p;
	listaCuOSinguraMasina.ultim = p;

	stergeMasinaDupaID(&listaCuOSinguraMasina, id);
	afisareListaMasiniDeLaInceput(listaCuOSinguraMasina);

	printf("\nMasina care nu e prima sau ultima:\n");

	id = 5;
	stergeMasinaDupaID(&lista, id);
	afisareListaMasiniDeLaInceput(lista);

	printf("\n\n");
	printf("--------------------------------------------\n\n");

	printf("Adaugare masina la inceput de lista:\n");
	adaugaLaInceputInLista(&lista, secondMasina);
	afisareListaMasiniDeLaInceput(lista);

	printf("\n\n");
	printf("--------------------------------------------\n\n");

	printf("Afisare nume sofer cu masina cu cel mai mare pret: ");
	char* pretMare = getNumeSoferMasinaScumpa(lista);
	printf("%s", pretMare);

	printf("\n\n");
	printf("--------------------------------------------\n\n");

	printf("Dezalocare:");
	dezalocareLDMasini(&lista);
	return 0;
}