//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <malloc.h>
//
////trebuie sa folositi fisierul masini.txt
////sau va creati un alt fisier cu alte date
//
//struct StructuraMasina {
//	int id;
//	int nrUsi;
//	float pret;
//	char* model;
//	char* numeSofer;
//	unsigned char serie;
//};
//typedef struct StructuraMasina Masina;
//
//void afisareMasina(Masina masina) {
//	//afiseaza toate atributele unei masini
//	printf("id: %d, nrUsi: %d, pret: %f, model: ", masina.id, masina.nrUsi, masina.pret);
//	for (int i = 0; i < strlen(masina.model) + 1; i++) {
//		printf("%c", masina.model[i]);
//	}
//
//	printf(", numeSofer: ");
//
//	for (int i = 0; i < strlen(masina.numeSofer) + 1; i++) {
//		printf("%c", masina.numeSofer[i]);
//	}
//
//	printf(", serie: %c;\n", masina.serie);
//}
//
//Masina citireMasinaFisier(FILE* file) {
//	//functia citeste o masina dintr-un strceam deja deschis
//	//masina citita este returnata;
//	Masina masinaReturnata;
//	char buffer[100];
//	char separator[3] = ",\n";
//
//	fgets(buffer, 100, file);
//	int id = atoi(strtok(buffer, separator));
//	masinaReturnata.id = id;
//
//	masinaReturnata.nrUsi = atoi(strtok(NULL, separator));
//	masinaReturnata.pret = atoi(strtok(NULL, separator));
//
//	char* modelAux;
//	modelAux = strtok(NULL, separator);
//	masinaReturnata.model = (char*)malloc(strlen(modelAux) + 1);
//	strcpy_s(masinaReturnata.model, strlen(modelAux) + 1, modelAux);
//
//	char* numeSoferAux;
//	numeSoferAux = strtok(NULL, separator);
//	masinaReturnata.numeSofer = (char*)malloc(strlen(numeSoferAux) + 1);
//	strcpy_s(masinaReturnata.numeSofer, strlen(numeSoferAux) + 1, numeSoferAux);
//
//	masinaReturnata.serie = strtok(NULL, separator)[0];
//
//	return masinaReturnata;
//}
//
//struct Nod {
//	Masina masina;
//	Masina* next;
//};
//typedef struct Nod Nod;
//
//void adaugaMasinaInLista(Nod** cap, Masina masinaNoua) {
//	//adauga la final in lista primita o noua masina pe care o primim ca parametru
//	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
//
//	nodNou->masina = masinaNoua;
//
//	nodNou->masina.model = (char*)malloc(strlen(masinaNoua.model) + 1);
//	strcpy_s(nodNou->masina.model, strlen(masinaNoua.model) + 1, masinaNoua.model);
//
//	nodNou->masina.numeSofer = (char*)malloc(strlen(masinaNoua.numeSofer) + 1);
//	strcpy_s(nodNou->masina.numeSofer, strlen(masinaNoua.numeSofer) + 1, masinaNoua.numeSofer);
//
//	free(masinaNoua.model);
//	free(masinaNoua.numeSofer);
//
//	nodNou->next = NULL;
//
//	if (*cap) {
//		Nod* aux = *cap;
//		while (aux->next != NULL) {
//			aux = aux->next;
//		}
//		aux->next = nodNou;
//	}
//	else {
//		*cap = nodNou;
//	}
//}
//
//Nod* citireListaMasiniDinFisier(const char* numeFisier) {
//	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
//	//prin apelul repetat al functiei citireMasinaDinFisier()
//	//ATENTIE - la final inchidem fisierul/stream-ul
//	FILE* file = fopen(numeFisier, "r");
//	Nod* cap = NULL;
//
//	if (file != NULL) {
//		while (!feof(file)) {
//			Masina masina = citireMasinaFisier(file);
//			adaugaMasinaInLista(&cap, masina);
//		}
//	}
//
//	fclose(file);
//	return cap;
//}
//
//void afisareListaMasini(Nod* cap) {
//	//afiseaza toate elemente de tip masina din lista simplu inlantuita
//	//prin apelarea functiei afisareMasina()
//	while (cap) {
//		afisareMasina(cap->masina);
//		cap = cap->next;
//	}
//}
//
//void adaugaLaInceputInLista(Nod** cap, Masina masinaNoua) {
//	//adauga la inceputul listei o noua masina pe care o primim ca parametru
//}
//
//void dezalocareListaMasini(Nod** cap) {
//	//sunt dezalocate toate masinile si lista de elemente
//	while (*cap) {
//		Nod* aux = *cap;
//		(*cap) = (*cap)->next;
//		free(aux->masina.model);
//		free(aux->masina.numeSofer);
//		free(aux);
//	}
//}
//
//float calculeazaPretMediu(/*lista de masini*/) {
//	//calculeaza pretul mediu al masinilor din lista.
//	return 0;
//}
//
//void stergeMasiniDinSeria(/*lista masini*/ const char* serieCautata) {
//	//sterge toate masinile din lista care au seria primita ca parametru.
//	//tratati situatia ca masina se afla si pe prima pozitie, si pe ultima pozitie
//}
//
//float calculeazaPretulMasinilorUnuiSofer(/*lista masini*/ const char* numeSofer) {
//	//calculeaza pretul tuturor masinilor unui sofer.
//	return 0;
//}
//
//int main() {
//
//	Nod* cap = NULL;
//	cap = citireListaMasiniDinFisier("D:\\Coding\\ASE\\SD_C\\ANGHEL_ANDREI_MIRCEA_ActivitateSD2025\\ANGHEL_ANDREI_MIRCEA_ActivitateSD2025\\Practice\\Practice1\\masini.txt");
//
//	afisareListaMasini(cap);
//
//	printf("\n\n");
//	printf("--------------------------------------------\n\n");
//
//	dezalocareListaMasini(&cap);
//	printf("Lista dezalocata:");
//
//	afisareListaMasini(cap);
//
//	return 0;
//}