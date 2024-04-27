#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} NODE;

typedef struct Graph {
    int vertices;
    int* visited;
    NODE** adjacency_lists;
} GPH;

NODE* create_node(int v) {
    NODE* new_node = malloc(sizeof(NODE));
    new_node->data = v;
    new_node->next = NULL;
    return new_node;
}

GPH* create_graph(int vertices) {
    GPH* graph = malloc(sizeof(GPH));
    graph->vertices = vertices;
    graph->adjacency_lists = malloc(vertices * sizeof(NODE*));
    graph->visited = malloc(vertices * sizeof(int));

    for (int i = 0; i < vertices; i++) {
        graph->adjacency_lists[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

void add_edge(GPH* graph, int src, int dest) {
    NODE* new_node = create_node(dest);
    new_node->next = graph->adjacency_lists[src];
    graph->adjacency_lists[src] = new_node;

    new_node = create_node(src);
    new_node->next = graph->adjacency_lists[dest];
    graph->adjacency_lists[dest] = new_node;
}

void ins_edges(int nr_of_vertices, int nr_of_edges, GPH* graph) {
    int src, dest;
    printf("Adauga %d muchii (de la 1 la %d):\n", nr_of_edges, nr_of_vertices);
    for (int i = 0; i < nr_of_edges; i++) {
        scanf("%d %d", &src, &dest);
        add_edge(graph, src, dest);
    }
}

void DFS(GPH* graph, int vertex_nr) {
    NODE* temp = graph->adjacency_lists[vertex_nr];
    graph->visited[vertex_nr] = 1;
    printf("%d->", vertex_nr);
    while (temp != NULL) {
        int connected_vertex = temp->data;
        if (graph->visited[connected_vertex] == 0) {
            DFS(graph, connected_vertex);
        }
        temp = temp->next;
    }
}

int main() {
    int nr_of_vertices, nr_of_edges, starting_vertex;
    printf("Cate noduri are graful? ");
    scanf("%d", &nr_of_vertices);
    printf("Cate muchii are graful? ");
    scanf("%d", &nr_of_edges);
    GPH* graph = create_graph(nr_of_vertices);
    ins_edges(nr_of_vertices, nr_of_edges, graph);
    printf("De unde incepe DFS? ");
    scanf("%d", &starting_vertex);
    printf("Parcurgere DFS:");
    DFS(graph, starting_vertex);
    return 0;
}
