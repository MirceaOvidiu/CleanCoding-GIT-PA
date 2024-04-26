#include <stdio.h>
#include <stdlib.h>

// Definiți o structură de nod pentru lista de adiacență
typedef struct Nod {
    int data;
    struct Nod *next;
} Nod;

// Definiți o structură de graf
typedef struct Graf {
    int varfuri;
    int *vizitat;
    Nod **liste_adiacente;
} Graf;

// Prototipurile funcțiilor
Nod *creare_nod(int v);
Graf *creare_graf(int varfuri);
void adauga_muchie(Graf *graf, int src, int dest);
void introduceti_muchii(int nr_varfuri, int nr_muchii, Graf *graf);
int este_gol(Nod *coada);
void adauga_in_coada(Nod **coada, int data);
int extrage_din_coada(Nod **coada);
void afiseaza_graf(Graf *graf);
void afiseaza_coada(Nod *coada);
void resetare_vizitate(Graf *graf, int nr_varfuri);
void DFS(Graf *graf, int varf);
void BFS(Graf *graf, int start);

// Funcție pentru a crea un nou nod
Nod *creare_nod(int v) {
    Nod *nod_nou = malloc(sizeof(Nod));
    nod_nou->data = v;
    nod_nou->next = NULL;
    return nod_nou;
}

// Funcție pentru a crea un graf cu numărul dat de varfuri
Graf *creare_graf(int varfuri) {
    int i;
    Graf *graf = malloc(sizeof(Graf));
    graf->varfuri = varfuri;
    graf->liste_adiacente = malloc(varfuri * sizeof(Nod *));
    graf->vizitat = malloc(sizeof(int) * varfuri);

    for (i = 0; i < varfuri; i++) {
        graf->liste_adiacente[i] = NULL;
        graf->vizitat[i] = 0;
    }
    return graf;
}

// Funcție pentru a adăuga o muchie la graf
void adauga_muchie(Graf *graf, int src, int dest) {
    Nod *nod_nou = creare_nod(dest);
    nod_nou->next = graf->liste_adiacente[src];
    graf->liste_adiacente[src] = nod_nou;

    nod_nou = creare_nod(src);
    nod_nou->next = graf->liste_adiacente[dest];
    graf->liste_adiacente[dest] = nod_nou;
}

// Funcție pentru a introduce muchiile grafului
void introduceti_muchii(int nr_varfuri, int nr_muchii, Graf *graf) {
    int src, dest, i;
    printf("Adăugați %d muchii (de la 1 la %d)\n", nr_muchii, nr_varfuri);
    for (i = 0; i < nr_muchii; i++) {
        scanf("%d %d", &src, &dest);
        adauga_muchie(graf, src, dest);
    }
}

// Funcție pentru a verifica dacă coada este goală
int este_gol(Nod *coada) {
    return coada == NULL;
}

// Funcție pentru a adăuga un element în coadă
void adauga_in_coada(Nod **coada, int data) {
    Nod *nod_nou = creare_nod(data);
    if (este_gol(*coada)) {
        *coada = nod_nou;
    } else {
        Nod *temp = *coada;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = nod_nou;
    }
}

// Funcție pentru a elimina un element din coadă
int extrage_din_coada(Nod **coada) {
    int data = (*coada)->data;
    Nod *temp = *coada;
    *coada = (*coada)->next;
    free(temp);
    return data;
}

// Funcție pentru a afișa graficul
void afiseaza_graf(Graf *graf) {
    int i;
    for (i = 0; i < graf->varfuri; i++) {
        printf("Varful %d: ", i);
        Nod *temp = graf->liste_adiacente[i];
        while (temp) {
            printf("%d ", temp->data);
            temp = temp->next;
        }
        printf("\n");
    }
}

// Funcție pentru a reseta lista vizitată
void resetare_vizitate(Graf *graf, int nr_varfuri) {
    for (int i = 0; i < nr_varfuri; i++) {
        graf->vizitat[i] = 0;
    }
}

// Căutare în adâncime
void DFS(Graf *graf, int varf) {
    graf->vizitat[varf] = 1;
    printf("%d -> ", varf);

    Nod *temp = graf->liste_adiacente[varf];
    while (temp != NULL) {
        int varf_adiacent = temp->data;
        if (graf->vizitat[varf_adiacent] == 0) {
            DFS(graf, varf_adiacent);
        }
        temp = temp->next;
    }
}

// Căutare în lățime
void BFS(Graf *graf, int start) {
    Nod *coada = NULL;
    graf->vizitat[start] = 1;
    adauga_in_coada(&coada, start);

    while (!este_gol(coada)) {
        int curent = extrage_din_coada(&coada);
        printf("%d ", curent);

        Nod *temp = graf->liste_adiacente[curent];
        while (temp) {
            int varf_adiacent = temp->data;
            if (graf->vizitat[varf_adiacent] == 0) {
                graf->vizitat[varf_adiacent] = 1;
                adauga_in_coada(&coada, varf_adiacent);
            }
            temp = temp->next;
        }
    }
}

int main() {
    int nr_varfuri, nr_muchii, varf_start;

    printf("Câte varfuri are graficul? ");
    scanf("%d", &nr_varfuri);

    printf("Câte muchii are graficul? ");
    scanf("%d", &nr_muchii);

    Graf *graf = creare_graf(nr_varfuri);
    introduceti_muchii(nr_varfuri, nr_muchii, graf);

    printf("De unde să înceapă DFS? ");
    scanf("%d", &varf_start);
    printf("Parcurgere DFS: ");
    DFS(graf, varf_start);
    resetare_vizitate(graf, nr_varfuri);
    printf("\n");

    printf("De unde să înceapă BFS? ");
    scanf("%d", &varf_start);
    printf("Parcurgere BFS: ");
    BFS(graf, varf_start);

    return 0;
}
