///Determine if there is a road between 2 restaurants

#include <stdio.h>
#include <stdlib.h>

// Number of vertices in the graph
struct node
{
    int vertex;
    struct node* next;
};

struct node* createNode(int v);

struct Graph
{
    int numVertices;
    int* visited;

    // We need int** to store a two dimensional array.
    // Similary, we need struct node** to store an array of Linked lists
    struct node** adjLists;
};

void DFS(struct Graph* graph, int vertex, int dest, int* found)
{
    if (*found) // If path already found, stop traversing
    {
        return;
    }

    struct node* temp = graph->adjLists[vertex];

    graph->visited[vertex] = 1;
    printf("Visited %d \n", vertex);

    while (temp != NULL)
    {
        int connectedVertex = temp->vertex;

        if (connectedVertex == dest)
        { // If destination found, set 'found' flag to true
            *found = 1;
            printf("Visited %d \n", dest);
            return;
        }

        if (graph->visited[connectedVertex] == 0)
        {
            DFS(graph, connectedVertex, dest, found);
        }
        temp = temp->next;
    }
}

int isPathExists(struct Graph* graph, int start, int dest)
{
    int found = 0; // Flag to indicate if destination node is found during DFS

    // Perform DFS traversal from the source node
    DFS(graph, start, dest, &found);

    return found;
}

struct node* createNode(int v)
{
    struct node* newNode = malloc(sizeof(struct node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

struct Graph* createGraph(int vertices)
{
    struct Graph* graph = malloc(sizeof(struct Graph));
    graph->numVertices = vertices;

    graph->adjLists = malloc(vertices * sizeof(struct node*));
    graph->visited = malloc(vertices * sizeof(int));

    for (int i = 0; i < vertices; i++)
    {
        graph->adjLists[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

void addEdge(struct Graph* graph, int start, int dest)
{
    // Add edge from start to dest
    struct node* newNode = createNode(dest);
    newNode->next = graph->adjLists[start];
    graph->adjLists[start] = newNode;

    // Add edge from dest to start
//    newNode = createNode(start);
//    newNode->next = graph->adjLists[dest];
//    graph->adjLists[dest] = newNode;

//    if you want to work with undirected graphs
}

void freeGraph(struct Graph* graph)
{
    for (int i = 0; i < graph->numVertices; i++)
    {
        struct node* temp = graph->adjLists[i];
        while (temp != NULL)
        {
            struct node* prev = temp;
            temp = temp->next;
            free(prev);
        }
    }
    free(graph->adjLists);
    free(graph->visited);
    free(graph);
}

int main()
{

    /// to make things simple, we will use int values to name restaurants
    /// ex: 1 - 1st restaurant and so on

    struct Graph* graph = createGraph(5);
    //how many "restaurants" are (this value can be modified)

    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 2);
    addEdge(graph, 2, 3);
    addEdge(graph, 2, 4);
    addEdge(graph, 3, 4);
    // add "road" between restaurants ((un)directed graph)
    // if there will be new "roads", just add them with
    // addEdge(graph, start, dest);

    // Test if there is a path between two nodes
    int start;
    int dest;

    scanf("%d %d", &start, &dest);
    // I want to see if between restaurant "start"
    // and restaurant "destination" is a road

    if (isPathExists(graph, start, dest))
    {
        printf("Path exists between %d and %d\n", start, dest);
    }
    
    else
      
    {
        printf("Path does not exist between %d and %d\n", start, dest);
    }

    freeGraph(graph);

    return 0;
}
