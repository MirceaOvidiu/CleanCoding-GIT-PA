
// Determinati daca exista sau nu drum direct intre doua
//  restaurante dintr-o retea de tip graf*/
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} NODE;
/// pentru simplitate, folosim int uri pt a numi restaurantel/locatiile
/// ex: 1 - restaurantul 1 si tot asa

typedef struct g {
    int v;
    int *vis;
    struct Node **adj_list;
} GPH;

typedef struct stiva {
    int lg_drum;
    int scap;
    int *drum; // drumul pana la  restaurantul(nodul) respectiv
} STIVA;

NODE *create_node(int value) {
    NODE *nod = malloc(sizeof(NODE));
    nod->data = value;
    nod->next = NULL;
    return nod;
}

void add_edge(GPH *g, int src, int dest) {
    NODE *nn = create_node(dest);
    nn->next = g->adj_list[src];
    g->adj_list[src] = nn;
    nn = create_node(src);
    nn->next = g->adj_list[dest];
    g->adj_list[dest] = nn;
}

GPH *create_g(int v) {
    int i;
    GPH *g = (GPH *)malloc(sizeof(GPH));
    g->v = v;
    g->adj_list = (NODE **)malloc(sizeof(NODE *) * (v + 1));
    g->vis = (int *)malloc(sizeof(int) * (v + 10));

    for (int i = 0; i < v; i++) {
        g->adj_list[i] = NULL;
        g->vis[i] = 0;
    }
    return g;
}

STIVA *create_stiva(int scap) {
    STIVA *s = malloc(sizeof(STIVA));
    s->drum = malloc(scap * sizeof(int));
    s->lg_drum = -1;
    s->scap = scap;

    return s;
}

void push(int value_nod, STIVA *s) {
    s->lg_drum = s->lg_drum + 1;
    s->drum[s->lg_drum] = value_nod;
}

void DFS(GPH *g, STIVA *s, int start) {
    NODE *adj_list = g->adj_list[start];
    NODE *aux = adj_list;
    g->vis[start] = 1;
    // printf("%d ", start);
    push(start, s);
    while (aux != NULL) {
        int con_ver = aux->data;
        if (g->vis[con_ver] == 0) {
            DFS(g, s, con_ver);
        }
        aux = aux->next;
    }
}

void insert_edges(GPH *g, int edg_nr, int nrv) {
    int src, dest, i;
    printf("adauga %d muchii (de la 1 la %d)\n", edg_nr, nrv);
    for (i = 0; i < edg_nr; i++) {
        scanf("%d%d", &src, &dest);
        add_edge(g, src, dest);
    }
}

void wipe(GPH *g, int nrv) {
    for (int i = 0; i < nrv; i++) {
        g->vis[i] = 0;
    }
}

int canbe(GPH *g, int nrv, int r1, int r2) // 0 sau 1 daca poate fi sau nu ajuns
{
    int canbe = 0;

    STIVA *s1 = create_stiva(100 * nrv);
    STIVA *s2 = create_stiva(100 * nrv);
    int ans = 0;
    DFS(g, s1, r1);

    wipe(g, nrv);

    DFS(g, s2, r2);

    // aici i tine loc de numar adica de restaurant

    for (int i = 0; i < s1->lg_drum; i++) {
        for (int j = 0; j < s2->lg_drum; j++) {

            if ((s1->drum[i] == s2->drum[j])) {

                canbe = 1;
            }
        }
    }

    free(s1);
    free(s2);

    return canbe;
}

int main() {
    int nrv;
    int edg_nr;
    int src, dest;
    int i;
    int vortex_1;
    int virtex_2;
    int ans;

    printf("cate noduri are girafa?");
    scanf("%d", &nrv);

    printf("cate muchii are giraful?");
    scanf("%d", &edg_nr);

    GPH *g = create_g(nrv);

    insert_edges(g, edg_nr, nrv);
    printf("Introduceti restaurant A si resturant B:\n");
    int r1, r2;
    scanf("%d%d", &r1, &r2);
    
    if (canbe(g, nrv, r1, r2) == 1)
        printf("Exista drum intre restaurantul A - %d si B- %d\n", r1, r2);
    else
        printf("Nu exista drum intre restaurantul A - %d si B- %d\n", r1,r2);


    printf("Introduceti restaurant C si resturant D:\n");

    scanf("%d%d", &r1, &r2);
    if (canbe(g, nrv, r1, r2) == 1)
        printf("Exista drum intre restaurantul C - %d si D - %d\n", r1,r2);
    else
        printf("Nu exista drum intre restaurantul C - %d si D- %d\n",r1,r2);
}