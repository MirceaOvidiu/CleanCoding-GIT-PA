#include <stdlib.h>
#include <stdio.h>

typedef struct Node{
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
    g->alst = malloc(sizeof(NODE *) * v);
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

void wipe(GPH *g, int nrv) {
    for (int i = 0; i < nrv; i++) {
        g->vis[i] = 0;
    }
}

void canbe(GPH *g, int nrv, STK *s1, STK *s2) { // 0 sau 1 daca poate fi sau nu ajuns
    int ans = 0; // Initialize ans variable
    for (int i = 0; i < nrv && !ans; i++) { // Iterate through vertices in s1
        DFS(g, s1, i); // DFS from vertex i in s1
        wipe(g, nrv); // Reset visited array
        for (int j = 0; j < nrv && !ans; j++) { // Iterate through vertices in s2
            DFS(g, s2, j); // DFS from vertex j in s2
            int found = 0; // Initialize found variable
            for (int k = 0; k < nrv && !found; k++) { // Iterate through vertices in s1 and s2
                if (s1->arr[k] == j && s2->arr[j] == i) { // If there's a connection from s1 to s2
                    ans = 1; // Update ans to 1
                    found = 1; // Update found to 1 to break the loop
                }
            }
        }
    }
    printf("Poate fi: %d\n", ans);
}

void insert_edges(GPH *g, int edg_nr, int nrv) {
    int src, dest, i;
    printf("Adauga %d muchii (de la 1 la %d)\n", edg_nr, nrv);
    for (i = 0; i < edg_nr; i++) {
        scanf("%d %d", &src, &dest);
        add_edge(g, src, dest);
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
