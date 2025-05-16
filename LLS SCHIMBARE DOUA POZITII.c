////Se considera lista simplu inlantuita realizata la seminar.
////1. Implementati o functie care sterge un nod de pe o pozitie data ca parametru.Daca lista
////are mai putine noduri decat index - ul dat, nu se realizeaza stergerea.
////2. Implementati o functie care sa insereze elementele in cadrul listei simplu inlantuite astfel
////incat acestea a fie sortate crescator dupa un camp la alegerea voastra.
////3. Implementati o functie care salveaza intr - un vector toate obiectele care indeplinesc o
////conditie stabilita de voi.Realizati deep copy, astfel incat elementele din vector sa fie
////diferentiate de cele din lista.Aveti grija la alocarea de spatiu, deoarece trebuie sa stabiliti
////pentru cate elemente veti aloca spatiu.
////4. Implementati o functie care primeste lista si doua pozitii.In cadrul functiei trebuie sa
////interschimbati elementele de pe cele doua pozitii din lista primita.

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

struct Nod {
    Masina info;
    struct Nod* next;
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

void afisareListaMasini(Nod* cap) {
    while (cap != NULL) {
        afisareMasina(cap->info);
        cap = cap->next;
    }
}

void adaugaMasinaInLista(Nod** cap, Masina masinaNoua) {
    Nod* nou = (Nod*)malloc(sizeof(Nod));
    nou->info = masinaNoua;
    nou->next = NULL;
    if (*cap) {
        Nod* p = *cap;
        while (p->next) {
            p = p->next;
        }
        p->next = nou;
    }
    else {
        *cap = nou;
    }
}

void adaugaLaInceputInLista(Nod** cap, Masina masinaNoua) {
    Nod* nou = (Nod*)malloc(sizeof(Nod));
    nou->info = masinaNoua;
    nou->next = *cap;
    *cap = nou;
}

Nod* citireListaMasiniDinFisier(const char* numeFisier) {
    Nod* cap = NULL;
    FILE* f = fopen(numeFisier, "r");
    if (f) {
        while (!feof(f)) {
            //creem lista cu inserare la sfarsit
            adaugaMasinaInLista(&cap, citireMasinaDinFisier(f));
        }
    }
    fclose(f);
    return cap;
}

void dezalocareListaMasini(Nod** cap) {
    while (*cap) {
        Nod* p = *cap;
        (*cap) = p->next;
        if (p->info.model) {
            free(p->info.model);
        }
        if (p->info.numeSofer) {
            free(p->info.numeSofer);
        }
        free(p);
    }
}
void dezalocaMasina(Masina* masina1)
{
    if (masina1->numeSofer!= NULL)free(masina1->numeSofer);
    if (masina1->model != NULL)free(masina1->model);
    masina1->numeSofer = NULL;
    masina1->model = NULL;
}
float calculeazaPretMediu(Nod* cap) {
    float suma = 0;
    int contor = 0;
    while (cap) {
        suma += cap->info.pret;
        contor++;
        cap = cap->next;
    }
    if (contor > 0) {
        return suma / contor;
    }
    return 0;
}

float calculeazaPretulMasinilorUnuiSofer(Nod* cap, const char* numeSofer) {
    float suma = 0;
    while (cap) {
        if (strcmp(cap->info.numeSofer, numeSofer) == 0) {
            suma += cap->info.pret;
        }
        cap = cap->next;
    }
    return suma;
}
void stergeMasiniDinSeria(Nod** cap, char serieCautata) {
    while ((*cap) && (*cap)->info.serie == serieCautata) {
        Nod* aux = *cap;
        (*cap) = aux->next;
        if (aux->info.numeSofer) {
            free(aux->info.numeSofer);
        }
        if (aux->info.model) {
            free(aux->info.model);
        }
        free(aux);
    }
    if ((*cap)) {
        Nod* p = *cap;
        while (p) {
            while (p->next && p->next->info.serie != serieCautata) {
                p = p->next;
            }
            if (p->next) {
                Nod* aux = p->next;
                p->next = aux->next;
                if (aux->info.numeSofer) {
                    free(aux->info.numeSofer);
                }
                if (aux->info.model) {
                    free(aux->info.model);
                }
                free(aux);
            }
            else {
                p = NULL;
            }
        }
    }

}
////1. Implementati o functie care sterge un nod de pe o pozitie data ca parametru.Daca lista
////are mai putine noduri decat index - ul dat, nu se realizeaza stergerea.
void StergeUnNodDupaIndex(Nod** cap, int index) {
    Nod* temp = *cap;
    int count = 0;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }

    if (index < count && index != 0) {
        printf("Avem acel index in lista\n");
        temp = *cap;
        for (int i = 0; i < index - 1; i++)temp = temp->next;
        Nod* p = temp->next;
        temp->next = p->next;
        free(p->info.numeSofer);
        free(p->info.model);
        free(p);
        printf("Nodul cu  indexul %d a fost sters cu succes.\n", index);
    }
    else {
        if (index > count) {
            printf("Index incorect, nu se face stergerea \ n");
        }
        else {
            if (index == 0)
            {
                temp = *cap;
                *cap = temp->next;
                free(temp->info.numeSofer);
                free(temp->info.model);
                free(temp);

            }
            else {
                if (index == count + 1) {
                    temp = *cap;
                    for (int i = 0; i < index; i++)temp = temp->next;
                    Nod* p = temp->next;
                    temp->next = NULL;
                    free(p->info.numeSofer);
                    free(p->info.model);
                    free(p);
                }
            }
        }
    }
}
///2. Implementati o functie care sa insereze elementele in cadrul listei simplu inlantuite astfel
////incat acestea a fie sortate crescator dupa un camp la alegerea voastra.
////3. Implementati o functie care salveaza intr - un vector toate obiectele care indeplinesc o
////conditie stabilita de voi.Realizati deep copy, astfel incat elementele din vector sa fie
////diferentiate de cele din lista.Aveti grija la alocarea de spatiu, deoarece trebuie sa stabiliti
////pentru cate elemente veti aloca spatiu.
////4. Implementati o functie care primeste lista si doua pozitii.In cadrul functiei trebuie sa
////interschimbati elementele de pe cele doua pozitii din lista primita.
void interschimba(Nod* cap, int poz1, int poz2) {
    if (poz1 == poz2) return;
    Masina* nod1 = NULL;
    Masina* nod2 = NULL;
    Nod* aux = cap;
    while (aux != NULL) {
        if (aux->info.id== poz1) copieMasinainMasina(nod1, &(aux->info));
        if (aux->info.id == poz2) copieMasinainMasina(nod2,&(aux->info));
        aux = aux->next;
        }

    if (nod1 != NULL && nod2 != NULL) {
        Masina* aux2 = NULL;
        copieMasinainMasina(aux2, nod1);
        dezalocaMasina(nod1);
        copieMasinainMasina(nod1, nod2);
        dezalocaMasina(nod2);
        copieMasinainMasina(nod2, aux);
        dezalocaMasina(aux2);

    }
}
void copieMasinainMasina(Masina* masina1, Masina* masina2)
{
    if (masina2 != NULL)
    {
        masina1->id = masina2->id;
        masina1->nrUsi = masina2->nrUsi;
        masina1->pret = masina2->pret;
        masina1->serie = masina2->serie;
        masina1->model = (char*)malloc(strlen(masina2->model) + 1);
        strcpy_s(masina2->model, strlen(masina2->model) + 1, masina2->model);
        masina1->numeSofer = (char*)malloc(strlen(masina2->numeSofer) + 1);

    }

}
int LungimeLista(Nod* cap) {
    int count = 0;
    Nod* aux = cap;
    while (cap != NULL) {
        int count = 0;
        aux = aux->next;

    }
    return count;
}
Masina ReturneazaDupaPozitie(Nod* cap, int poz)
{   Nod* temp = cap;
    while (!cap) {
        if (temp->info.id != poz) {
            temp = temp->next;
        }
        else return temp->info;
    }
}
int Nr_Noduri_Lista(Nod* cap)
{
    Nod* temp = cap;
    int count = 0;
    while (temp != NULL)
    {
        count++;
        temp = temp->next;

    }
    return count;
}
int main() {
    Nod* cap = citireListaMasiniDinFisier("masini.txt");
    afisareListaMasini(cap);
    /*printf("Pretul mediu este:%.2f\n", calculeazaPretMediu(cap));
    printf("Pretul masinilor unui Sofer este:%.2f\n",
        calculeazaPretulMasinilorUnuiSofer(cap, "Gigel"));

    printf("\nStergere seria A\n");
    stergeMasiniDinSeria(&cap, 'A');
    afisareListaMasini(cap);
    printf("\nStergere seria B\n");
    stergeMasiniDinSeria(&cap, 'B');*/
    int index;
    printf("index=");
    scanf("%d", &index);
    printf("index= %d", index);
    //StergeUnNodDupaIndex(&cap, index);
    interschimba(cap, 2, 3);
    afisareListaMasini(cap);
    dezalocareListaMasini(&cap);
    return 0;
}