//1. Structura si functii
//Se consideră prima literă din numele vostru(i), și prima literă din prenumele vostru(a).
//Sa se construiască un articol care să conțină cele două litere.
//Exemplu: Alin Zamfiroiu->A si Z.
// Articolul Magazin :
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

// Am ales articolul ghiozdan din cadrul unui magazin online care va include urmatoarele campuri:
// Dimensiunie Lxlxa in mm
//  int cod_produs
//  float pret
//  char* nume_producator
//  char in_stoc (folosim prescurtarea Y - pentru in stoc si N- nu este in stoc)
#include <stdio.h>
#include <malloc.h>

struct dimensiuni
{
	float lungime;
	float latime;
	float adancime;
};
struct ghiozdan{
 struct dimensiuni d;
 int cod_produs;
 char* nume_producator;
 char in_stoc;
};
struct ghiozdan initializare(struct dimensiuni d_init, int cod_init, const char* nume_producator_init,char in_stoc_init) {
	struct ghiozdan g;
	g.d.adancime = d_init.adancime;
	g.d.latime = d_init.latime;
	g.d.lungime = d_init.lungime;
	g.cod_produs = cod_init;
	//g.nume_producator = (char*)malloc((strlen(nume_producator_init) + 1) * sizeof(char));
	g.in_stoc = in_stoc_init;
	return g;
	}
//struct dimensiuni initializare(float lungime_init, float latime_init, float adancime_init){
//	struct dimensiuni d;
//	d.lungime = lungime_init;
//	d.latime = latime_init;
//	d.adancime = adancime_init;
//	return d;

//}
void afisare(struct ghiozdan g, struct dimensiuni d){
	printf("Dimensiuni(Lxlxa)mm: %5.2f  %5.2f %5.2f \n", g.d.lungime, g.d.latime, g.d.adancime);
	printf("Cod produs: %d\n", g.cod_produs);
	printf("Nume producator: %s\n",g.nume_producator);
	printf("In stoc: %c\n", g.in_stoc);
}
int main()
{
	struct dimensiuni d;
	d.adancime = 150;
	d.latime = 120;
	d.lungime = 200;

	struct ghiozdan g1 = initializare(d, 130, "Adiddas", 'Y');
	afisare(g1,d);

	return 1;
}
