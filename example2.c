#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} NODE;

typedef struct {
    int vertices;
    int *visited;
    NODE **adjacency_lists;
} GRAPH;

NODE *create_node(int v) {
    NODE *new_node = malloc(sizeof(NODE));
    new_node->data = v;
    new_node->next = NULL;
    return new_node;
}

GRAPH *create_graph(int vertices) {
    GRAPH *graph = malloc(sizeof(GRAPH));
    graph->vertices = vertices;
    graph->adjacency_lists = malloc(vertices * sizeof(NODE *));
    graph->visited = malloc(vertices * sizeof(int));
    for (int i = 0; i < vertices; i++) {
        graph->adjacency_lists[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

void add_edge(GRAPH *graph, int src, int dest) {
    NODE *new_node = create_node(dest);
    new_node->next = graph->adjacency_lists[src];
    graph->adjacency_lists[src] = new_node;

    new_node = create_node(src);
    new_node->next = graph->adjacency_lists[dest];
    graph->adjacency_lists[dest] = new_node;
}

void enqueue(NODE **queue, int data) {
    NODE *new_node = create_node(data);
    if (!*queue) {
        *queue = new_node;
    } else {
        NODE *temp = *queue;
        while (temp->next) temp = temp->next;
        temp->next = new_node;
    }
}

int dequeue(NODE **queue) {
    if (!*queue) return -1;
    NODE *temp = *queue;
    int data = temp->data;
    *queue = (*queue)->next;
    free(temp);
    return data;
}

int is_empty(NODE *queue) {
    return queue == NULL;
}

void DFS(GRAPH *graph, int vertex) {
    NODE *adj_list = graph->adjacency_lists[vertex];
    NODE *temp = adj_list;
    graph->visited[vertex] = 1;
    printf("%d ", vertex);

    while (temp != NULL) {
        int connected_vertex = temp->data;
        if (graph->visited[connected_vertex] == 0) {
            DFS(graph, connected_vertex);
        }
        temp = temp->next;
    }
}

void BFS(GRAPH *graph, int start) {
    NODE *queue = NULL;
    enqueue(&queue, start);
    graph->visited[start] = 1;

    while (!is_empty(queue)) {
        int current = dequeue(&queue);
        printf("%d ", current);
        NODE *temp = graph->adjacency_lists[current];

        while (temp) {
            int adj_vertex = temp->data;
            if (graph->visited[adj_vertex] == 0) {
                graph->visited[adj_vertex] = 1;
                enqueue(&queue, adj_vertex);
            }
            temp = temp->next;
        }
    }
}

int main() {
    int nr_of_vertices, nr_of_edges, starting_vertex;
    printf("Cate noduri are graful? ");
    scanf("%d", &nr_of_vertices);

    printf("Cate muchii are graful? ");
    scanf("%d", &nr_of_edges);

    GRAPH *graph = create_graph(nr_of_vertices);
    printf("Adauga %d muchii \n", nr_of_edges, nr_of_vertices - 1);
    for (int i = 0; i < nr_of_edges; i++) {
        int src, dest;
        scanf("%d %d", &src, &dest);
        add_edge(graph, src, dest);
    }

    printf("De unde plecam in DFS? ");
    scanf("%d", &starting_vertex);
    printf("Parcurgere cu DFS: ");
    DFS(graph, starting_vertex);
    printf("\n");

    for (int i = 0; i < nr_of_vertices; i++) graph->visited[i] = 0;

    printf("De unde plecam in BFS? ");
    scanf("%d", &starting_vertex);
    printf("Parcurgere cu BFS: ");
    BFS(graph, starting_vertex);
    printf("\n");

    return 0;
}
