#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct Graph {
    int v;
    int *vis;
    Node **alst;
} Graph;

typedef struct Stack {
    int t;
    int scap;
    int *arr;
} Stack;

Node *create_node(int v) {
    Node *nn = malloc(sizeof(Node));
    nn->data = v;
    nn->next = NULL;
    return nn;
}

void add_edge(Graph *g, int src, int dest) {
    Node *nn = create_node(dest);
    nn->next = g->alst[src];
    g->alst[src] = nn;

    nn = create_node(src);
    nn->next = g->alst[dest];
    g->alst[dest] = nn;
}

Graph *create_graph(int v) {
    Graph *g = malloc(sizeof(Graph));
    g->v = v;
    g->alst = malloc(sizeof(Node *) * v);
    g->vis = malloc(sizeof(int) * v);

    for (int i = 0; i < v; i++) {
        g->alst[i] = NULL;
        g->vis[i] = 0;
    }
    return g;
}

Stack *create_stack(int scap) {
    Stack *s = malloc(sizeof(Stack));
    s->arr = malloc(scap * sizeof(int));
    s->t = -1;
    s->scap = scap;

    return s;
}

void push(int pshd, Stack *s) {
    s->t = s->t + 1;
    s->arr[s->t] = pshd;
}

void DFS(Graph *g, Stack *s, int v_nr) {
    Node *adj_list = g->alst[v_nr];
    g->vis[v_nr] = 1;
    printf("%d ", v_nr);
    push(v_nr, s);

    Node *aux = adj_list;
    while (aux != NULL) {
        int con_ver = aux->data;
        if (g->vis[con_ver] == 0)
            DFS(g, s, con_ver);
        aux = aux->next;
    }
}

void insert_edges(Graph *g, int edg_nr) {
    int src, dest;
    printf("Adauga %d muchii:\n", edg_nr);
    for (int i = 0; i < edg_nr; i++) {
        scanf("%d%d", &src, &dest);
        add_edge(g, src, dest);
    }
}

void wipe(Graph *g) {
    for (int i = 0; i < g->v; i++) {
        g->vis[i] = 0;
    }
}

void can_reach(Graph *g, int nrv, Stack *s1, Stack *s2) {
    for (int i = 0; i < nrv; i++) {
        DFS(g, s1, i);
        wipe(g);
        DFS(g, s2, i);
        printf("\n");
    }
}

int main() {
    int nrv, edg_nr;

    printf("Cate noduri are graf-ul? ");
    scanf("%d", &nrv);

    printf("Cate muchii are graf-ul? ");
    scanf("%d", &edg_nr);

    Graph *g = create_graph(nrv);
    Stack *s1 = create_stack(2 * nrv);
    Stack *s2 = create_stack(2 * nrv);

    insert_edges(g, edg_nr);

    can_reach(g, nrv, s1, s2);

    return 0;
}
