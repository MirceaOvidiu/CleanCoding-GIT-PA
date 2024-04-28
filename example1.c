#include <stdlib.h>
#include <stdio.h>

typedef struct Node{
    int data;
    struct Node *next;
} NODE;

typedef struct g {
    int v;
    int *vis;
    NODE **alst;
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
    g->alst = malloc((v + 1) * sizeof(NODE *));//incepem nodurile de la 1 asa ca adaugam + 1 la alocarea memorie si la nrv
    g->vis = malloc((v + 1) * sizeof(int));

    for (i = 1; i <= v; i++) {
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
    if (s->t < s->scap - 1) {
        s->t = s->t + 1;
        s->arr[s->t] = pshd;
    } else {
        printf("Stack overflow error: cannot push to a full stack.\n");
    }
}

void DFS(GPH *g, STK *s, int v_nr) {
    NODE *adj_list = g->alst[v_nr];
    NODE *aux = adj_list;
    g->vis[v_nr] = 1;
    push(v_nr, s);
    while (aux != NULL) {
        int con_ver = aux->data;
        if (g->vis[con_ver] == 0){
            DFS(g, s, con_ver);}
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
    for (int i = 1; i <= nrv; i++) {
        g->vis[i] = 0;
    }
}

void print_canbe(int *canbe, int nrv) {
    printf("Rezultatele functiei canbe:\n");
    for (int i = 1; i <= nrv; i++) {
        printf("canbe[%d] = %d\n", i, canbe[i]);
    }
}

void canbe(GPH *g, int nrv, STK *s1, STK *s2) {
    int *canbe = calloc(nrv + 1, sizeof(int));
    for (int i = 1; i <= nrv; i++) {
        if (g->alst[i] != NULL) { //verificam daca nodul este izolat
            DFS(g, s1, i);
            for (int j = 0; j <= s1->t; j++) {
                wipe(g, nrv);
                DFS(g, s2, s1->arr[j]);
                for (int k = 0; k <= s2->t; k++) {
                    if (s2->arr[k] == i) {
                        canbe[i] = 1;
                        break;
                    }
                }
                if (canbe[i] == 1) {
                    break;
                }
            }
            s1->t = -1; // Resetam stivele
            s2->t = -1; //problema era la resetarea stivelor deoarece acestea avea 2*nrv dar noi punem in stiva de mult mai multe ori decat 2*nrv
            wipe(g, nrv);
        }
    }
    print_canbe(canbe, nrv);
}

int main() {
    int nrv;
    int edg_nr;

    printf("cate noduri are graful?");
    scanf("%d", &nrv);

    printf("cate muchii are graful?");
    scanf("%d", &edg_nr);

    GPH *g = create_g(nrv);

    STK *s1 = create_s(2 * nrv);
    STK *s2 = create_s(2 * nrv);

    insert_edges(g, edg_nr, nrv);

    canbe(g, nrv, s1, s2);
}
