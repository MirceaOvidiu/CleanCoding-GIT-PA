// Parcurgere graf cu BFS respectiv DFS

#include <stdlib.h>
#include <stdio.h>

typedef struct Node
{  int data;
  struct Node *next;
} NODE;

typedef struct Graph
{ int vertices;
    int *vertices_visited;
    struct Node **adjacency_lists;
} GRAPH;

NODE *createNode(int vertex)
{
    NODE *new_node = (NODE*) malloc(sizeof(NODE));
    new_node -> data = vertex;
    new_node -> next = NULL;
    return new_node;
}

GRAPH *createGraph(int number_vertices)
{
    GRAPH *graph = (GRAPH*) malloc(sizeof(GRAPH));

    graph ->vertices = number_vertices;
    graph->adjacency_lists = (NODE **)malloc((number_vertices +  1) * sizeof(NODE));
    graph->vertices_visited = (int *) malloc(sizeof(int) * number_vertices);

    for (int i = 1; i <= number_vertices; i++)
    {
        graph->adjacency_lists[i] = NULL;
        graph->vertices_visited[i] = 0;
    }
    return graph;
}

void addEdge(GRAPH *graph, int source, int destination)
{
    NODE *new_node = createNode (destination);

    new_node->next = graph->adjacency_lists[source];
    graph->adjacency_lists[source] = new_node;

    new_node = createNode (source);

    new_node->next = graph->adjacency_lists[destination];
    graph->adjacency_lists[destination] = new_node;
}

int *insertEdge(int number_vertices, int number_edges, GRAPH *graph)
{
    int source_node, destination_node, i;

    printf("Adauga %d muchii (de la 1 la %d)\n", number_edges, number_vertices);

    for (i = 1; i <= number_edges; i++)
    {
        scanf("%d%d", &source_node, &destination_node);
        addEdge(graph, source_node, destination_node);
    }

}

/// bfs utils

int is_empty( NODE *queue)
{
    if ( queue == NULL )
    {
      return 1;
    }
    else
    {
        return 0;
    }
}


void enqueue(NODE **queue, int data)
{
    NODE *new_node = createNode(data);

    if ( is_empty(*queue) )
        *queue = new_node;
    else
    {
        NODE *temp = *queue;
        while (temp->next)
        {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

int dequeue(NODE **queue)
{
    if (is_empty(*queue))
    {
        printf("Coada goala!\n");
        return -1;
    }

    int data = (*queue)->data;

    NODE *temp = *queue;
    *queue = (*queue)->next;

    free(temp);
    return data;
}


void printGraph(GRAPH *graph)
{
    int i;

    for (i = 1; i <= graph->vertices;  i++)
    {
        printf("Nodul %d \n", i);
        NODE *temp = graph->adjacency_lists[i];

     while ( temp )
     {
        printf("%d ", temp->data);
       temp = temp->next;
     }
    printf("\n");
    }
}

void wipeVisitedList(GRAPH *graph, int number_vertices)
{
for (int i = 1; i <= number_vertices; i++)
{
graph->vertices_visited[i] = 0;
}
}

//Parcurgerile:

void DFS( GRAPH *graph, int vertex_number)
{
    NODE *adjacency_newlist = graph->adjacency_lists[vertex_number];
   NODE *temp = adjacency_newlist;

   graph->vertices_visited[vertex_number] = 1;

   printf("%d->", vertex_number);

   while (temp != NULL)
{
    int connected_vertex = temp->data;

    if (graph->vertices_visited[connected_vertex] == 0)
    {
        DFS(graph, connected_vertex);
    }
temp = temp->next;
     }
}

void BFS(GRAPH *graph, int starting_vertex)
{
    NODE *queue = NULL;

    graph->vertices_visited[starting_vertex] = 1;
    enqueue( &queue, starting_vertex);

    while ( !is_empty(queue) )
    {
        int current_node = dequeue(&queue);
      printf("%d ", current_node);

      NODE *temp = graph -> adjacency_lists[current_node];

      while (temp)
      {
          int adjacency_vertex = temp->data;

            if (graph -> vertices_visited[adjacency_vertex] == 0)
            {
            graph->vertices_visited[adjacency_vertex] = 1;
            enqueue(&queue, adjacency_vertex);
            }
    temp = temp->next;
     }
     }
}

int main()
{   int number_vertices, number_edges;
    int starting_vertex;

    printf("Cate noduri are graful?\n");
    scanf("%d", &number_vertices);

    printf("Cate muchii are graful?\n");
    scanf("%d", &number_edges);

    GRAPH *graph = createGraph(number_vertices);

    insertEdge(number_vertices, number_edges, graph);

    printf("Lista de adiacenta a nodurilor este: \n");
    printGraph( graph );

    printf("De unde plecam in DFS?\n");
    scanf("%d", &starting_vertex);

    printf("Parcurgere cu DFS: \n");
    DFS(graph, starting_vertex);

    wipeVisitedList(graph, number_vertices);

    printf("\nDe unde plecam in BFS?\n");
    scanf("%d", &starting_vertex);

   printf("Parcurgere cu BFS:\n");
    BFS(graph, starting_vertex);

    free(graph);
    return 0;
}
