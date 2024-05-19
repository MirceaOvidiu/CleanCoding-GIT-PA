#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} NODE;

typedef struct Graph {
    int vertices;
    int *visited;
    struct Node **adjacency_lists;
} GRAPH;

// Crează un nod nou
NODE *create_node(int v) {
    NODE *new_node = (NODE *)malloc(sizeof(NODE));
    new_node->data = v;
    new_node->next = NULL;
    return new_node;
}

// Crează un graf cu un număr dat de vârfuri
GRAPH *create_graph(int vertices) {
    GRAPH *graph = (GRAPH *)malloc(sizeof(GRAPH));
    graph->vertices = vertices;
    graph->adjacency_lists = (NODE **)malloc(vertices * sizeof(NODE *));
    graph->visited = (int *)malloc(vertices * sizeof(int));

    for (int i = 0; i < vertices; i++) {
        graph->adjacency_lists[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

// Adaugă o muchie între două vârfuri
void add_edge(GRAPH *graph, int src, int dest) {
    // Adaugă muchia de la src la dest
    NODE *new_node = create_node(dest);
    new_node->next = graph->adjacency_lists[src];
    graph->adjacency_lists[src] = new_node;

    // Adaugă muchia de la dest la src (graf neorientat)
    new_node = create_node(src);
    new_node->next = graph->adjacency_lists[dest];
    graph->adjacency_lists[dest] = new_node;
}

// Inserează muchiile în graf
void insert_edges(int nr_of_vertices, int nr_of_edges, GRAPH *graph) {
    int src, dest;
    printf("Adăugați %d muchii (de la 0 la %d)\n", nr_of_edges, nr_of_vertices - 1);
    for (int i = 0; i < nr_of_edges; i++) {
        scanf("%d%d", &src, &dest);
        add_edge(graph, src, dest);
    }
}

// Verifică dacă coada este goală
int is_empty(NODE *queue) {
    return queue == NULL;
}

// Adaugă un nod în coadă
void enqueue(NODE **queue, int data) {
    NODE *new_node = create_node(data);
    if (is_empty(*queue)) {
        *queue = new_node;
    } else {
        NODE *temp = *queue;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

// Scoate un nod din coadă
int dequeue(NODE **queue) {
    if (is_empty(*queue)) {
        return -1;
    }
    int data = (*queue)->data;
    NODE *temp = *queue;
    *queue = (*queue)->next;
    free(temp);
    return data;
}

// Afișează graful
void print_graph(GRAPH *graph) {
    for (int i = 0; i < graph->vertices; i++) {
        NODE *temp = graph->adjacency_lists[i];
        printf("Lista de adiacență a vârfului %d: ", i);
        while (temp) {
            printf("%d -> ", temp->data);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

// Resetează lista de vizite
void wipe_visited_list(GRAPH *graph) {
    for (int i = 0; i < graph->vertices; i++) {
        graph->visited[i] = 0;
    }
}

// Parcurgere DFS
void DFS(GRAPH *graph, int vertex) {
    NODE *adj_list = graph->adjacency_lists[vertex];
    NODE *temp = adj_list;

    graph->visited[vertex] = 1;
    printf("%d -> ", vertex);

    while (temp != NULL) {
        int connected_vertex = temp->data;
        if (graph->visited[connected_vertex] == 0) {
            DFS(graph, connected_vertex);
        }
        temp = temp->next;
    }
}

// Parcurgere BFS
void BFS(GRAPH *graph, int start_vertex) {
    NODE *queue = NULL;

    graph->visited[start_vertex] = 1;
    enqueue(&queue, start_vertex);

    while (!is_empty(queue)) {
        int current_vertex = dequeue(&queue);
        printf("%d -> ", current_vertex);

        NODE *temp = graph->adjacency_lists[current_vertex];
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
    int nr_of_vertices;
    int nr_of_edges;
    int starting_vertex;

    printf("Câte noduri are graful? ");
    scanf("%d", &nr_of_vertices);
    printf("Câte muchii are graful? ");
    scanf("%d", &nr_of_edges);

    GRAPH *graph = create_graph(nr_of_vertices);
    insert_edges(nr_of_vertices, nr_of_edges, graph);

    printf("De unde începem parcurgerea DFS? ");
    scanf("%d", &starting_vertex);
    printf("Parcurgere cu DFS: ");
    DFS(graph, starting_vertex);
    printf("\n");

    wipe_visited_list(graph);

    printf("De unde începem parcurgerea BFS? ");
    scanf("%d", &starting_vertex);
    printf("Parcurgere cu BFS: ");
    BFS(graph, starting_vertex);
    printf("\n");

    return 0;
}
