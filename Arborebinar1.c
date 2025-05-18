#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;

struct Nod {
	Masina infoUtil;
	struct Nod* FiuStang;
	struct Nod* FiuDrept;
};
typedef struct Nod Nod;

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


void adaugaMasinaInArbore(Nod** radacina, Masina masinaNoua) {
	if (*radacina != NULL)
	{
		if (masinaNoua.id > ((*radacina)->infoUtil.id)) {
			adaugaMasinaInArbore(&(*radacina)->FiuDrept, masinaNoua);
		}
		else {
			adaugaMasinaInArbore(&(*radacina)->FiuStang, masinaNoua);

		}

	}
	else {
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->FiuStang = NULL;
		nou->FiuDrept = NULL;
		nou->infoUtil = masinaNoua;
		nou->infoUtil.numeSofer = (char*)malloc(sizeof(char) * (strlen(masinaNoua.numeSofer) + 1));
		//strcpy_s(nou->infoUtil.numeSofer, strlen(masinaNoua.numeSofer) + 1, masinaNoua.numeSofer);
		strcpy(nou->infoUtil.numeSofer, masinaNoua.numeSofer);
		nou->infoUtil.model = (char*)malloc(sizeof(char) * (strlen(masinaNoua.model) + 1));
		strcpy(nou->infoUtil.model, masinaNoua.model);
		(*radacina) = nou;

	}
}

Nod* citireArboreDeMasiniDinFisier(const char* numeFisier) {
	FILE* file = fopen(numeFisier, "r");
	Nod* nou = NULL;
	if (file != NULL)
	{

		while (!feof(file)) {
			Masina masinaNoua = citireMasinaDinFisier(file);
			adaugaMasinaInArbore(&nou, masinaNoua);
			free(masinaNoua.model);
			free(masinaNoua.numeSofer);

		}

	}
	fclose(file);
	return nou;
}

void afisareMasiniDinArbore(Nod* radacina) {

	//afisare RSD preordine
	if (radacina != NULL)
	{
		afisareMasina(radacina->infoUtil);
		afisareMasiniDinArbore(radacina->FiuStang);
		afisareMasiniDinArbore(radacina->FiuDrept);

	}
	////afisare srd inordine
	//if (radacina != NULL)
	//{
	//	
	//	afisareMasiniDinArbore(radacina->FiuStang);
	//	afisareMasina(radacina->infoUtil);
	//	afisareMasiniDinArbore(radacina->FiuDrept);

	//}

	////afisare sdr postordine
	//if (radacina != NULL)
	//{

	//	afisareMasiniDinArbore(radacina->FiuStang);
	//	afisareMasiniDinArbore(radacina->FiuDrept);
	//	afisareMasina(radacina->infoUtil);

}


//afiseaza toate elemente de tip masina din arborele creat
//prin apelarea functiei afisareMasina()
//parcurgerea arborelui poate fi realizata in TREI moduri
//folositi toate cele TREI moduri de parcurgere


void dezalocareArboreDeMasini(Nod** radacina) {
	if (*radacina != NULL) {
		dezalocareArboreDeMasini(&(*radacina)->FiuStang);
		dezalocareArboreDeMasini(&(*radacina)->FiuDrept);
		free(&(*radacina)->infoUtil.numeSofer);
		free(&(*radacina)->infoUtil.model);
		free(*radacina);
		*radacina = NULL;
	}
}

Masina getMasinaByID(Nod* radacina, int id) {
	Masina m;
	m.id = -1;
	if (radacina != NULL) {
		if (id > radacina->infoUtil.id)getMasinaByID(radacina->FiuDrept, id);
		else
			if (id < radacina->infoUtil.id)
				getMasinaByID(radacina->FiuStang, id);
			else
			{
				return radacina->infoUtil;

			}
	}
	return m;
}

int determinaNumarNoduri(Nod* rad) {

	if (rad != NULL) {
		return 1 + determinaNumarNoduri(rad->FiuStang) + determinaNumarNoduri(rad->FiuDrept);
	}
	else return 0;
}

int calculeazaInaltimeArbore(/*arbore de masini*/) {
	//calculeaza inaltimea arborelui care este data de 
	//lungimea maxima de la radacina pana la cel mai indepartat nod frunza
	return 0;
}

float calculeazaPretTotal(Nod* rad) {
	if (rad != NULL) {
		return rad->infoUtil.pret + calculeazaPretTotal(rad->FiuStang) + calculeazaPretTotal(rad->FiuDrept);
	}
	else return 0;
}

float calculeazaPretulMasinilorUnuiSofer(/*arbore de masini*/ const char* numeSofer) {
	//calculeaza pretul tuturor masinilor unui sofer.
	return 0;
}

int main() {
	Nod* radacina = citireArboreDeMasiniDinFisier("MasiniArbori.txt");
	afisareMasiniDinArbore(radacina);
	afisareMasina(getMasinaByID(radacina, 5));
	int nr = determinaNumarNoduri(radacina);
	printf("Avem  noduri:%d\n", nr);
	float Pret = calculeazaPretTotal(radacina);
	printf("Avem  noduri:%f\n", Pret);
	return 0;
}