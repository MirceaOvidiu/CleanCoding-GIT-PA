#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct Graph {
    int vertices;
    int *visited;
    Node **adjacency_lists;
} Graph;

Node* create_node(int v) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = v;
    new_node->next = NULL;
    return new_node;
}

Graph* create_graph(int vertices) {
    int i;
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->vertices = vertices;
    graph->adjacency_lists = (Node**)malloc(vertices * sizeof(Node*));
    graph->visited = (int*)malloc(vertices * sizeof(int));

    for (i = 0; i < vertices; i++) {
        graph->adjacency_lists[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

void add_edge(Graph* graph, int src, int dest) {
    Node* new_node = create_node(dest);
    new_node->next = graph->adjacency_lists[src];
    graph->adjacency_lists[src] = new_node;

    new_node = create_node(src);
    new_node->next = graph->adjacency_lists[dest];
    graph->adjacency_lists[dest] = new_node;
}

void insert_edges(int nr_of_vertices, int nr_of_edges, Graph* graph) {
    int src, dest, i;
    printf("Adauga %d muchii (de la 1 la %d):\n", nr_of_edges, nr_of_vertices);
    for (i = 0; i < nr_of_edges; i++) {
        scanf("%d%d", &src, &dest);
        add_edge(graph, src, dest);
    }
}

int is_empty(Node* queue) {
    return queue == NULL;
}

void enqueue(Node** queue, int data) {
    Node* new_node = create_node(data);
    if (is_empty(*queue))
        *queue = new_node;
    else {
        Node* temp = *queue;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

int dequeue(Node** queue) {
    int data = (*queue)->data;
    Node* temp = *queue;
    *queue = (*queue)->next;
    free(temp);
    return data;
}

void print_graph(Graph* graph) {
    int i;
    for (i = 0; i < graph->vertices; i++) {
        printf("%d: ", i);
        Node* temp = graph->adjacency_lists[i];
        while (temp != NULL) {
            printf("%d ", temp->data);
            temp = temp->next;
        }
        printf("\n");
    }
}

void wipe_visited_list(Graph* graph) {
    int i;
    for (i = 0; i < graph->vertices; i++) {
        graph->visited[i] = 0;
    }
}

void DFS(Graph* graph, int vertex_nr) {
    graph->visited[vertex_nr] = 1;
    printf("%d->", vertex_nr);

    Node* temp = graph->adjacency_lists[vertex_nr];
    while (temp != NULL) {
        int connected_vertex = temp->data;
        if (graph->visited[connected_vertex] == 0) {
            DFS(graph, connected_vertex);
        }
        temp = temp->next;
    }
}

void BFS(Graph* graph, int start) {
    Node* queue = NULL;
    graph->visited[start] = 1;
    enqueue(&queue, start);

    while (!is_empty(queue)) {
        int current = dequeue(&queue);
        printf("%d ", current);

        Node* temp = graph->adjacency_lists[current];
        while (temp != NULL) {
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
    int nr_of_vertices;
    int nr_of_edges;
    int starting_vertex;

    printf("Cate noduri are graful? ");
    scanf("%d", &nr_of_vertices);

    printf("Cate muchii are graful? ");
    scanf("%d", &nr_of_edges);

    Graph* graph = create_graph(nr_of_vertices);
    insert_edges(nr_of_vertices, nr_of_edges, graph);

    printf("De unde plecam in DFS? ");
    scanf("%d", &starting_vertex);
    printf("Parcurgere cu DFS: ");
    DFS(graph, starting_vertex);
    wipe_visited_list(graph);
    printf("\n");

    printf("De unde plecam in BFS? ");
    scanf("%d", &starting_vertex);
    printf("Parcurgere cu BFS: ");
    BFS(graph, starting_vertex);

    return 0;
}
