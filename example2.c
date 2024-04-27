/*parcurgerge  graf cu DFS/BFS*/

#include <stdio.h>
#include <stdlib.h>

typedef struct queue
{
    int items[100];
    int front;
    int rear;
} QUEUE;

typedef struct Node
{
    int data;
    struct Node *next;
} NODE;

typedef struct Graph
{
    int vertices;
    int *visited;
    NODE **adjacency_lists;
} GPH;

/// utils
NODE *createNode(int v)
{
    NODE *new_node = malloc(sizeof(NODE));
    new_node->data = v;
    new_node->next = NULL;
    return new_node;
}

GPH *createGraph(int vertices)
{
    int i;
    GPH *graph = malloc(sizeof(GPH));

    graph->vertices = vertices;
    graph->adjacency_lists = malloc(vertices * sizeof(NODE *));
    graph->visited = malloc(vertices * sizeof(int));

    for (i = 0; i < vertices; i++)
    {
        graph->adjacency_lists[i] = NULL;
        graph->visited[i] = 0;
    }

    return graph;
}

void addEdge(GPH *graph, int src, int dest)
{
    NODE *new_node = createNode(dest);
    new_node->next = graph->adjacency_lists[src];
    graph->adjacency_lists[src] = new_node;

    new_node = createNode(src);
    new_node->next = graph->adjacency_lists[dest];
    graph->adjacency_lists[dest] = new_node;
}

void insertEdge(int nr_of_vertices, int nr_of_edges, GPH *graph)
{
    int src, dest, i;
    printf("Adauga %d muchii (pentru noduri de la 0 la %d)\n", nr_of_edges, nr_of_vertices - 1);
    for (i = 0; i < nr_of_edges; i++)
    {
        scanf("%d%d", &src, &dest);
        addEdge(graph, src, dest);
    }
}

QUEUE *createQueue()
{
    QUEUE *queue = malloc(sizeof(QUEUE));
    queue->front = -1;
    queue->rear = -1;
    return queue;
}

int isEmpty(QUEUE *queue)
{
    if (queue->rear == -1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void enqueue(QUEUE *queue, int data)
{
    if (queue->rear == 99)
    {
        printf("\n Queue is full.");
    }
    else
    {
        if (queue->front == -1)
        {
            queue->front = 0;
        }
        queue->rear++;
        queue->items[queue->rear] = data;
    }
}

int dequeue(QUEUE *queue)
{
    int item;
    if (isEmpty(queue))
    {
        printf("Queue is empty.");
        item = -1;
    }
    else
    {
        item = queue->items[queue->front];
        queue->front++;
        if (queue->front > queue->rear)
        {
            queue->front = queue->rear = -1;
        }
    }

    return item;
}

void printGraph(GPH *graph)
{
    int i;
    for (i = 0; i < graph->vertices; i++)
    {
        NODE *temp = graph->adjacency_lists[i];

        while (temp)
        {
            printf("%d ", temp->data);
            temp = temp->next;
        }
        printf("\n");
    }
}

void printQueue(QUEUE *queue)
{
    int i = queue->front;

    if (isEmpty(queue))
    {
        printf("Queue is empty.");
    }
    else
    {
        for (i = queue->front; i < queue->rear + 1; i++)
        {
            printf("%d ", queue->items[i]);
        }
    }
}

void wipeVisitedList(GPH *graph, int nr_of_vertices)
{
    for (int i = 0; i < nr_of_vertices; i++)
    {
        graph->visited[i] = 0;
    }
}

void DFS(GPH *graph, int vertex_nr)
{
    NODE *temp = graph->adjacency_lists[vertex_nr];

    graph->visited[vertex_nr] = 1;
    printf("%d ", vertex_nr);

    while (temp != NULL)
    {
        int connected_vertex = temp->data;

        if (graph->visited[connected_vertex] == 0)
        {
            DFS(graph, connected_vertex);
        }
        temp = temp->next;
    }
}

void BFS(GPH *graph, int start)
{
    QUEUE *queue = createQueue();

    graph->visited[start] = 1;
    enqueue(queue, start);

    while (!isEmpty(queue))
    {
        int current = dequeue(queue);
        printf("%d ", current);

        NODE *temp = graph->adjacency_lists[current];

        while (temp)
        {
            int adj_vertex = temp->data;

            if (graph->visited[adj_vertex] == 0)
            {
                graph->visited[adj_vertex] = 1;
                enqueue(queue, adj_vertex);
            }
            temp = temp->next;
        }
    }
}

int main()
{

    int nr_of_vertices;
    int nr_of_edges;
    int starting_vertex;

    printf("Cate noduri are graful?");
    scanf("%d", &nr_of_vertices);

    printf("Cate muchii are graful?");
    scanf("%d", &nr_of_edges);

    GPH *graph = createGraph(nr_of_vertices);

    insertEdge(nr_of_vertices, nr_of_edges, graph);

    printf("De unde plecam in DFS?");
    scanf("%d", &starting_vertex);

    printf("Parcurgere cu DFS: ");
    DFS(graph, starting_vertex);

    wipeVisitedList(graph, nr_of_vertices);
    printf("\n");

    printf("De unde plecam in BFS?");
    scanf("%d", &starting_vertex);

    printf("Parcurgere cu BFS: ");
    BFS(graph, starting_vertex);

    return 0;
}
