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

    printf("\nAdauga %d muchii (de la 1 la %d)\n", edgeNum, graph->numNodes);

    // Citirea de la tastatura a muchiilor
    for (i = 0; i < edgeNum; i++)
    {
        do
        {
            printf("Muchia %d:", i + 1);
            scanf("%d %d", &src, &dest);

            // Asiguram crearea de muchie intre doua noduri valide
            if (src < 1 || src > graph->numNodes || dest < 1 || dest > graph->numNodes || src == dest)
            {
                printf("Noduri invalide! Introduceti noduri valide (intre %d si %d).\n", 1, graph->numNodes);
            }

        } while (src < 1 || src > graph->numNodes || dest < 1 || dest > graph->numNodes || src == dest);

        addEdge(graph, src - 1, dest - 1);
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

// BFS Utils
int isEmpty(NODE *queue)
{
    return (queue == NULL);
}

void enqueue(NODE **queue, int data)
{
    NODE *newNode = createNode(data);

    if (isEmpty(*queue))
    {
        *queue = newNode;
    }
    else
    {
        NODE *aux = *queue;
        while (aux->next)
        {
            aux = aux->next;
        }

        aux->next = newNode;
    }
}

int dequeue(NODE **queue)
{
    int data = (*queue)->data;

    NODE *temp = *queue;
    *queue = (*queue)->next;

    return data;
}

// Parcurgere in adancime graf prin transmiterea sursei (nod de inceput)
void DFS(GRAPH *graph, int src)
{
    NODE *adjacencyList = graph->adjacencyList[src];
    NODE *aux = adjacencyList;

    graph->visited[src] = 1;
    printf("%d ", src + 1);

    while (aux != NULL)
    {
        int neighbor = aux->data;

        if (graph->visited[neighbor] == 0)
        {
            DFS(graph, neighbor);
        }
        aux = aux->next;
    }
}

// Parcurgere in latime graf prin transmiterea sursei (nod de inceput)
void BFS(GRAPH *graph, int src)
{
    NODE *queue = NULL;

    graph->visited[src] = 1;
    enqueue(&queue, src);

    while (!isEmpty(queue))
    {
        int current = dequeue(&queue);
        printf("%d ", current + 1);

        NODE *temp = graph->adjacencyList[current];

        while (temp)
        {
            int adj_vertex = temp->data;

            if (graph->visited[adj_vertex] == 0) {
                graph->visited[adj_vertex] = 1;
                enqueue(&queue, adj_vertex);
            }
            temp = temp->next;
        }
    }
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

int main()
{
    int numNodes, numEdges;

    do
    {
        printf("\nIntroduceti numarul de noduri (intre 2 si 100):");
        scanf("%d", &numNodes);

        if (numNodes < 2 || numNodes > 100)
        {
            printf("Numarul de noduri trebuie sa fie intre 2 si 100!\n");
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
        printf("Introduceti numarul de muchii dintre noduri (intre 1 si %d):", maxEdges);
        scanf("%d", &numEdges);

        if (numEdges < 1 || numEdges > maxEdges)
        {
            printf("Numarul de muchii trebuie sa fie intre 1 si %d!\n", maxEdges);
        }
    } while (numEdges < 1 || numEdges > maxEdges);

    // Adaugam muchiile in graf
    insertEdges(graph, numEdges);

    int src;

    // Parcurgerea DFS
    printf("De unde plecam in DFS?\n");
    scanf("%d", &src);

    printf("Parcurgere cu DFS: ");
    DFS(graph, src - 1);

    printf("\n\n");

    wipe(graph);

    // Parcurgerea BFS
    printf("De unde plecam in BFS?\n");
    scanf("%d", &src);

    printf("Parcurgere cu BFS: ");
    BFS(graph, src - 1);
    printf("\n");

    freeGraph(graph);

    return 0;
}
