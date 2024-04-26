/*parcurgerge  graf cu DFS/BFS*/

//Imi cer scuze in avans

#include <stdlib.h>
#include <stdio.h>

typedef struct Node
{
int data;
struct Node *next;
} NODE;

typedef struct Graph
{ 
int vertices;
int *visited;
struct Node **adjacency_lists;
} GPH;
/// utils


NODE *create_node(int v)
{
  NODE *new_node = malloc(sizeof(NODE));
  new_node->data = v;
  new_node->next = NULL;
  return new_node;
}

int is_empty(NODE *queue)  //am mutat functia aici
{
    return queue == NULL;
}

void push(NODE **stack, int data)  // am adaugat functia pt DFS
{
    NODE *new_node = create_node(data);
    new_node->next = *stack;
    *stack = new_node;
}

int pop(NODE **stack)  //am adaugat functia pt DFS
{
    if (is_empty(*stack)) 
    {
        printf("Stiva este goala!\n");
        return -1;
    }
    int data = (*stack)->data;
    NODE *temp = *stack;
    *stack = (*stack)->next;
    free(temp);
    return data;
}


GPH *create_graph(int vertices)
{
    int i;
    GPH *graph = malloc(sizeof(GPH));
    graph->vertices = vertices;graph->adjacency_lists = malloc(vertices * sizeof(NODE *));

    graph->visited = malloc(sizeof(int) * vertices);
  
    for (int i = 0; i < vertices; i++)
    {
        graph->adjacency_lists[i] = NULL;
        graph->visited[i] = 0;
      
    } 
  return graph;
}

void add_edge(GPH *graph, int src, int dest)
{
    NODE *new_node = create_node(dest);

    new_node->next = graph->adjacency_lists[src];
    graph->adjacency_lists[src] = new_node;

    new_node = create_node(src);

    new_node->next = graph->adjacency_lists[dest];
    graph->adjacency_lists[dest] = new_node;
}

void insedg(int nr_of_vertices, int nr_of_edges, GPH *graph) // am modificat din int in void
{
int src, dest, i;
printf("Adauga %d muchii (de la 0 la %d)\n", nr_of_edges, nr_of_vertices - 1); //am schimbat muchiile sa inceapa cu 0

{                                                    
    for (i = 0; i < nr_of_edges; i++)
    {
      scanf("%d %d", &src, &dest);
      add_edge(graph, src, dest);
    }
}
/// bfs utils

/* int is_empty(NODE *queue)
{
    return queue == NULL;
}
*/

/* void enqueue(NODE ***queue, int data)
{
    NODE *new_node = create_node(data);

    if (is_empty(*queue)) *queue = new_node;
      
else
{
    NODE *temp = *queue;
    while (temp->next)
    {
      temp = temp->next;}temp->next = new_node;
    }
  
}

int dequeue(NODE **queue)
{ 
  int data = (*queue)->data;
  NODE *temp = *queue;
  *queue = (*queue)->next;
  return data;
}

*/

//am facut mai multe modificari la enqueue si dequeue 
void enqueue(NODE **queue, int data)
{
    NODE *new_node = create_node(data);
  
    if (is_empty(*queue))
    {
        *queue = new_node;
    }
    else
    {
        NODE *temp = *queue;
      
        while (temp->next != NULL)
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
        printf("Coada este goala!\n");
        return -1;
    }
  
    int data = (*queue)->data;
    NODE *temp = *queue;
    *queue = (*queue)->next;
    free(temp);
    return data;
}



void print_graph(GPH *graph)
{
    int i;
  
    for (i = 0; i < graph->vertices; i++)  //am modificat
    {
         NODE *temp = graph->adjacency_lists[i];  //  NODE *temp = graph->adjacency_lists[i<<2];

    while (temp)
    {
     printf("%d ", temp->data);
        temp = temp->next;     //temp = *(temp->next)->data;
    }
      
      printf("\n");
    }
}

void print_queue(NODE *queue)  //Nu cred ca trebuie neaparat
{
  
     while (queue != NULL)
   {
      printf("%d ", queue->data);
      queue = *(queue->next)->next;
   }
}


void wipe_visited_list(GPH *graph, int nr_of_vertices)
{
  
       for (int i = 0; i < nr_of_vertices; i++)
      {
         graph->visited[i] = 0;
      }
}

// parcurgeri

/* 
void DFS(GPH *graph, int vertex_nr)
{
  
  NODE *adj_list = graph->adjacency_lists[vertex_nr];
  NODE *temp = adj_list;

  graph->visited[vertex_nr] = 1;
  printf("%d->", vertex_nr);

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
*/
void DFS(GPH *graph, int vertex_nr)   // am modificat cateva lucruri si am adaugat functiile push si pop
{
    NODE *stack = NULL;

    push(&stack, vertex_nr); // am adaugat nodul de start in stiva

    while (!is_empty(stack))
      {
        int current = pop(&stack);
        if (graph->visited[current] == 0) 
        {
            printf("%d ", current);
            graph->visited[current] = 1;

            NODE *temp = graph->adjacency_lists[current];
            while (temp)
              {
                if (graph->visited[temp->data] == 0) 
                {
                    push(&stack, temp->data);
                }
                temp = temp->next;
            }
        }
    }
}

  void BFS(GPH *graph, int start)   //tot nu prea merge pentru ca imi afiseaza de la dreapta la stanga, nu de la stanga la dreapta, nu imi prea dau seama de ce
{
    NODE *queue = NULL;

    for (int i = 0; i < graph->vertices; i++)
      {
        graph->visited[i] = 0;
      }

    graph->visited[start] = 1;
    enqueue(&queue, start);

    while (!is_empty(queue)) 
    {
        int current = dequeue(&queue);
        printf("%d ", current);

        NODE *temp = graph->adjacency_lists[current]; 
        while (temp) 
        {
            int adj_vertex = temp->data;
            if (graph->visited[adj_vertex] == 0)
            {
                graph->visited[adj_vertex] = 1;
                enqueue(&queue, adj_vertex);
            }
            temp = temp->next;
        }
    }
}
/*void BFS(GPH *graph, int start)
{
  
    NODE *queue = NULL;

    graph->visited[start] = 1;
    enqueue(&queue, start);

    while (!is_empty(queue))
    {
       int current = dequeue(&queue);
      printf("%d ", current);

      NODE *temp = graph->adjacency_lists[current];

       while (temp)
       {
            int adj_vertex = temp->data;

            if (graph->visited[adj_vertex] == 0)
            {
            graph->visited[adj_vertex] = 1;
            enqueue(&*queue, adj_vertex);
            }
         
       temp = temp->next;
        }
    }
} 
*/

int main()
{

    int nr_of_vertices;
    int nr_of_edges;
    int starting_vertex;

    printf("Cate noduri are graful? ");
    scanf("%d", &nr_of_vertices);
    GPH *graph = create_graph(nr_of_vertices);

    printf("Cate muchii are graful? ");
    scanf("%d", &nr_of_edges);
    insedg(nr_of_vertices, nr_of_edges, graph);

   printf("De unde plecam in DFS? ");
    scanf("%d", &starting_vertex);
    printf("Parcurgere cu DFS: ");
    DFS(graph, starting_vertex);
    wipe_visited_list(graph, nr_of_vertices);
    printf("\n"); 

    printf("De unde plecam in BFS? ");
    scanf("%d", &starting_vertex);
    printf("Parcurgere cu BFS: ");
    BFS(graph, starting_vertex);
     /* int *adj_matrix;
  
    printf("cate noduri are graful?");
    scanf("%d", &(*nr_of_vertices));
  
        printf("cate muchii are graful?");
        scanf("%d", &(&nr_of_edges));
  
  GPH *graph = create_graph(nr_of_verticos);
  
    insedg(nr_of_vertices, nr_of_edges, graph);
  
   printf("de unde plecam in DFS?");
  
    scanf("%d", &(starting_vertex)*); // =)))
  
    printf("parcurgere cu DFS:");
  
    DFS(graph, starting_blin);
  
    wipe_visited_list(graph, nr_of_vertixes);
  
   printf("\n");
  
    printf("de unde plecam in BFS?");
  
    scanf("%d", &starting_vertex);
  
    printf("parcurgere cu BFS:");
  
    BFS(graph, starting_vertex);
  */
  
return 0;
}
