#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct Graph {
    int vertices;
    int *visited;
    Node **adjacency_list;
} Graph;

typedef struct Stack {
    int top;
    int capacity;
    int *array;
} Stack;

Node *create_node(int value) {
    Node *new_node = malloc(sizeof(Node));
    new_node->data = value;
    new_node->next = NULL;
    return new_node;
}

void add_edge(Graph *graph, int source, int destination) {
    Node *new_node = create_node(destination);
    new_node->next = graph->adjacency_list[source];
    graph->adjacency_list[source] = new_node;

    new_node = create_node(source);
    new_node->next = graph->adjacency_list[destination];
    graph->adjacency_list[destination] = new_node;
}

Graph *create_graph(int vertices) {
    int i;
    Graph *graph = malloc(sizeof(Graph));
    graph->vertices = vertices;
    graph->adjacency_list = malloc(sizeof(Node *) * vertices);
    graph->visited = malloc(sizeof(int) * vertices);

    for (i = 0; i < vertices; i++) {
        graph->adjacency_list[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

Stack *create_stack(int capacity) {
    Stack *stack = malloc(sizeof(Stack));
    stack->array = malloc(capacity * sizeof(int));
    stack->top = -1;
    stack->capacity = capacity;
    return stack;
}

void push(int pushed_element, Stack *stack) {
    stack->top++;
    stack->array[stack->top] = pushed_element;
}

void DFS(Graph *graph, Stack *stack, int vertex_number) {
    Node *adj_list = graph->adjacency_list[vertex_number];
    Node *aux = adj_list;
    graph->visited[vertex_number] = 1;
    printf("%d ", vertex_number);
    push(vertex_number, stack);
    while (aux != NULL) {
        int connected_vertex = aux->data;
        if (graph->visited[connected_vertex] == 0)
            DFS(graph, stack, connected_vertex);
        aux = aux->next;
    }
}

void insert_edges(Graph *graph, int edge_number, int num_vertices) {
    int source, destination, i;
    printf("Adauga %d muchii (de la 0 la %d)\n", edge_number, num_vertices-1);
    for (i = 0; i < edge_number; i++) {
        scanf("%d%d", &source, &destination);
        add_edge(graph, source, destination);
    }
}


void can_reach(Graph *graph, int num_vertices, Stack *stack) {
    int answer = 1;
    DFS(graph, stack, 0);
    for (int i = 0; i < num_vertices; i++) {
        if (graph->visited[i] == 0) {
            answer = 0;
            break;
        }
    }
    printf("\nPoate fi strabatut: %s\n", answer ? "Da" : "Nu");
}

int main() {
    int num_vertices, edge_number;

    printf("Cate noduri are graful ");
    scanf("%d", &num_vertices);

    printf("Cate muchii are graful ");
    scanf("%d", &edge_number);

    Graph *graph = create_graph(num_vertices);
    Stack *stack = create_stack(2 * num_vertices);

    insert_edges(graph, edge_number, num_vertices);
    can_reach(graph, num_vertices, stack);

    return 0;
}
