#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct Graph {
    int vertices;
    int *visited;
    Node **adjacency_lists;
} Graph;

Node *create_node(int v) {
    Node *new_node = malloc(sizeof(Node));
    new_node->data = v;
    new_node->next = NULL;
    return new_node;
}

Graph *create_graph(int vertices) {
    Graph *graph = malloc(sizeof(Graph));
    graph->vertices = vertices;
    graph->adjacency_lists = malloc(vertices * sizeof(Node *));
    graph->visited = malloc(vertices * sizeof(int));

    for (int i = 0; i < vertices; i++) {
        graph->adjacency_lists[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

void add_edge(Graph *graph, int src, int dest) {
    Node *new_node = create_node(dest);
    new_node->next = graph->adjacency_lists[src];
    graph->adjacency_lists[src] = new_node;

    new_node = create_node(src);
    new_node->next = graph->adjacency_lists[dest];
    graph->adjacency_lists[dest] = new_node;
}

void print_graph(Graph *graph) {
    for (int i = 0; i < graph->vertices; i++) {
        printf("Nod %d: ", i);
        Node *temp = graph->adjacency_lists[i];
        while (temp) {
            printf("%d ", temp->data);
            temp = temp->next;
        }
        printf("\n");
    }
}

int is_empty(Node *queue) {
    return queue == NULL;
}

void enqueue(Node **queue, int data) {
    Node *new_node = create_node(data);
    if (is_empty(*queue)) {
        *queue = new_node;
    } else {
        Node *temp = *queue;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

int dequeue(Node **queue) {
    int data = (*queue)->data;
    Node *temp = *queue;
    *queue = (*queue)->next;
    free(temp);
    return data;
}

void DFS(Graph *graph, int vertex) {
    Node *adj_list = graph->adjacency_lists[vertex];
    graph->visited[vertex] = 1;
    printf("%d->", vertex);
    Node *temp = adj_list;
    while (temp != NULL) {
        int connected_vertex = temp->data;
        if (graph->visited[connected_vertex] == 0) {
            DFS(graph, connected_vertex);
        }
        temp = temp->next;
    }
}

void BFS(Graph *graph, int start) {
    Node *queue = NULL;
    graph->visited[start] = 1;
    enqueue(&queue, start);
    while (!is_empty(queue)) {
        int current = dequeue(&queue);
        printf("%d ", current);
        Node *temp = graph->adjacency_lists[current];
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

void wipe_visited_list(Graph *graph) {
    for (int i = 0; i < graph->vertices; i++) {
        graph->visited[i] = 0;
    }
}

int main() {
    int nr_of_vertices;
    int nr_of_edges;
    int starting_vertex;

    printf("Cate noduri vrei sa aiba graful? ");
    scanf("%d", &nr_of_vertices);
    printf("Cate muchii vrei sa aiba graful? ");
    scanf("%d", &nr_of_edges);

    Graph *graph = create_graph(nr_of_vertices);

    printf("Introdu muchiile (de la 0 la %d):\n", nr_of_vertices-1);
    for (int i = 0; i < nr_of_edges; i++) {
        int src, dest;
        scanf("%d %d", &src, &dest);
        add_edge(graph, src, dest);
    }

    printf("Nodul de inceput DFS: ");
    scanf("%d", &starting_vertex);
    printf("DFS traversare: ");
    DFS(graph, starting_vertex);
    printf("\n");

    wipe_visited_list(graph);

    printf("Nodul de inceput BFS: ");
    scanf("%d", &starting_vertex);
    printf("BFS traversare: ");
    BFS(graph, starting_vertex);

    return 0;
}
