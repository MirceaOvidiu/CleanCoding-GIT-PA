#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct GPH {
    int v;
    int *vis;
    struct Node **alst;
} GPH;

typedef struct STK {
    int t;
    int scap;
    int *arr;
} STK;

Node *create_node(int v) {
    Node *nn = malloc(sizeof(Node));
    nn->data = v;
    nn->next = NULL;
    return nn;
}

void add_edge(GPH *g, int src, int dest) {
    Node *nn_src = create_node(dest); // nod pentru nodul destinatie
    nn_src->next = g->alst[src];
    g->alst[src] = nn_src;

    Node *nn_dest = create_node(src); // nod pentru nodul sursa
    nn_dest->next = g->alst[dest];
    g->alst[dest] = nn_dest;
}



GPH *create_g(int v) {
    int i;
    GPH *g = malloc(sizeof(GPH));
    g->v = v;
    g->alst = malloc(sizeof(Node *) * v);
    g->vis = malloc(sizeof(int) * v);

    for (i = 0; i < v; i++) {
        g->alst[i] = NULL;
        g->vis[i] = 0;
    }
    return g;
}

STK *create_s(int scap) {
    STK *s = malloc(sizeof(STK));
    s->arr = malloc(scap * sizeof(int));
    s->t = -1;
    s->scap = scap;

    return s;
}

void push(int pshd, STK *s) {
    s->t = s->t + 1;
    s->arr[s->t] = pshd;
}

void DFS(GPH *g, STK *s, int v_nr) {
    Node *adj_list = g->alst[v_nr];
    g->vis[v_nr] = 1;
    printf("%d ", v_nr);
    while (adj_list != NULL) {
        int con_ver = adj_list->data;
        if (g->vis[con_ver] == 0)
            DFS(g, s, con_ver);
        adj_list = adj_list->next;
    }
    push(v_nr, s); // Adaugarea nodului in stiva se face la final
}


void insert_edges(GPH *g, int edg_nr) {
    int src, dest, i;
    printf("adauga %d muchii (de la 1 la %d)\n", edg_nr, g->v);
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

void canbe(GPH *g, int nrv, STK *s1, STK *s2) {
    int *canbe = calloc(nrv, sizeof(int));
    for (int i = 0; i < nrv; i++) {
        DFS(g, s1, i);
        wipe(g, nrv);
        DFS(g, s2, i);
        for (int j = 0; j < nrv; j++) {
            if ((s1->arr[j] == i) && (s2->arr[j] == i))
                canbe[i] = 1;
        }
    }
}


int main() {
    int nrv;
    int edg_nr;

    printf("Cate noduri are graful? ");
    scanf("%d", &nrv);

    printf("Cate muchii are graful? ");
    scanf("%d", &edg_nr);

    GPH *g = create_g(nrv);

    STK *s1 = create_s(2 * nrv);
    STK *s2 = create_s(2 * nrv);

    insert_edges(g, edg_nr);

    canbe(g, nrv, s1, s2);

    return 0;
}
