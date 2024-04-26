#include <stdio.h>
#include <stdlib.h>

// Structura pentru un nod într-o listă de adiacență
typedef struct Nod {
    int data;
    struct Nod *next;
} Nod;

// Structura pentru un graf
typedef struct Graf {
    int noduri;
    int *vizitat;
    Nod **liste_adiacente;
} Graf;

// Structura pentru o stivă
typedef struct Stiva {
    int varf;
    int capacitate;
    int *vector;
} Stiva;

// Prototipurile funcțiilor
Nod *creare_nod(int v);
void adauga_muchie(Graf *g, int src, int dest);
Graf *creare_graf(int noduri);
Stiva *creare_stiva(int capacitate);
void apasa(Stiva *s, int valoare);
int extrage(Stiva *s);
void DFS(Graf *g, Stiva *s, int nod);
void introducere_muchii(Graf *g, int numar_muchii);
void reseteaza_vizitate(Graf *g);
void pot_fi_schimbate(Graf *g, Stiva *s1, Stiva *s2);

// Funcția pentru crearea unui nod nou
Nod *creare_nod(int v) {
    Nod *nod_nou = malloc(sizeof(Nod));
    nod_nou->data = v;
    nod_nou->next = NULL;
    return nod_nou;
}

// Funcția pentru adăugarea unei muchii la graf
void adauga_muchie(Graf *g, int src, int dest) {
    Nod *nod_nou = creare_nod(dest);
    nod_nou->next = g->liste_adiacente[src];
    g->liste_adiacente[src] = nod_nou;

    nod_nou = creare_nod(src);
    nod_nou->next = g->liste_adiacente[dest];
    g->liste_adiacente[dest] = nod_nou;
}

// Funcția pentru crearea unui graf cu un număr dat de noduri
Graf *creare_graf(int noduri) {
    int i;
    Graf *g = malloc(sizeof(Graf));
    g->noduri = noduri;
    g->liste_adiacente = malloc(noduri * sizeof(Nod *));
    g->vizitat = malloc(noduri * sizeof(int));

    for (i = 0; i < noduri; i++) {
        g->liste_adiacente[i] = NULL;
        g->vizitat[i] = 0;
    }
    return g;
}

// Funcția pentru crearea unei stive cu o anumită capacitate
Stiva *creare_stiva(int capacitate) {
    Stiva *stiva = malloc(sizeof(Stiva));
    stiva->capacitate = capacitate;
    stiva->varf = -1;
    stiva->vector = malloc(capacitate * sizeof(int));
    return stiva;
}

// Funcția pentru adăugarea unui element în vârful stivei
void apasa(Stiva *s, int valoare) {
    s->vector[++s->varf] = valoare;
}

// Funcția pentru extragerea unui element din vârful stivei
int extrage(Stiva *s) {
    return s->vector[s->varf--];
}

// Parcurgerea în adâncime (DFS)
void DFS(Graf *g, Stiva *s, int nod) {
    Nod *lista_adiacente = g->liste_adiacente[nod];
    Nod *aux = lista_adiacente;
    g->vizitat[nod] = 1;
    printf("%d ", nod);
    apasa(s, nod);
    while (aux != NULL) {
        int nod_adiacent = aux->data;
        if (g->vizitat[nod_adiacent] == 0)
            DFS(g, s, nod_adiacent);
        aux = aux->next;
    }
}

// Funcția pentru introducerea muchiilor în graf
void introducere_muchii(Graf *g, int numar_muchii) {
    int src, dest, i;
    printf("Adauga %d muchii (de la 1 la %d)\n", numar_muchii, g->noduri);
    for (i = 0; i < numar_muchii; i++) {
        scanf("%d %d", &src, &dest);
        adauga_muchie(g, src, dest);
    }
}

// Funcția pentru resetarea vectorului de vizitare a nodurilor
void reseteaza_vizitate(Graf *g) {
    for (int i = 0; i < g->noduri; i++) {
        g->vizitat[i] = 0;
    }
}

// Funcția pentru verificarea dacă nodurile pot fi schimbate între ele în timpul parcurgerilor DFS
void pot_fi_schimbate(Graf *g, Stiva *s1, Stiva *s2) {
    int *pot_fi_schimbate = calloc(g->noduri, sizeof(int));
    for (int i = 0; i < g->noduri; i++) {
        reseteaza_vizitate(g);
        DFS(g, s1, i);  // Parcurgere DFS cu prima stivă începând de la nodul i
        reseteaza_vizitate(g);
        DFS(g, s2, i);  // Parcurgere DFS cu a doua stivă începând de la nodul i
        // Verificare dacă nodurile corespunzătoare pot fi schimbate între ele
        for (int j = 0; j < g->noduri; j++) {
            if (s1->vector[j] != s2->vector[j]) {
                pot_fi_schimbate[i] = 1;
                break;
            }
        }
    }
    // Afișare rezultat
    printf("Nodurile care pot fi schimbate între ele:\n");
    int gasit = 0;
    for (int i = 0; i < g->noduri; i++) {
        if (pot_fi_schimbate[i]) {
            printf("%d ", i);
            gasit = 1;
        }
    }
    if (!gasit) {
        printf("Nu există noduri care pot fi schimbate între ele.");
    }
    printf("\n");
}

// Funcția principală
int main() {
    int noduri, muchii;

    printf("Câte noduri are graful? ");
    scanf("%d", &noduri);

    printf("Câte muchii are graful? ");
    scanf("%d", &muchii);

    Graf *graf = creare_graf(noduri);
    introducere_muchii(graf, muchii);

    Stiva *stiva1 = creare_stiva(2 * noduri);
    Stiva *stiva2 = creare_stiva(2 * noduri);

    pot_fi_schimbate(graf, stiva1, stiva2);

    return 0;
}
