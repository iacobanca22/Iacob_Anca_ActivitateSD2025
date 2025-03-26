//1. Structura si functii
//Se consideră prima literă din numele vostru, și prima literă din prenumele vostru.
//Sa se construiască un articol care să conțină cele două litere.
//Exemplu: Alin Zamfiroiu->A si Z.Articolul Magazin :
//struct Magazin {
//	int cod;
//	char* denumire;
//	int nrProduse;
//	float* preturi;
//}
//Articolul trebuie să aibă logica.Articolul trebuie sa fie un substantiv.Articolul trebuie sa aibă
//cel puțin trei atribute, si cel puțin unul să fie alocat dinamic.
//Realizati o functie cu ajutorul careia sa cititi de la tastatura un articol de tipul construit de
//voi.Funcția returnează obiectul citit.
//Realizati o functie care calculeaza ceva pentru un obiect de tipul implementat de voi. (o
//	medie sau o suma, un maxim, un minim...sau orice altceva)
//	Realizati o functie care modifica pentru un obiect primit ca parametru, un anumit camp.
//	noua valoare este primita ca parametru.
//	Realizați o funcție care afișează un obiect de tipul creat.Afișarea se face la console, și sunt
//	afișate toate informațiile.
//1.Aleg substantivul familie care va avea urmatoarele atribute(pentru asociatia de locatari) :
//- int nr membri 
//- int nr apartament
//- char* nume
//- float intretinere_curenta
//2. Calculez suma ce trebuie platita la intretinere de toti proprietarii
//3. Realizez o functie care va returna intretinerea minima pe care o platesc proprietarii
//4. Realizez o functie care va returna numarul de apartamente care au la intretinere peste o suma impusa
//5. Realizez o functie care va modifica parametri necesari in cazul in care o familie se muta, parametrul constant fiind nrApartament
#include< stdio.h>
#include<stdlib.h>
#include<malloc.h>
struct Familie {
	int nrMembri;
	int nrApartament;
	char* nume;
	float intretinere;
};
struct Familie initializare(int nrMembriNou, int nrApartamentNou, const char* numeNou, float intretinereNou) {
	struct Familie f;
	f.nrMembri = nrMembriNou;
	f.nrApartament = nrApartamentNou;
	f.nume = (char*)malloc(sizeof(char) * (strlen(numeNou) + 1));
	strcpy_s(f.nume, strlen(numeNou) + 1, numeNou);
	f.intretinere = intretinereNou;
	return f;

}
void afisare(struct Familie f)
{
	if (f.nume != NULL)
	{
		printf("Familia %s are %d membri, locuieste in apartamentul  % d si are de platit luna acesta % 6.2f la intretiere lei\n", f.nume, f.nrMembri, f.nrApartament, f.intretinere);

	}
	else printf(" Datele nu sunt completate corect\n");

}
void dezalocare(struct Familie* f) {
	if (f->nume != NULL) {
		free(f->nume);
		f->nume = NULL;
	}
}

int main()
{
	struct Familie f;
	f = initializare(3,25,"Mihai",452.96);
	afisare(f);
	dezalocare(&f);
    return 0;
}