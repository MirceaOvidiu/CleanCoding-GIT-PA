#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    int data;
    struct Node *next;
} NODE;

typedef struct {
    int v;        
    struct Node **alst; 
} GRAPH;

NODE *create_node(int v) {
    NODE *nn = malloc(sizeof(NODE));
    nn->data = v;
    nn->next = NULL;
    return nn;
}

void add_edge(GRAPH *g, int src, int dest) {
    NODE *nn = create_node(dest);
    nn->next = g->alst[src];
    g->alst[src] = nn;

    nn = create_node(src);
    nn->next = g->alst[dest];
    g->alst[dest] = nn;
}

GRAPH *create_graph(int v) {
    GRAPH *g = malloc(sizeof(GRAPH));
    g->v = v;
    g->alst = malloc(v * sizeof(NODE*));
    for (int i = 0; i < v; i++) {
        g->alst[i] = NULL;
    }
    return g;
}

int has_direct_edge(GRAPH *g, int src, int dest) {
    NODE *temp = g->alst[src];
    while (temp != NULL) {
        if (temp->data == dest) return 1;
        temp = temp->next;
    }
    return 0;
}

int main() {
    int num_nodes, num_edges;
    printf("Cate noduri are graficul? ");
    scanf("%d", &num_nodes);

    printf("Cate muchii are graficul? ");
    scanf("%d", &num_edges);

    GRAPH *g = create_graph(num_nodes);

    printf("Introduceti perechile de noduri pentru muchii:\n");
    for (int i = 0; i < num_edges; i++) {
        int src, dest;
        scanf("%d %d", &src, &dest);
        add_edge(g, src, dest);
    }

    int src, dest;
    printf("Introduceti nodurile intre care sa verificati existenta unei muchii directe: ");
    scanf("%d %d", &src, &dest);

    if (has_direct_edge(g, src, dest)) {
        printf("Exista o muchie directa intre nodul %d si nodul %d.\n", src, dest);
    } else {
        printf("Nu exista o muchie directa intre nodul %d si nodul %d.\n", src, dest);
    }

    return 0;
}
