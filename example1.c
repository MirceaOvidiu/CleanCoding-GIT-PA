/*Determinati daca exista sau nu drum direct intre doua restaurante dintr-o retea de tip graf*/

#include <stdlib.h>
#include <stdio.h>

typedef struct Node
{
    int data;
    struct Node *next;
}
/// pentru simplitate, folosim int uri pt a numi restaurantel/locatiile
/// ex: 1 - restaurantul 1 si tot asa

Node;

typedef struct Graph
{
    int vertexCount;
    int *visited;
    struct Node **adjacencyList;
} Graph;

typedef struct Stack
{
    int top;
    int capacity;
    int *array;
} Stack;

Node *createNode(int vertex)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = vertex;
    newNode->next = NULL;
    return newNode;
}

void addEdge(Graph *graph, int source, int destination)
{
    if (source >= graph->vertexCount || destination >= graph->vertexCount)
    {
        printf("Error: Vertex does not exist\n");
        return;
    }

    Node *newNode = createNode(destination);
    newNode->next = graph->adjacencyList[source];
    graph->adjacencyList[source] = newNode;

    newNode = createNode(source);
    newNode->next = graph->adjacencyList[destination];
    graph->adjacencyList[destination] = newNode;
}

Graph *createGraph(int vertexCount)
{
    int i;
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->vertexCount = vertexCount;
    graph->adjacencyList = (Node **)malloc(sizeof(Node *) * vertexCount);
    graph->visited = (int *)malloc(sizeof(int) * vertexCount);

    for (int i = 0; i < vertexCount; i++)
    {
        graph->adjacencyList[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

Stack *createStack(int capacity)
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->array = (int *)malloc(capacity * sizeof(int));
    stack->top = -1;
    stack->capacity = capacity;

    return stack;
}

void push(int pushedElement, Stack *stack)
{
    stack->top = stack->top + 1;
    stack->array[stack->top] = pushedElement;
}

void DFS(Graph *graph, Stack *stack, int vertexNumber, int vertexCount)
{
    if (vertexNumber >= vertexCount)
    {
        printf("Error: Vertex does not exist\n");
        return;
    }

    Node *adjacencyList = graph->adjacencyList[vertexNumber];
    Node *temp = adjacencyList;

    graph->visited[vertexNumber] = 1;
    printf("%d ", vertexNumber);
    push(vertexNumber, stack);

    while (temp != NULL)
    {
        int connectedVertex = temp->data;

        if (connectedVertex >= vertexCount)
        {
            printf("Error: Connected vertex does not exist\n");
            temp = temp->next;
            continue;
        }

        if (graph->visited[connectedVertex] == 0)
        {
            DFS(graph, stack, connectedVertex, vertexCount);
        }

        temp = temp->next;
    }
}

void insertEdges(Graph *graph, int edgeCount, int vertexCount)
{
    int source, destination, i;
    printf("Adauga %d munchii (de la 0 la %d). In formatul source destination\n", edgeCount, vertexCount-1);
    for (i = 0; i < edgeCount; i++)
    {
        scanf("%d%d", &source, &destination);
        if (source >= vertexCount || destination >= vertexCount)
        {
            printf("Error: Vertex does not exist\n");
            i--; // decrement i to retry this iteration
            continue;
        }
        addEdge(graph, source, destination);
    }
}

void resetVisited(Graph *graph, int vertexCount)
{
    for (int i = 0; i < vertexCount; i++)
    {
        graph->visited[i] = 0;
    }
}
void checkReachability(Graph *graph, int vertexCount, Stack *stack1, Stack *stack2)
{
    int *isReachable = (int *)calloc(vertexCount, sizeof(int));
    for (int i = 0; i < vertexCount; i++)
    {
        printf("\nThe DFS for the node %d is: ", i);
        DFS(graph, stack1, i, vertexCount);
        for (int j = 0; j < vertexCount; j++)
        {
            int foundPath = 0;
            for (int k = 0; k <= stack1->top && !foundPath; k++)
            {
                if (stack1->array[k] == j && i != j) 
                {
                    isReachable[i] = 1; 
                    foundPath = 1;
                }
            }
        }
        resetVisited(graph, vertexCount);
    }
    for (int i = 0; i < vertexCount; i++)
    {
        printf("Reachability for vertex %d: %d\n", i, isReachable[i]);
    }
    free(isReachable);
}
int main()
{

    int vertexCount;
    int edgeCount;
    int source, destination;
    int i;
    int vortex_1;
    int virtex_2;
    int foundPath;

    printf("Cate Noduri are Graful?   ");
    scanf("%d", &vertexCount);

    printf("Cate Muchii are Graful?   ");
    scanf("%d", &edgeCount);

    Graph *graph = createGraph(vertexCount);

    Stack *stack1 = createStack(2 * vertexCount);

    insertEdges(graph, edgeCount, vertexCount);
    Stack *stack2 = createStack(edgeCount);
    printf("\n");
    checkReachability(graph, vertexCount, stack1, stack2);
    return 0;
}