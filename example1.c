#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    int data;
    struct Node *next;
} NODE;

typedef struct g {
    int v;
    int *vis;
    struct Node **alst;
} GPH;

typedef struct s {
    int t;
    int scap;
    int *arr;
} STK;

NODE *create_node(int v) {
    NODE *nn = malloc(sizeof(NODE));
    nn->data = v;
    nn->next = NULL;
    return nn;
}

void add_edge(GPH *g, int src, int dest) {
    NODE *nn = create_node(dest);
    nn->next = g->alst[src];
    g->alst[src] = nn;
    nn = create_node(src);
    nn->next = g->alst[dest];
    g->alst[dest] = nn;
}

GPH *create_g(int v) {
    int i;
    GPH *g = malloc(sizeof(GPH));
    g->v = v;
    g->alst = malloc(sizeof(NODE *));
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

void wipe(GPH *g, int nrv) {
    int i;
    for (i = 0; i < nrv; i++) {
        g->vis[i] = 0;
    }
}

void DFS(GPH *g, STK *s, int v_nr) {
    NODE *adj_list = g->alst[v_nr];
    NODE *aux = adj_list;
    g->vis[v_nr] = 1;
    printf("%d ", v_nr);
    push(v_nr, s);
    while (aux != NULL) {
        int con_ver = aux->data;
        if (g->vis[con_ver] == 0)
            DFS(g, s, con_ver);
        aux = aux->next;
    }
}

void insert_edges(GPH *g, int edg_nr, int nrv) {
    int src, dest, i;
    printf("Adauga %d muchii (de la 1 la %d)\n", edg_nr, nrv);
    for (i = 0; i < edg_nr; i++) {
        scanf("%d%d", &src, &dest);
        add_edge(g, src, dest);
    }
}

void canbe(GPH *g, int nrv, STK *s1, STK *s2) {
    int i, j;
    for (i = 0; i < nrv; i++) {
        DFS(g, s1, i);
        wipe(g, nrv);
        DFS(g, s2, j);
        for (j = 0; j < nrv; j++) {
            if ((s1->arr[i] == j) && (s2->arr[j] == i)) {
                printf("%d can reach %d\n", i, j);
            }
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

    insert_edges(g, edg_nr, nrv);

    canbe(g, nrv, s1, s2);

    return 0;
}
