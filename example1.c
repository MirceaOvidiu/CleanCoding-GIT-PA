#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    int data;
    struct Node *next;
} NODE;

typedef struct Graph {
    int v;
    int *vis;
    NODE **alst;
} GPH;

typedef struct Stack {
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
    NODE *nn1 = create_node(dest);
    nn1->next = g->alst[src];
    g->alst[src] = nn1;

    NODE *nn2 = create_node(src);
    nn2->next = g->alst[dest];
    g->alst[dest] = nn2;
}

GPH *create_graph(int v) {
    GPH *g = malloc(sizeof(GPH));
    g->v = v;
    g->alst = malloc(v * sizeof(NODE *));
    g->vis = malloc(v * sizeof(int));

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
    g->vis[v_nr] = 1;
    printf("%d ", v_nr);
    push(v_nr, s);

    NODE *adj_list = g->alst[v_nr];
    while (adj_list != NULL) {
        int con_ver = adj_list->data;
        if (g->vis[con_ver] == 0)
            DFS(g, s, con_ver);
        adj_list = adj_list->next;
    }
}

void insert_edges(GPH *g, int edg_nr) {
    int src, dest;
    printf("Adauga %d muchii:\n", edg_nr);
    for (int i = 0; i < edg_nr; i++) {
        scanf("%d%d", &src, &dest);
        add_edge(g, src, dest);
    }
}

void wipe(GPH *g) {
    for (int i = 0; i < g->v; i++) {
        g->vis[i] = 0;
    }
}

void can_be_reversed(GPH *g, int nrv, STK *s1, STK *s2) {
    int *canbe = calloc(nrv, sizeof(int));
    
    for (int i = 0; i < nrv; i++) {
        DFS(g, s1, i);
        wipe(g);
        DFS(g, s2, i);
        
        for (int j = 0; j < nrv; j++) {
            if (s1->arr[j] == i && s2->arr[i] == j) {
                canbe[j] = 1;
                break;
            }
        }
    }
    
    printf("Vertices that can be reversed:\n");
    for (int i = 0; i < nrv; i++) {
        if (canbe[i])
            printf("%d ", i);
    }
    printf("\n");
    
    free(canbe);
}

int main() {
    int nrv;
    int edg_nr;

    printf("How many vertices does the graph have? ");
    scanf("%d", &nrv);

    printf("How many edges does the graph have? ");
    scanf("%d", &edg_nr);

    GPH *g = create_graph(nrv);
    STK *s1 = create_stack(2 * nrv);
    STK *s2 = create_stack(2 * nrv);

    insert_edges(g, edg_nr);

    can_be_reversed(g, nrv, s1, s2);

    return 0;
}
