#include<stdio.h>
#include<malloc.h>

struct Client {
	int id;
	int varsta;
	char* nume;
	float buget;
	char initialaTata;
};
struct Client initializare(int varsta, const char* nume, float buget, char initialaTata) {
	struct Client s;

	//initializare structura
	s.id = 1;
	s.varsta = varsta;
	if (nume != NULL) {
		s.nume = (char*)malloc(strlen(nume) + 1);
		for (int i = 0; i < strlen(nume) + 1; i++) {
			s.nume[i] = nume[i];
		}
	}
	else {
		s.nume = NULL;
	}
	s.buget = buget;
	s.initialaTata = initialaTata;
	return s;
}

void afisare(struct Client s) {
	//afisarea tuturor atributelor.
	printf("id: %d, varsta: %d, nume: ", s.id, s.varsta);
	for (int i = 0; i < strlen(s.nume) + 1; i++) {
		printf("%c", s.nume[i]);
	}
	printf(", buget: %f, initialaTata: %c", s.buget, s.initialaTata);

}

void afisareVector(struct Client* vector, int nrElemente) {
	//afisarea elementelor din vector apeland functia afisare
	for (int i = 0; i < nrElemente; i++) {
		afisare(vector[i]);
		printf("\n");
	}
}

float calculVarstaMedie(struct Client* vector, int nrElemente) {
	float sumaVarsta = 0;

	for (int i = 0; i < nrElemente; i++) {
		sumaVarsta += vector[i].varsta;
	}

	return sumaVarsta / nrElemente;
}

struct Client* copiazaPrimeleNElemente(struct Client* vector, int nrElemente, int nrElementeCopiate) {
	//copiem intr-un vector nou pe care il vom returna primele nrElementeCopiate
	struct Client* vectorNou = (struct Client*)malloc(nrElementeCopiate * sizeof(struct Client));

	if (nrElemente > nrElementeCopiate) {
		for (int i = 0; i < nrElementeCopiate; i++) {
			vectorNou[i] = vector[i];
			vectorNou[i].nume = (char*)malloc(strlen(vector[i].nume) + 1);
			strcpy_s(vectorNou[i].nume, strlen(vector[i].nume) + 1, vector[i].nume);
		}
	}

	return vectorNou;
}

void dezalocare(struct Client** vector, int* nrElemente) {
	//dezalocam elementele din vector si vectorul
	for (int i = 0; i < *nrElemente; i++) {
		free((*vector)[i].nume);
	}

	free(*vector);
	*vector = NULL;
	*nrElemente = 0;
}

void copiazaClientiCuBugetMare(struct Client* vector, char nrElemente, float bugetMare, struct Client** vectorNou, int* dimensiune) {
	*dimensiune = 0;
	for (int i = 0; i < nrElemente - '0'; i++) {
		if (vector[i].buget >= bugetMare) {
			(*dimensiune)++;
		}
	}

	*vectorNou = (struct Client*)malloc(*dimensiune * sizeof(struct Client));
	int index = 0;
	for (int i = 0; i < nrElemente - '0'; i++) {
		if (vector[i].buget >= bugetMare) {
			(*vectorNou)[index] = vector[i];
			(*vectorNou)[index].nume = (char*)malloc(strlen(vector[i].nume) + 1);
			strcpy_s((*vectorNou)[index].nume, strlen(vector[i].nume) + 1, vector[i].nume);
			index++;
		}
	}
}

struct Client getPrimulElementConditionat(struct Client* vector, int nrElemente, const char* conditie) {
	//trebuie cautat elementul care indeplineste o conditie
	//dupa atributul de tip char*. Acesta este returnat.
	struct Client c;
	for (int i = 0; i < nrElemente; i++) {
		if (strcmp(vector[i].nume, conditie) == 0) {
			c = vector[i];
			c.nume = (char*)malloc(sizeof(strlen(vector[i].nume) + 1));
			c.nume = vector[i].nume;
			return c;
		}
	}
}

int main() {
	struct Client firstClient = initializare(18, "Cineva", 100.6, 'N');
	struct Client secondClient = initializare(16, "Ceva", 666.6, 'I');
	struct Client thirdClient = initializare(16, "Ceva", 666.6, 'S');
	struct Client fourthClient = initializare(16, "Ceva", 666.6, 'P');
	struct Client fifthClient = initializare(16, "Ceva", 666.6, 'E');
	afisare(firstClient);
	printf("\n\n");
	printf("--------------------------------------------\n\n");

	int nrClienti = 5;
	struct Client* moreClients = (struct Client*)malloc(nrClienti * sizeof(struct Client));


	moreClients[0] = firstClient;
	moreClients[1] = secondClient;
	moreClients[2] = thirdClient;
	moreClients[3] = fourthClient;
	moreClients[4] = fifthClient;
	afisareVector(moreClients, nrClienti);

	printf("\n\n");
	printf("--------------------------------------------\n\n");

	printf("Varsta medie: %f", calculVarstaMedie(moreClients, nrClienti));

	printf("\n\n");
	printf("--------------------------------------------\n\n");

	int nrElementeCopiate = 3;
	struct Client* moreClientsTwo = copiazaPrimeleNElemente(moreClients, nrClienti, nrElementeCopiate);
	afisareVector(moreClientsTwo, nrElementeCopiate);

	printf("\n\n");
	printf("--------------------------------------------\n\n");

	afisare(getPrimulElementConditionat(moreClients, nrClienti, "Cineva"));

	printf("\n\n");
	printf("--------------------------------------------\n\n");

	struct Clienti* clientiCuBugetMare = NULL;
	int nrClientiCuBugetMare = 0;
	//printf("aaa");
	copiazaClientiCuBugetMare(moreClients, '5', 150, &clientiCuBugetMare, &nrClientiCuBugetMare);
	afisareVector(clientiCuBugetMare, nrClientiCuBugetMare);

	printf("\n\n");
	printf("--------------------------------------------\n\n");

	dezalocare(&moreClients, &nrClienti);
	printf("Vector dupa dezalocare:\n");
	afisareVector(moreClients, nrClienti);

	return 0;
}