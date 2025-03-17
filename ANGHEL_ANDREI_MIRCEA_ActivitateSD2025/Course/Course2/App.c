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
//void afisareVectorMasini(Masina* masini, int nrMasini) {
//	for (int i = 0; i < nrMasini; i++) {
//		afisareMasina(masini[i]);
//	}
//}
//
//void dezalocareVectorMasini(Masina** vector, int* nrMasini) {
//	for (int i = 0; i < (*nrMasini); i++) {
//		free((*vector)[i].model);
//		free((*vector)[i].numeSofer);
//	}
//
//	free(*vector);
//	*vector = NULL;
//	*nrMasini = 0;
//}
//
////void adaugaMasinaInVector(Masina** masini, int* nrMasini, Masina masinaNoua) {
////	//adauga in vectorul primit o noua masina pe care o primim ca parametru
////	//ATENTIE - se modifica numarul de masini din vector;
////	int aux = (*nrMasini) + 1;
////	int secondAux = sizeof(Masina*) * aux;
////	Masina* temp = (Masina*)realloc(*masini, secondAux);
////	//dezalocareVectorMasini(masini, nrMasini);
////	(*nrMasini)++;
////
////	if (temp == NULL) {
////		printf("Memory reallocation failed. New element was not added.");
////	}
////	else {
////		(*masini) = temp;
////	}
////
////	(*masini)[(*nrMasini) - 1] = masinaNoua;
////
////	(*masini)[(*nrMasini) - 1].model = (char*)malloc(strlen(masinaNoua.model) + 1);
////	strcpy_s((*masini)[(*nrMasini) - 1].model, strlen(masinaNoua.model) + 1, masinaNoua.model);
////
////	(*masini)[(*nrMasini) - 1].numeSofer = (char*)malloc(strlen(masinaNoua.numeSofer) + 1);
////	strcpy_s((*masini)[(*nrMasini) - 1].numeSofer, strlen(masinaNoua.numeSofer) + 1, masinaNoua.numeSofer);
////}
//
//void adaugaMasinaInVector(Masina** masini, int* nrMasini, Masina masinaNoua) {
//	//adauga in vectorul primit o noua masina pe care o primim ca parametru
//	//ATENTIE - se modifica numarul de masini din vector;
//	//int aux = (*nrMasini) + 1;
//	//int secondAux = sizeof(Masina*) * aux;
//	Masina* aux = (Masina*)malloc(sizeof(Masina) * ((*nrMasini) + 1));
//
//	for (int i = 0; i < *nrMasini; i++) {
//		aux[i] = (*masini)[i];
//
//		aux[i].model = (char*)malloc(strlen((*masini)[i].model) + 1);
//		strcpy_s(aux[i].model, strlen((*masini)[i].model) + 1, (*masini)[i].model);
//
//		aux[i].numeSofer = (char*)malloc(strlen((*masini)[i].numeSofer) + 1);
//		strcpy_s(aux[i].numeSofer, strlen((*masini)[i].numeSofer) + 1, (*masini)[i].numeSofer);
//	}
//
//	aux[(*nrMasini)] = masinaNoua;
//
//	aux[(*nrMasini)].model = (char*)malloc(strlen(masinaNoua.model) + 1);
//	strcpy_s(aux[(*nrMasini)].model, strlen(masinaNoua.model) + 1, masinaNoua.model);
//
//	aux[(*nrMasini)].numeSofer = (char*)malloc(strlen(masinaNoua.numeSofer) + 1);
//	strcpy_s(aux[(*nrMasini)].numeSofer, strlen(masinaNoua.numeSofer) + 1, masinaNoua.numeSofer);
//
//	//dezalocareVectorMasini(masini, nrMasini);
//	//free(*masini);
//
//	for (int i = 0; i < (*nrMasini); i++) {
//		free((*masini)[i].model);
//		free((*masini)[i].numeSofer);
//	}
//	free(*masini);
//	(*masini) = aux;
//
//	(*nrMasini)++;
//
//	//for (int i = 0; i < *nrMasini; i++) {
//	//	afisareMasina((*masini)[i]);
//	//	printf("\nNew Iteration ----------------------------\n");
//	//}
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
//Masina* citireVectorMasiniFisier(const char* numeFisier, int* nrMasiniCitite) {
//	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
//	//prin apelul repetat al functiei citireMasinaFisier()
//	//numarul de masini este determinat prin numarul de citiri din fisier
//	//ATENTIE - la final inchidem fisierul/stream-ul
//	FILE* file = fopen(numeFisier, "r");
//	Masina* vector = (Masina*)malloc(sizeof(Masina) * 0);
//	*nrMasiniCitite = 0;
//
//	while (!feof(file)) {
//		Masina masina = citireMasinaFisier(file);
//		adaugaMasinaInVector(&vector, nrMasiniCitite, masina);
//	}
//
//	fclose(file);
//	return vector;
//}
//
//int main() {
//
//	FILE* file = fopen("D:\\Coding\\ASE\\SD_C\\ANGHEL_ANDREI_MIRCEA_ActivitateSD2025\\ANGHEL_ANDREI_MIRCEA_ActivitateSD2025\\Course\\Course2\\masini.txt", "r");
//	Masina firstMasina = citireMasinaFisier(file);
//	afisareMasina(firstMasina);
//
//	printf("\n\n");
//	printf("--------------------------------------------\n\n");
//
//	int nrMasiniCitite = 0;
//
//	Masina* vectorMasini = citireVectorMasiniFisier("D:\\Coding\\ASE\\SD_C\\ANGHEL_ANDREI_MIRCEA_ActivitateSD2025\\ANGHEL_ANDREI_MIRCEA_ActivitateSD2025\\Course\\Course2\\masini.txt", &nrMasiniCitite);
//	afisareVectorMasini(vectorMasini, nrMasiniCitite);
//
//	printf("\n\n");
//	printf("--------------------------------------------\n\n");
//
//	return 0;
//}