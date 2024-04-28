/*Determinati daca exista sau nu drum direct intre doua
                 restaurante dintr-o retea de tip graf*/
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

GPH *create_graph(int v) {
    int i;
    GPH *g = malloc(sizeof(GPH));
    g->v = v;
    g->alst = malloc(sizeof(NODE *));
    g->vis = malloc(sizeof(int) * v);

    for (int i = 0; i < v; i++) {
        g->alst[i] = NULL;
        g->vis[i] = 0;
    }
    return g;
}

STK *create_stack(int scap) {
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

void insert_edges(GPH *g, int edg_nr, int nrv) {
    int src, dest, i;
    printf("adauga %d munchii (de la 1 la %d)\n", edg_nr, nrv);
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

// 0 sau 1 daca poate fi sau nu
// ajuns
void canbe(GPH *g, int nr_vertices, STK *s1, STK *s2, ) {
    int *canbe = calloc(5, sizeof(int));
    // aici i tine loc de numar adica de
    // restaurant
    for (int i = 0; i < nr_vertices; i++) {
        for (int j = 0; j < 5; j++) {
            DFS(g, s1, i);
            wipe(g, nr_vertices);
            DFS(g, s2, j);
            for (int j = 0; j < nr_vertices && !ans; j++)
                for (int i = 0; i < nr_vertices && !ans; i++)
                    if ((s1->arr[i] == j) && (s2->arr[j] == i))
                        (*canbe) = 1;
        }
    }
}

int main() {
    int nr_vertices;
    int edg_nr;
    int src, dest;
    int i;
    int vertex_1;
    int vertex_2;
    int ans;

    printf("cate noduri are girafa?");
    scanf("%d", &nr_vertices);

    printf("cate muchii are giraful?");
    scanf("%d", &edg_nr);

    GPH *g = create_graph(nr_vertices);

    STK *s1 = create_stack(2 * nr_vertices);
    STK *s2 = create_stack(2 * nr_vertices);

    insert_edges(g, edg_nr, nr_vertices);

    canbe(g, nr_vertices, s1, s2);
}
