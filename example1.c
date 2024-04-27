// Determinati daca exista sau nu drum direct intre doua restaurante dintr-o retea de tip graf*/

#include <stdlib.h>
#include <stdio.h>

typedef struct Node
{
    int data;
    struct Node *next;
} NODE;
/// pentru simplitate, folosim int uri pt a numi restaurantel/locatiile
/// ex: 1 - restaurantul 1 si tot asa

typedef struct graph
{
    int vertices;
    int *visited;
    NODE **adj_lists;
} GPH;

typedef struct stack
{
    int top;
    int stack_cap; // maxim
    int *array;
} STK;

NODE *createNode(int v)
{
    NODE *new_node = malloc(sizeof(NODE));
    new_node->data = v;
    new_node->next = NULL;
    return new_node;
}

void addEdge(GPH *graph, int src, int dest)
{
    NODE *new_node = createNode(dest);
    new_node->next = graph->adj_lists[src];
    graph->adj_lists[src] = new_node;

    new_node = createNode(src);
    new_node->next = graph->adj_lists[dest];
    graph->adj_lists[dest] = new_node;
}

GPH *createGraph(int v)
{
    int i;
    GPH *graph = malloc(sizeof(GPH));

    graph->vertices = v;
    graph->adj_lists = malloc(v * sizeof(NODE *));
    graph->visited = malloc(v * sizeof(int));

    for (int i = 0; i < v; i++)
    {
        graph->adj_lists[i] = NULL;
        graph->visited[i] = 0;
    }

    return graph;
}

STK *createStack(int stack_cap)
{
    STK *stack = malloc(sizeof(STK));
    stack->array = malloc(stack_cap * sizeof(int));

    stack->top = -1;
    stack->stack_cap = stack_cap;

    return stack;
}

void push(int pushedItem, STK *stack)
{
    stack->top = stack->top + 1;
    stack->array[stack->top] = pushedItem;
}

void DFS(GPH *graph, STK *stack, int vertex_nr)
{
    push(vertex_nr, stack);
    NODE *temp = graph->adj_lists[vertex_nr];

    graph->visited[vertex_nr] = 1;

    while (temp != NULL)
    {
        int connected_vertex = temp->data;

        if (graph->visited[connected_vertex] == 0)
        {
            DFS(graph, stack, connected_vertex);
        }
        temp = temp->next;
    }
}

void insertEdges(GPH *graph, int nr_of_vertices, int nr_of_edges)
{
    int src, dest, i;
    printf("Adauga %d muchii (pentru noduri de la 0 la %d)\n", nr_of_edges, nr_of_vertices - 1);
    for (i = 0; i < nr_of_edges; i++)
    {
        scanf("%d%d", &src, &dest);
        addEdge(graph, src, dest);
    }
}

void wipeVisitedList(GPH *graph, int nr_of_vertices)
{
    for (int i = 0; i < nr_of_vertices; i++)
    {
        graph->visited[i] = 0;
    }
}

void canBeEdge(GPH *graph, int nr_of_vertices, int canbe[100][100])
{
    for (int i = 0; i < nr_of_vertices; i++)
    {
        for (int j = 0; j < nr_of_vertices; j++)
        {
            if (i != j)
            {
                STK *stack1 = createStack(2 * nr_of_vertices);
                STK *stack2 = createStack(2 * nr_of_vertices);

                DFS(graph, stack1, i);
                wipeVisitedList(graph, nr_of_vertices);
                DFS(graph, stack2, j);

                if (graph->visited[i] && graph->visited[j])
                {
                    canbe[i][j] = 1;
                }
                else
                {
                    canbe[i][j] = 0;
                }

                free(stack1);
                free(stack2);
            }
        }
    }
}

int main()
{

    int nr_of_vertices;
    int nr_of_edges;
    int vertex1;
    int vertex2;
    int canbe[100][100];

    printf("Cate noduri are graful?");
    scanf("%d", &nr_of_vertices);

    printf("Cate muchii are graful?");
    scanf("%d", &nr_of_edges);

    GPH *graph = createGraph(nr_of_vertices);

    insertEdges(graph, nr_of_vertices, nr_of_edges);

    printf("Intre ce noduri vreti sa verificati daca exista drum: ");
    scanf("%d%d", &vertex1, &vertex2);

    canBeEdge(graph, nr_of_vertices, canbe);

    if (canbe[vertex1][vertex2] == 1 && canbe[vertex2][vertex1] == 1)
    {
        printf("Exista drum intre restaurantul %d si restaurantul %d.", vertex1, vertex2);
    }
    else
    {
        printf("Nu exista drum intre aceste doua restaurante.");
    }
}
