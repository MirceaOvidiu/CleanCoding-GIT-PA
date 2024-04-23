#include <stdio.h>
#include <stdlib.h>

// Define a node structure for adjacency list
typedef struct Node {
    int data;
    struct Node *next;
} Node;

// Define a graph structure
typedef struct Graph {
    int vertices;
    int *visited;
    Node **adjacency_lists;
} Graph;

// Function prototypes
Node *create_node(int v);
Graph *create_graph(int vertices);
void add_edge(Graph *graph, int src, int dest);
void input_edges(int nr_of_vertices, int nr_of_edges, Graph *graph);
int is_empty(Node *queue);
void enqueue(Node **queue, int data);
int dequeue(Node **queue);
void print_graph(Graph *graph);
void print_queue(Node *queue);
void reset_visited(Graph *graph, int nr_of_vertices);
void DFS(Graph *graph, int vertex);
void BFS(Graph *graph, int start);

// Function to create a new node
Node *create_node(int v) {
    Node *new_node = malloc(sizeof(Node));
    new_node->data = v;
    new_node->next = NULL;
    return new_node;
}

// Function to create a graph with given number of vertices
Graph *create_graph(int vertices) {
    int i;
    Graph *graph = malloc(sizeof(Graph));
    graph->vertices = vertices;
    graph->adjacency_lists = malloc(vertices * sizeof(Node *));
    graph->visited = malloc(sizeof(int) * vertices);

    for (i = 0; i < vertices; i++) {
        graph->adjacency_lists[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

// Function to add an edge to the graph
void add_edge(Graph *graph, int src, int dest) {
    Node *new_node = create_node(dest);
    new_node->next = graph->adjacency_lists[src];
    graph->adjacency_lists[src] = new_node;

    new_node = create_node(src);
    new_node->next = graph->adjacency_lists[dest];
    graph->adjacency_lists[dest] = new_node;
}

// Function to input edges of the graph
void input_edges(int nr_of_vertices, int nr_of_edges, Graph *graph) {
    int src, dest, i;
    printf("Add %d edges (from 1 to %d)\n", nr_of_edges, nr_of_vertices);
    for (i = 0; i < nr_of_edges; i++) {
        scanf("%d %d", &src, &dest);
        add_edge(graph, src, dest);
    }
}

// Function to check if the queue is empty
int is_empty(Node *queue) {
    return queue == NULL;
}

// Function to add an element to the queue
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

// Function to remove an element from the queue
int dequeue(Node **queue) {
    int data = (*queue)->data;
    Node *temp = *queue;
    *queue = (*queue)->next;
    free(temp);
    return data;
}

// Function to print the graph
void print_graph(Graph *graph) {
    int i;
    for (i = 0; i < graph->vertices; i++) {
        printf("Vertex %d: ", i);
        Node *temp = graph->adjacency_lists[i];
        while (temp) {
            printf("%d ", temp->data);
            temp = temp->next;
        }
        printf("\n");
    }
}

// Function to reset visited list
void reset_visited(Graph *graph, int nr_of_vertices) {
    for (int i = 0; i < nr_of_vertices; i++) {
        graph->visited[i] = 0;
    }
}

// Depth First Search
void DFS(Graph *graph, int vertex) {
    graph->visited[vertex] = 1;
    printf("%d -> ", vertex);

    Node *temp = graph->adjacency_lists[vertex];
    while (temp != NULL) {
        int connected_vertex = temp->data;
        if (graph->visited[connected_vertex] == 0) {
            DFS(graph, connected_vertex);
        }
        temp = temp->next;
    }
}

// Breadth First Search
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

int main() {
    int nr_of_vertices, nr_of_edges, starting_vertex;

    printf("How many vertices does the graph have? ");
    scanf("%d", &nr_of_vertices);

    printf("How many edges does the graph have? ");
    scanf("%d", &nr_of_edges);

    Graph *graph = create_graph(nr_of_vertices);
    input_edges(nr_of_vertices, nr_of_edges, graph);

    printf("Where to start DFS? ");
    scanf("%d", &starting_vertex);
    printf("DFS traversal: ");
    DFS(graph, starting_vertex);
    reset_visited(graph, nr_of_vertices);
    printf("\n");

    printf("Where to start BFS? ");
    scanf("%d", &starting_vertex);
    printf("BFS traversal: ");
    BFS(graph, starting_vertex);

    return 0;
}
