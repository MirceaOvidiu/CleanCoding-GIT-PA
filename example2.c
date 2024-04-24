/*parcurgerge  graf cu DFS/BFS*/

//Imi cer scuze in avans

#include <stdlib.h>
#include <stdio.h>

// Structura unui nod din graf
typedef struct Node {
    int data;
    struct Node *next;
} Node;

// Structura pentru graf
typedef struct Graph {
    int vertices;
    int *visited;
    Node **adjacency_lists;
} Graph;

// Creare nod
Node *create_node(int v) {
    Node *new_node = malloc(sizeof(Node));
    new_node->data = v;
    new_node->next = NULL;
    return new_node;
}

// Creare graf
Graph *create_graph(int vertices) {
    Graph *graph = malloc(sizeof(Graph));
    graph->vertices = vertices;
    graph->adjacency_lists = malloc(vertices * sizeof(Node *));
    graph->visited = malloc(sizeof(int) * vertices);

    for (int i = 0; i < vertices; i++) {
        graph->adjacency_lists[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

// Adaugare muchie intre doua noduri
void add_edge(Graph *graph, int src, int dest) {
    Node *new_node = create_node(dest);
    new_node->next = graph->adjacency_lists[src];
    graph->adjacency_lists[src] = new_node;

    new_node = create_node(src);
    new_node->next = graph->adjacency_lists[dest];
    graph->adjacency_lists[dest] = new_node;
}

// Citire muchii
void input_edges(int nr_of_vertices, int nr_of_edges, Graph *graph) {
    int src, dest;
    printf("Adauga %d muchii (de la 1 la %d)\n", nr_of_edges, nr_of_vertices);
    for (int i = 0; i < nr_of_edges; i++) {
        scanf("%d%d", &src, &dest);
        add_edge(graph, src, dest);
    }
}

// Verifica daca coada este goala
int is_empty(Node *queue) {
    return queue == NULL;
}

// Adauga in coada
void enqueue(Node **queue, int data) {
    Node *new_node = create_node(data);
    if (is_empty(*queue))
        *queue = new_node;
    else {
        Node *temp = *queue;
        while (temp->next)
            temp = temp->next;
        temp->next = new_node;
    }
}

// Sterge din coada
int dequeue(Node **queue) {
    int data = (*queue)->data;
    Node *temp = *queue;
    *queue = (*queue)->next;
    free(temp);
    return data;
}

// Afiseaza graful
void print_graph(Graph *graph) {
    for (int i = 0; i < graph->vertices; i++) {
        Node *temp = graph->adjacency_lists[i];
        printf("Node %d: ", i);
        while (temp != NULL) {
            printf("%d -> ", temp->data);
            temp = temp->next;
        }
        printf("NULL\n");
    }

void print_queue(Node *queue){
while (queue != NULL){
  printf("%d ", queue->data);
  queue = *(queue->next)->next;
}
}


void wipe_visited_list(Graph *graph, int nr_of_vertices){
for (int i = 0; 
i < nr_of_vertices;i++){
  graph->visited[i] = 0;
  }
}

// Parcurgere in adancime (DFS)
void DFS(Graph *graph, int vertex) {
    Node *adj_list = graph->adjacency_lists[vertex];
    graph->visited[vertex] = 1;
    printf("%d -> ", vertex);

    while (adj_list != NULL) {
        int connected_vertex = adj_list->data;
        if (graph->visited[connected_vertex] == 0) {
            DFS(graph, connected_vertex);
        }
        adj_list = adj_list->next;
    }
}

// Parcurgere in latime (BFS)
void BFS(Graph *graph, int start) {
    Node *queue = NULL;
    graph->visited[start] = 1;
    enqueue(&queue, start);

    while (!is_empty(queue)) {
        int current = dequeue(&queue);
        printf("%d -> ", current);

        Node *adj_list = graph->adjacency_lists[current];
        while (adj_list != NULL) {
            int adj_vertex = adj_list->data;
            if (graph->visited[adj_vertex] == 0) {
                graph->visited[adj_vertex] = 1;
                enqueue(&queue, adj_vertex);
            }
            adj_list = adj_list->next;
        }
    }
}

int main() {
    int nr_of_vertices, nr_of_edges, starting_vertex;
    printf("Cate noduri are graful? ");
    scanf("%d", &nr_of_vertices);
    printf("Cate muchii are graful? ");
    scanf("%d", &nr_of_edges);

    Graph *graph = create_graph(nr_of_vertices);
    input_edges(nr_of_vertices, nr_of_edges, graph);

    printf("De unde pornim in DFS? ");
    scanf("%d", &starting_vertex);
    printf("Parcurgere DFS: ");
    DFS(graph, starting_vertex);
    reset_visited(graph);

    printf("\nDe unde pornim in BFS? ");
    scanf("%d", &starting_vertex);
    printf("Parcurgere BFS: ");
    BFS(graph, starting_vertex);

    return 0;
}
