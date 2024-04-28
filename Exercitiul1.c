#include <stdlib.h>
#include <stdio.h>


/// STRUCTURI

// Structura nod
typedef struct Node
{
    int data;
    struct Node *next;
} NODE;

// Structura graf
typedef struct Graph
{
    int numNodes;
    int *visited;
    NODE **adjacencyList;
} GRAPH;

// Structura stiva
typedef struct Stack
{
    int top;
    int stackCapacity;
    int *array;
} STACK;


/// FUNCTII

// Creare graf prin transmiterea numarului de noduri
GRAPH *createGraph(int numNodes)
{
    int i;

    GRAPH *graph = (GRAPH *)malloc(sizeof(GRAPH));
    graph->numNodes = numNodes;
    graph->adjacencyList = (NODE **)malloc(numNodes * sizeof(NODE*));
    graph->visited = (int *)malloc(numNodes * sizeof(int));

    for (i = 0; i < numNodes; i++)
    {
        graph->adjacencyList[i] = NULL;
        graph->visited[i] = 0;
    }

    return graph;
}

// Creare nod prin transmiterea valorii sale
NODE *createNode(int data)
{
    NODE *newNode = (NODE *)malloc(sizeof(NODE));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Adaugare muchie in graf prin transmiterea capetelor muchiei (sursa - destinatie)
void addEdge(GRAPH *graph, int src, int dest)
{
    // Adaugam muchia de la destinatie la sursa
    NODE *newNode = createNode(dest);
    newNode->next = graph->adjacencyList[src];
    graph->adjacencyList[src] = newNode;

    // Adaugam muchia de la sursa la destinatie (fiind graf neorientat)
    newNode = createNode(src);
    newNode->next = graph->adjacencyList[dest];
    graph->adjacencyList[dest] = newNode;
}

// Adaugare muchii in graf prin transmiterea numarului de muchii
void insertEdges(GRAPH *graph, int edgeNum)
{
    int src, dest, i;

    printf("\nAdauga %d drumuri (de la 1 la %d)\n", edgeNum, graph->numNodes);

    // Citirea de la tastatura a muchiilor
    for (i = 0; i < edgeNum; i++)
    {
        do
        {
            printf("Drumul %d:", i + 1);
            scanf("%d %d", &src, &dest);

            // Asiguram crearea de muchie (drum) intre doua noduri (restaurante) valide
            if (src < 1 || src > graph->numNodes || dest < 1 || dest > graph->numNodes || src == dest)
            {
                printf("Restaurante invalide! Introduceti restaurante valide (intre %d si %d).\n", 1, graph->numNodes);
            }

        } while (src < 1 || src > graph->numNodes || dest < 1 || dest > graph->numNodes || src == dest);

        addEdge(graph, src - 1, dest - 1);
    }
}

// Creare stiva prin trasmiterea capacitatii acesteia
STACK *createStack(int stackCapacity)
{
    STACK *stack = (STACK *)malloc(sizeof(STACK));

    stack->array = (int *)malloc(stackCapacity * sizeof(int));
    stack->top = -1;
    stack->stackCapacity = stackCapacity;

    return stack;
}

// Adaugare element in stiva prin transmiterea valorii adaugate
void push(STACK *stack, int data)
{
    stack->top = stack->top + 1;
    stack->array[stack->top] = data;
}

// Extragere element din stiva si returnarea acestuia
int pop(STACK *stack)
{
    return stack->array[stack->top--];
}

// Parcurgere in adancime graf prin transmiterea sursei (nod de inceput)
void DFS(GRAPH *graph, STACK *stack, int src)
{
    NODE *adjacencyList = graph->adjacencyList[src];
    NODE *aux = adjacencyList;

    graph->visited[src] = 1;
    push(stack, src);

    while (aux != NULL)
    {
        int neighbor = aux->data;

        if (graph->visited[neighbor] == 0)
            DFS(graph, stack, neighbor);

        aux = aux->next;
    }
}

// Resetarea vectorului visited
void wipe(GRAPH *graph)
{
    for (int i = 0; i < graph->numNodes; i++)
    {
        graph->visited[i] = 0;
    }
}

// Functie care verifica existenta unui drum intre doua noduri date
// Stiu ca in codul original scria ca se doreste cautarea unui drum direct intre doua restaurante,
// dar asa iese problema direct din lista de adiacenta, deci am zis sa fac asa :))
int canBeReached(GRAPH *graph, int src, int dest)
{
    STACK *stack = createStack(graph->numNodes);

    wipe(graph);
    DFS(graph, stack, src);

    while (stack->top != -1)
    {
        if (pop(stack) == dest)
        {
            return 1;
        }
    }

    return 0;
}


/// ELIBERARE MEMORIE GRAF

void freeGraph(GRAPH* graph)
{
    for (int i = 0; i < graph->numNodes; i++)
    {
        NODE *current = graph->adjacencyList[i];

        while (current != NULL)
        {
            NODE *temp = current;
            current = current->next;

            free(temp);
        }
    }

    free(graph->adjacencyList);
    free(graph->visited);
    free(graph);
}


/// MAIN

int main()
{
    int numNodes, numEdges;

    do
    {
        printf("\nIntroduceti numarul de restaurante (intre 2 si 100):");
        scanf("%d", &numNodes);

        if (numNodes < 2 || numNodes > 100)
        {
            printf("Numarul de restaurante trebuie sa fie intre 2 si 100!\n");
        }
    } while (numNodes < 2 || numNodes > 100);

    // Cream graful
    GRAPH* graph = createGraph(numNodes);

    // Calculam numarul maxim de muchii pentru un graf complet
    // Folosim asta pentru a asigura o citire corecta a numarului de muchii
    int maxEdges = (numNodes * (numNodes - 1)) / 2;

    // Asiguram initializarea cu un numar posibil de muchii
    do
    {
        printf("Introduceti numarul de drumuri dintre restaurante (intre 1 si %d):", maxEdges);
        scanf("%d", &numEdges);

        if (numEdges < 1 || numEdges > maxEdges)
        {
            printf("Numarul de drumuri trebuie sa fie intre 1 si %d!\n", maxEdges);
        }
    } while (numEdges < 1 || numEdges > maxEdges);

    // Adaugam muchiile (drumurile) in graf
    insertEdges(graph, numEdges);

    int src, dest;
    do
    {
        printf("\nIntroduceti doua restaurante intre care vreti sa gasiti drum:");
        scanf("%d %d", &src, &dest);

        // Asiguram cautarea de drum intre doua noduri (restaurante) valide
        if (src < 1 || src > numNodes || dest < 1 || dest > numNodes)
        {
            printf("Restaurante invalide! Introduceti restaurante valide (intre %d si %d).\n", 1, numNodes);
        }

        if (src == dest)
        {
            printf("\nDa, poti ajunge din acelasi restaurant in acelasi restaurant! Foarte bine!\n");

            return 0;
        }
    } while (src < 1 || src > numNodes || dest < 1 || dest > numNodes);

    if (canBeReached(graph, src - 1, dest - 1))
    {
        printf("\nExista drum intre restaurantul %d si restaurantul %d!", src, dest);
    }
    else
    {
        printf("\nNu exista drum intre restaurantul %d si restaurantul %d!", src, dest);
    }

    freeGraph(graph);

    return 0;
}
