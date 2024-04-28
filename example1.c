//Determinati daca exista sau nu drum direct intre doua restaurante dintr-o retea de tip graf

#include <stdlib.h>
#include <stdio.h>

typedef struct Node
{
    int data;
    struct Node *next;
}NODE;
/// pentru simplitate, folosim int pt a numi restaurantel/locatiile
/// ex: 1 - restaurantul 1 si tot asa    

typedef struct graph
{
    int nrVertex;
    int *visited;
    struct Node **adjList;
}GPH;

typedef struct stack
{
    int top;
    int capacity;
    int *array;
}STK;


NODE *create_node(int vertex)
{
    NODE *newNode = malloc(sizeof(NODE));
    newNode->data = vertex;
    newNode->next = NULL;
    return newNode;
}

void free_node(NODE *node)
{
    NODE *temp = node, *rez;
    while(temp != NULL)
    {
        rez = temp;
        temp = temp->next;
        free(rez);
    }
}


void add_edge(GPH *graph, int src, int dest)
{
    NODE *newNode = create_node(dest);
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;

    newNode = create_node(src);
    newNode->next = graph->adjList[dest];
    graph->adjList[dest] = newNode;
}

GPH *create_graph(int nrVertex)
{
    int i;
    GPH *graph = malloc(sizeof(GPH));
    graph->nrVertex = nrVertex;
    graph->adjList = malloc(sizeof(NODE) * nrVertex);
    graph->visited = calloc(nrVertex, sizeof(int));
    for (i = 0; i < nrVertex; i ++)
    {
        graph->adjList[i]=NULL;
    }    
    return graph;
}

void free_graph(GPH *graph)
{
    int i;
    for(i = 0; i < graph->nrVertex; i ++)
        free_node(graph->adjList[i]);
    free(graph->adjList);
    free(graph->visited);
    free(graph);
}

STK *create_stack(int capacity)
{
    STK *stack = malloc(sizeof(STK));
    stack->array = malloc(capacity * sizeof(int));
    stack->top = -1;
    stack->capacity = capacity;
    return stack;
}

void free_stack(STK* stack)
{
    free(stack->array);
    free(stack);
}

void push(int value, STK *stack)
{
    if(stack->top == stack->capacity)
    {
        printf("STACK_OVERFLOW!\n");
        exit(11);
    }
    stack->top = stack->top + 1;
    stack->array[stack->top] = value;
}

void DFS(GPH *graph, STK *stack, int start)
{
    NODE *adj_list = graph->adjList[start];
    NODE *aux = adj_list;
    graph->visited[start] = 1;
    push(start, stack);
    while (aux != NULL)
    {
        int conVer = aux->data;
        if (graph->visited[conVer] == 0)
            DFS(graph, stack, conVer);
        aux = aux->next;
    }
}

void insert_edges(GPH *graph, int nrEdges)
{
    int src, dest, i;
    printf("adauga %d munchii (de la 0 la %d)\n", nrEdges, graph->nrVertex - 1);
    for (i = 0; i < nrEdges; i ++)
    {
        scanf("%d %d", &src, &dest);
        add_edge(graph, src, dest);
    }
}

void wipe(GPH *graph)
{
    int i;
    for (i = 0; i < graph->nrVertex; i ++)
    {
        graph->visited[i] = 0;
    }
}    

int path(GPH *graph, STK *stack1, STK *stack2, int vertex1, int vertex2)
{
    DFS(graph, stack1, vertex1); //parcurgem graful în adâncime pornind din vertex1
    int oneWay = graph->visited[vertex2];
    wipe(graph);
    DFS(graph, stack2, vertex2);
    int twoWay = graph->visited[vertex1];
    wipe(graph);

    return oneWay * twoWay;
}

int main()
{
    int nrVertex;
    int nrEdges;
    int src, dest;
    int vortex1, vortex2;
    int i;
    printf("Cate noduri are graful: ");
    scanf("%d", &nrVertex);
    printf("Cate muchii are graful: ");
    scanf("%d", &nrEdges);
    GPH *graph = create_graph(nrVertex);

    STK *stack1 = create_stack(nrVertex);
    STK *stack2 = create_stack(nrVertex);
    
    insert_edges(graph, nrEdges);

    printf("Restaurant ");
    scanf("%d", &vortex1);
    printf("Restaurant ");
    scanf("%d", &vortex2);
    if(path(graph, stack1, stack2, vortex1, vortex2) == 1)
        printf("Exista drum intre restaurante.\n");
    else
        printf("Nu exista drum intre restaurante.\n");

    free_graph(graph);
    free_stack(stack1);
    free_stack(stack2);
    return 0;
}