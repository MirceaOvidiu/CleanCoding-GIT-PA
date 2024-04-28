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

GPH *create_graph(int nr_vertices) {
    int i;
    GPH *g = malloc(sizeof(GPH));
    g->v = nr_vertices;
    g->alst = malloc(nr_vertices* sizeof(NODE *));
    g->vis = malloc(sizeof(int) * nr_vertices);

    for (int i = 0; i < nr_vertices; i++) {
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

void push(int pshd, STK *stack) {
    stack->t = stack->t + 1;
    stack->arr[stack->t] = pshd;
}

void DFS(GPH *g, STK *s, int v_nr) {
    NODE *adj_list = g->alst[v_nr];
    NODE *aux = adj_list;
    g->vis[v_nr] = 1;

    printf("%d test", v_nr);
    push(v_nr, s);
    
    while (aux != NULL) {
        printf("%d\n", aux->data);
        int con_ver = aux->data;
        
        if (g->vis[con_ver] == 0)
            DFS(g, s, con_ver);
        
        aux = aux->next;
    }

    printf("done\n");
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
void canbe(GPH *g, int nr_vertices, STK *s1, STK *s2, int vertex1, int vertex2) {
    int *canbe = calloc(5, sizeof(int));
    int ans=0;
    // aici i tine loc de numar adica de
    // restaurant
    for (int i = 0; (i < nr_vertices) && !ans ; i++) {
        for (int j = 0; (j < nr_vertices) && (!ans); j++) {
            DFS(g, s1, i);
            wipe(g, nr_vertices);
            DFS(g, s2, j);
            for (int k = 0; (j < nr_vertices) && !ans; j++)
                for (int l = 0; (i < nr_vertices) && !ans; i++)
                    if ((s1->arr[i] == j) && (s2->arr[j] == i))
                        ans = 1;
        }
    } 

    if(ans) printf("Da, există drum\n");
    else printf("Nu, nu există drum\n");
}

int main() {
    int nr_vertices;
    int edg_nr;
    int src, dest;
    int i;
    int vertex_1;
    int vertex_2;
    int ans;

    printf("cate noduri are graful?");
    scanf("%d", &nr_vertices);

    printf("cate muchii are graful?");
    scanf("%d", &edg_nr);

    GPH *g = create_graph(nr_vertices);

    STK *s1 = create_stack(2 * nr_vertices);
    STK *s2 = create_stack(2 * nr_vertices);

    insert_edges(g, edg_nr, nr_vertices);

    printf("Pentru care două restaurante vreți să aflați existența unui drum?\n");
    scanf("%d%d", &vertex_1, &vertex_2);
    canbe(g, nr_vertices, s1, s2, vertex_1, vertex_2);
}
