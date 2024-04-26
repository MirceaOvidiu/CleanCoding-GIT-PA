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
    struct Node **adj_lists;
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

void DFS(GPH *graph, STK *stack, int v_nr)
{
    push(v_nr, stack);
    NODE *temp = graph->adj_lists[v_nr];

    graph->visited[v_nr] = 1;

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

void insertEdges(GPH *graph, int nr_edg, int nr_v)
{
    int src, dest, i;
    printf("Adauga %d munchii (de la 1 la %d)\n", nr_edg, nr_v);

    for (i = 0; i < nr_edg; i++)
    {
        scanf("%d%d", &src, &dest);
        addEdge(graph, src, dest);
    }
}

void wipe(GPH *graph, int nr_v)
{
    for (int i = 0; i < nr_v; i++)
    {
        graph->visited[i] = 0;
    }
}

void canBeEdge(GPH *graph, int nr_v, STK *stack1, STK *stack2) // 0 sau 1 daca poate fi sau nu ajuns
{
    int *canbe = calloc(nr_v, sizeof(int));

    for (int i = 0; i < nr_v; i++) // aici i tine loc de numar adica de restaurant{for (int j = 0; j < 5; j++)
    {
        for (int j = 0; j < nr_v; j++)
        {
            DFS(graph, stack1, i);
            wipe(graph, nr_v);
            DFS(graph, stack2, j);

            if ((stack1->array[i] == j) && (stack2->array[j] == i))
            {
                canbe[i] = 1;
            }
        }
    }
}

int main()
{

    int nr_v;
    int nr_edg;
    int src, dest;
    int i;
    int vertex1;
    int vertex2;
    int canbe[100];

    printf("Cate noduri are graful?");
    scanf("%d", &nr_v);

    printf("Cate muchii are graful?");
    scanf("%d", &nr_edg);

    printf("Intre ce noduri vreti sa verificati daca exista drum: ");
    scanf("%d%d", &vertex1, &vertex2);

    GPH *graph = createGraph(nr_v);

    STK *stack1 = createStack(2 * nr_v);
    STK *stack2 = createStack(2 * nr_v);

    insertEdges(graph, nr_edg, nr_v);

    canBeEdge(graph, nr_v, stack1, stack2);

    if (canbe[vertex1] == canbe[vertex2] == 1)
    {
        printf("printf exista drum");
    }
    else
        printf("nu exista");
}
