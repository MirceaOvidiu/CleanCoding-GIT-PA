///Determinati daca exista sau nu drum direct intre doua restaurante dintr-o retea de tip graf
#include <stdlib.h>
#include <stdio.h>

typedef struct Node
{
    int data;
    struct Node *next;

}NODE;
/// pentru simplitate, folosim int uri pt a numi restaurantele/locatiile
/// ex: 1 - restaurantul 1 si tot asa


typedef struct Graph
{
    int nr_edges;
    int *visited;
    struct Node **adjacency_list;

}Graph;

typedef struct Stack
{
    int top;
    int capacity;
    int *array;

} Stack;

NODE *createNode(int nr_edges)
{
    NODE *new_node = malloc(sizeof(NODE));
    new_node->data = nr_edges;
    new_node->next = NULL;
    return new_node;
}

void addEdge(Graph *graph,int source,int destination)
{
    NODE *new_node = createNode(destination);
    new_node->next = graph->adjacency_list[source];
    graph->adjacency_list[source] = new_node;

    new_node = createNode(source);
    new_node->next = graph->adjacency_list[destination];
    graph->adjacency_list[destination] = new_node;
}

Stack *createStack(int capacity)
{
    Stack *stack = malloc(sizeof(Stack));
    stack->array = malloc(capacity * sizeof(int));
    stack->top = -1;
    stack->capacity = capacity;

    return stack;
}

void push(Stack *stack, int data)
{
    stack->top = stack->top + 1;
    stack->array[stack->top] = data;
}

int existPath(Graph *graph, int source, int destination)
{
    if (source < 1 || source > graph->nr_edges || destination < 1 || destination > graph->nr_edges) {

        printf("Noduri invalide.\n");
        return 0;
    }

    int i;
    int *visited = malloc(sizeof(int) * graph->nr_edges);
    for ( i = 1; i < graph->nr_edges; i++ ) {
        visited[i] = 0;
    }

    Stack *stack = createStack(graph->nr_edges + 1);
    push(stack, source);

    while (stack->top != -1)
        {
            int current = stack->array[stack->top];
            stack->top--;

            if (current == destination)
                {
                    free(visited);
                    return 1;
                }

            if (!visited[current])
                {
                    visited[current] = 1;
                    NODE *adj_list = graph->adjacency_list[current];
                    NODE *current_node = adj_list;

                    while (current_node != NULL)
                        {
                            if (!visited[current_node->data])
                                {
                                    push(stack, current_node->data);
                                }

                               current_node = current_node->next;
                        }
                }
        }

    return 0;
}
int main()
{
    Graph *graph = malloc(sizeof(Graph));
    graph->nr_edges = 5;
    graph->adjacency_list = malloc((graph->nr_edges + 1) * sizeof(NODE *));
    graph->visited = malloc((graph->nr_edges + 1) * sizeof(int));

    int i;
    for ( i = 1; i <= graph->nr_edges; i++ )
        {
            graph->adjacency_list[i] = NULL;
            graph->visited[i] = 0;
        }

    addEdge(graph, 1, 2);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 4);
    addEdge(graph, 4, 5);

    int source = 1, dest = 2;
    if (existPath(graph, source, dest)) {
        printf("Exista un drum direct");
    } else {
        printf("Nu exista un drum direct");
    }

    return 0;
}