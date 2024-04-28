#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int nod;
    struct Node *next;
} Node;

typedef struct {
    int numNod;
    int *visited;
    Node **adjList;
} Graph;

Node *createNode(int nod) {
    Node *newNode = (Node*) malloc(sizeof(Node));
    newNode->nod = nod;
    newNode->next = NULL;
    return newNode;
}

void addEdge(Graph *graph, int source, int destination) {
    Node *newNode = createNode(destination);
    newNode->next = graph->adjList[source];
    graph->adjList[source] = newNode;

    newNode = createNode(source);
    newNode->next = graph->adjList[destination];
    graph->adjList[destination] = newNode;
}

Graph *createGraph(int numNod) {
    Graph *graph = (Graph*) malloc(sizeof(Graph));
    graph->numNod = numNod;
    graph->adjList = (Node**) malloc(numNod * sizeof(Node*));
    graph->visited = (int*) malloc(numNod * sizeof(int));

    for (int i = 0; i < numNod; i++) {
        graph->adjList[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

void DFS(Graph *graph, int startnod) {
    graph->visited[startnod] = 1;
    printf("%d ", startnod);

    for (Node *currentNode = graph->adjList[startnod]; currentNode != NULL; currentNode = currentNode->next) {
        if (graph->visited[currentNode->nod] == 0)
            DFS(graph, currentNode->nod);
    }
}

void insertEdges(Graph *graph) {
    int numEdges, source, destination;

    printf("Cate drumuri? ");
    scanf("%d", &numEdges);

    printf("adauga %d drumuri:\n", numEdges);
    for (int i = 0; i < numEdges; i++) {
        scanf("%d %d", &source, &destination);
        addEdge(graph, source, destination);
    }
}

int main() {
    int numNod;

    printf("Cate Noduri? ");
    scanf("%d", &numNod);

    Graph *graph = createGraph(numNod);

    insertEdges(graph);

    printf("Performing DFS starting from node 0:\n");
    DFS(graph, 0);
    
    return 0;
}