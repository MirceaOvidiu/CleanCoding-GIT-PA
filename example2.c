#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int Nod;
    struct Node *next;
} Node;

typedef struct Graph {
    int numNoduri;
    int *visited;
    Node **adjacencyLists;
} Graph;

Node *createNode(int Nod) {
    Node *newNode = malloc(sizeof(Node));
    newNode->Nod = Nod;
    newNode->next = NULL;
    return newNode;
}

Graph *createGraph(int numNoduri) {
    Graph *graph = malloc(sizeof(Graph));
    graph->numNoduri = numNoduri;
    graph->adjacencyLists = malloc(numNoduri * sizeof(Node*));
    graph->visited = malloc(numNoduri * sizeof(int));

    for (int i = 0; i < numNoduri; i++) {
        graph->adjacencyLists[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

void addEdge(Graph *graph, int src, int dest) {
    Node *newNode = createNode(dest);
    newNode->next = graph->adjacencyLists[src];
    graph->adjacencyLists[src] = newNode;

    newNode = createNode(src);
    newNode->next = graph->adjacencyLists[dest];
    graph->adjacencyLists[dest] = newNode;
}

void insertEdges(Graph *graph, int numEdges) {
    int src, dest;
    printf("Enter %d edges (format: src dest):\n", numEdges);
    for (int i = 0; i < numEdges; i++) {
        scanf("%d %d", &src, &dest);
        addEdge(graph, src, dest);
    }
}

int isEmpty(Node *queue) {
    return queue == NULL;
}

void enqueue(Node **queue, int Nod) {
    Node *newNode = createNode(Nod);
    if (*queue == NULL) {
        *queue = newNode;
    } else {
        Node *temp = *queue;
        while (temp->next)
            temp = temp->next;
        temp->next = newNode;
    }
}

int dequeue(Node **queue) {
    if (isEmpty(*queue)) {
        return -1; // Or handle error
    }
    Node *temp = *queue;
    int Nod = temp->Nod;
    *queue = temp->next;
    free(temp);
    return Nod;
}

void DFS(Graph *graph, int startNod) {
    graph->visited[startNod] = 1;
    printf("%d ", startNod);

    Node *adjacencyList = graph->adjacencyLists[startNod];
    while (adjacencyList) {
        int connectedNod = adjacencyList->Nod;
        if (!graph->visited[connectedNod]) {
            DFS(graph, connectedNod);
        }
        adjacencyList = adjacencyList->next;
    }
}

void BFS(Graph *graph, int startNod) {
    Node *queue = NULL;
    graph->visited[startNod] = 1;
    enqueue(&queue, startNod);

    while (!isEmpty(queue)) {
        int currentNod = dequeue(&queue);
        printf("%d ", currentNod);

        Node *adjacencyList = graph->adjacencyLists[currentNod];
        while (adjacencyList) {
            int adjacentNod = adjacencyList->Nod;
            if (!graph->visited[adjacentNod]) {
                graph->visited[adjacentNod] = 1;
                enqueue(&queue, adjacentNod);
            }
            adjacencyList = adjacencyList->next;
        }
    }
}

void wipeVisited(Graph *graph) {
    for (int i = 0; i < graph->numNoduri; i++) {
        graph->visited[i] = 0;
    }
}

int main() {
    int numNoduri, numEdges, startingNod;

    printf("Cate nodrui are graful? ");
    scanf("%d", &numNoduri);

    printf("Cate drumuri are graful? ");
    scanf("%d", &numEdges);

    Graph *graph = createGraph(numNoduri);
    insertEdges(graph, numEdges);

    printf("Starting Nod for DFS? ");
    scanf("%d", &startingNod);
    printf("DFS traversal: ");
    DFS(graph, startingNod);
    wipeVisited(graph);
    printf("\n");

    printf("Starting Nod for BFS? ");
    scanf("%d", &startingNod);
    printf("BFS traversal: ");
    BFS(graph, startingNod);
    printf("\n");

    return 0;
}
