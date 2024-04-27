/*Determinati daca exista sau nu drum direct intre doua restaurante dintr-o retea de tip graf*/
// I might have forgiven you but God didn't he saw you what you did lil bro

// pentru simplitate, folosim int uri pt a numi restaurantele/locatiile
//  ex: 1 - restaurantul 1 si tot asa

#include <stdlib.h>
#include <stdio.h>

typedef struct Node
{
    int data;
    struct Node *next;
} NODE;

typedef struct Graph
{
    int vertices;
    int *visited;
    struct Node **adjacency_lists;
} GRAPH;

typedef struct Stack
{
    int top;
    int capacity;
    int *elements;
} STACK;

NODE *create_node(int vertex)
{
    NODE *new_node = malloc(sizeof(NODE));
    new_node->data = vertex;
    new_node->next = NULL;
    return new_node;
}

GRAPH *create_graph(int vertices)
{
    GRAPH *graph = malloc(sizeof(GRAPH));
    graph->vertices = vertices;
    graph->adjacency_lists = malloc(vertices * sizeof(NODE *));
    graph->visited = malloc(vertices * sizeof(int));

    for (int i = 0; i < vertices; i++)
    {
        graph->adjacency_lists[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

void add_edge(GRAPH *graph, int source, int destination)
{
    NODE *new_node = create_node(destination);
    new_node->next = graph->adjacency_lists[source];
    graph->adjacency_lists[source] = new_node;

    new_node = create_node(source);
    new_node->next = graph->adjacency_lists[destination];
    graph->adjacency_lists[destination] = new_node;
}

void insert_edge(int nr_of_edges, GRAPH *graph)
{
    int source, destination;
    printf("Adauga %d muchii:\n", nr_of_edges);
    for (int i = 0; i < nr_of_edges; i++)
    {
        scanf("%d %d", &source, &destination);
        add_edge(graph, source, destination);
    }
    printf("\n");
}

STACK *create_stack(int capacity)
{
    STACK *stack = malloc(sizeof(STACK));
    stack->elements = malloc(capacity * sizeof(int));
    stack->top = -1; // Initializeaza topul cu -1, deoarece stiva este goala initial
    stack->capacity = capacity;

    return stack;
}

void push(int pushed, STACK *stack)
{
    stack->top = stack->top + 1;
    stack->elements[stack->top] = pushed;
}

void wipe_visited_list(GRAPH *graph)
{
    for (int i = 0; i < graph->vertices; i++)
        graph->visited[i] = 0;
}

void DFS(GRAPH *graph, int vertex_nr)
{
    NODE *adj_list = graph->adjacency_lists[vertex_nr];
    NODE *temp = adj_list;

    graph->visited[vertex_nr] = 1;
    printf("%d->", vertex_nr);

    while (temp != NULL)
    {
        int connected_vertex = temp->data;

        if (graph->visited[connected_vertex] == 0)
            DFS(graph, connected_vertex);
        temp = temp->next;
    }
}

void IsPath(GRAPH *graph, int num_vertices, STACK *s1, STACK *s2)
{
    int *possible_paths = calloc(num_vertices, sizeof(int));

    for (int i = 0; i < num_vertices; i++)
    {
        wipe_visited_list(graph);
        DFS(graph, i);
        printf("\n");
        for (int k = 0; k < num_vertices; k++)
        {
            if ((s1->elements[k] != i) && (graph->visited[s1->elements[k]] == 1) &&
                (s2->elements[s1->elements[k]] == s2->elements[i]))
            {
                possible_paths[i] = 1;
                break;
            }
        }
    }

    int path_exists = 0;
    for (int i = 0; i < num_vertices; i++)
    {
        if (possible_paths[i] == 1)
        {
            path_exists = 1;
            break;
        }
    }

    if (path_exists)
        printf("\nExista cel putin un drum intre nodurile din cele doua stive.\n");
    else
        printf("Nu exista niciun drum intre nodurile din cele doua stive.\n");

    free(possible_paths);
}

int main()
{

    int number_of_vertices;
    int number_of_edges;
    int source;
    int destination;

    printf("cate noduri are girafa? ");
    scanf("%d", &number_of_vertices);

    printf("cate muchii are giraful? ");
    scanf("%d", &number_of_edges);

    GRAPH *graph = create_graph(number_of_vertices);

    STACK *s1 = create_stack(2 * number_of_vertices);
    STACK *s2 = create_stack(2 * number_of_vertices);

    insert_edge(number_of_edges, graph);
    IsPath(graph, number_of_vertices, s1, s2);

    return 0;
}
