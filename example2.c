#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct Graph {
    int vertices;
    int *visited;
    Node **adjacencyLists;
} Graph;

Node *createNode(int v);
Graph *createGraph(int vertices);
void addEdge(Graph *graph, int src, int dest);
void insEdge(int nrOfVertices, int nrOfEdges, Graph *graph);
int isEmpty(Node *queue);
void enqueue(Node **queue, int data);
int dequeue(Node **queue);
void printGraph(Graph *graph);
void printQueue(Node *queue);
void wipeVisitedList(Graph *graph, int nrOfVertices);
void DFS(Graph *graph, int vertexNr);
void BFS(Graph *graph, int start);

Node *createNode(int v) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = v;
    newNode->next = NULL;
    return newNode;
}

Graph *createGraph(int vertices) {
    int i;
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->vertices = vertices;
    graph->adjacencyLists = (Node **)malloc(vertices * sizeof(Node *));
    graph->visited = (int *)malloc(vertices * sizeof(int));

    for (i = 0; i < vertices; i++) {
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

void insEdge(int nrOfVertices, int nrOfEdges, Graph *graph) {
    int src, dest, i;
    printf("Adauga %d muchi (de la 1 la %d)\n", nrOfEdges, nrOfVertices);
    for (i = 0; i < nrOfEdges; i++) {
        scanf("%d %d", &src, &dest);
        addEdge(graph, src - 1, dest - 1); 
    }
}

int isEmpty(Node *queue) {
    return queue == NULL;
}

void enqueue(Node **queue, int data) {
    Node *newNode = createNode(data);

    if (isEmpty(*queue))
        *queue = newNode;
    else {
        Node *temp = *queue;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

int dequeue(Node **queue) {
    int data = (*queue)->data;
    Node *temp = *queue;
    *queue = (*queue)->next;
    free(temp);
    return data;
}

void printGraph(Graph *graph) {
    int i;
    for (i = 0; i < graph->vertices; i++) {
        printf("%d: ", i + 1); 
        Node *temp = graph->adjacencyLists[i];
        while (temp) {
            printf("%d ", temp->data + 1); 
            temp = temp->next;
        }
        printf("\n");
    }
}

void printQueue(Node *queue) {
    while (queue != NULL) {
        printf("%d ", queue->data);
        queue = queue->next;
    }
    printf("\n");
}

void wipeVisitedList(Graph *graph, int nrOfVertices) {
    for (int i = 0; i < nrOfVertices; i++) {
        graph->visited[i] = 0;
    }
}

void DFS(Graph *graph, int vertexNr) {
    Node *adjList = graph->adjacencyLists[vertexNr];
    Node *temp = adjList;

    graph->visited[vertexNr] = 1;
    printf("%d -> ", vertexNr + 1);
    while (temp != NULL) {
        int connectedVertex = temp->data;

        if (graph->visited[connectedVertex] == 0) {
            DFS(graph, connectedVertex);
        }
        temp = temp->next;
    }
}

void BFS(Graph *graph, int start) {
    Node *queue = NULL;

    graph->visited[start] = 1;
    enqueue(&queue, start);

    while (!isEmpty(queue)) {
        int current = dequeue(&queue);
        printf("%d ", current + 1); 

        Node *temp = graph->adjacencyLists[current];
        while (temp) {
            int adjVertex = temp->data;

            if (graph->visited[adjVertex] == 0) {
                graph->visited[adjVertex] = 1;
                enqueue(&queue, adjVertex);
            }
            temp = temp->next;
        }
    }
}

int main() {
    int nrOfVertices, nrOfEdges;
    int startingVertex;

    printf("Cate noduri are graful? ");
    scanf("%d", &nrOfVertices);
    printf("Cate muchii are graful? ");
    scanf("%d", &nrOfEdges);

    Graph *graph = createGraph(nrOfVertices);
    insEdge(nrOfVertices, nrOfEdges, graph);

    printf("De unde plecam in DFS? ");
    scanf("%d", &startingVertex);
    printf("Parcurgere cu DFS: ");
    DFS(graph, startingVertex - 1); 

    wipeVisitedList(graph, nrOfVertices);
    printf("\n");

    printf("De unde plecam in BFS? ");
    scanf("%d", &startingVertex);
    printf("Parcurgere cu BFS: ");
    BFS(graph, startingVertex - 1); 

    return 0;
}
