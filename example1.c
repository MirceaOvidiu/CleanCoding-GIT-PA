/* Determinati daca exista sau nu drum direct intre
doua restaurante dintr-o retea de tip graf */

// Restaurantele le diferentiem prin variabila int,ex: restaurant nr 1,2,....

#include <stdlib.h>
#include <stdio.h>

typedef struct Node
{
    int data;
    struct Node *next;
} NODE;

typedef struct Graph
{
    int *nodes_visited;
    struct Node **adjacency_list;
} GRAPH;


typedef struct Stack
{
    int top;
    int stack_capacity;
    int *array_of_elements;
} STACK;


NODE *create_node(int vertex)
{
    NODE *newnode = (NODE *) malloc(sizeof(NODE));
    newnode -> data = vertex;
    newnode -> next = NULL;
    return newnode;
}


void addEdge (GRAPH *graph, int source_node, int destination_node)
{
    NODE *new_node = create_node(destination_node);

    new_node-> next = graph -> adjacency_list [source_node];
    graph -> adjacency_list [source_node] = new_node;

    new_node = create_node(source_node);
    new_node -> next = graph -> adjacency_list [destination_node];
    graph -> adjacency_list [destination_node] = new_node;
}

GRAPH *createGraph (int number_of_vertex)
{
    GRAPH * new_graph = (GRAPH *) malloc (sizeof(GRAPH)) ;
    new_graph -> adjacency_list = (NODE **)malloc(sizeof(NODE *) * (number_of_vertex + 1));
    new_graph -> nodes_visited = (int *) malloc(sizeof(int) * number_of_vertex);

    for (int i = 1; i <= number_of_vertex; i++ )
    {
        new_graph -> adjacency_list[i] = NULL;
        new_graph -> nodes_visited[i] = 0;
    }

    return new_graph ;
}

STACK *createStack (int stack_capacity)
{
    STACK *new_stack = (STACK *) malloc(sizeof(STACK));
    new_stack -> array_of_elements = (int *) malloc(stack_capacity * sizeof(int));
    new_stack -> top = -1;
    new_stack -> stack_capacity = stack_capacity;

    return new_stack;
}

void pushElement(int pushed_element, STACK *stack)
{
    stack->top = stack->top + 1;
    stack->array_of_elements[stack->top] = pushed_element;
}

void DFS (GRAPH *graph, STACK *stack, int vertex)
{
    NODE *list_of_adjacency = graph->adjacency_list[vertex];
    NODE *temporary_list = list_of_adjacency;

    graph->nodes_visited[vertex] = 1;

    printf(" %d ", vertex);

    pushElement(vertex, stack);

    while (temporary_list != NULL)
    {
        int adjacency_node = temporary_list -> data;

        if ( graph -> nodes_visited[adjacency_node] == 0)
        {
            DFS(graph, stack, adjacency_node);
        }

        temporary_list = temporary_list -> next;
    }
}

void insertEdges (GRAPH *graph, int number_edges, int number_vertex)
{
    int source_node, destination_node, i;

    printf("\nAdauga %d muchii (de la 1 la %d)\n ", number_edges, number_vertex);

    for (i = 1; i <= number_edges; i++)
    {
        scanf("%d%d", &source_node, &destination_node);
        addEdge(graph, source_node, destination_node);
    }

}

void wipeElement(GRAPH *graph, int number_vertex)  //marcheaza nodurile grafului ca nevizitate
{
    for (int i = 1; i <= number_vertex; i++)
    {
        graph->nodes_visited[i] = 0;
    }
}

int verifyRoad(GRAPH *graph, int number_of_vertex, STACK *stack1, STACK *stack2, int restaurant_1, int restaurant_2)
// 0 sau 1 daca poate fi sau nu ajuns
{
    int existing_road = 0;

    printf( "\nParcurgere DFS nodul %d\n", restaurant_1 );
    DFS( graph, stack1 , restaurant_1);

    wipeElement(graph, number_of_vertex );

    printf( "\nParcurgere DFS nodul %d\n", restaurant_2 );
    DFS( graph, stack2 , restaurant_2);

    for (int j = 1 ; j <= number_of_vertex ; j++)
    {
        for (int i = 1; i <= number_of_vertex; i++) {
            if ((stack1->array_of_elements[i] == restaurant_2) && (stack2->array_of_elements[j] == restaurant_1)) {
                existing_road = 1;

            }

        }
    }
    return existing_road;
}

int main ( )
{
    int number_of_vertex , number_of_edges , road_between_nodes, restaurant_1, restaurant_2;

    printf ( " \nCate noduri are graful? " );
    scanf ( "%d" , &number_of_vertex );

    printf ( " \nCate muchii are graful? " );
    scanf("%d" , &number_of_edges );

    GRAPH *graph = createGraph (number_of_vertex );

    insertEdges(graph, number_of_edges, number_of_vertex);

    printf ( "\nScrieti indicativul celor 2 restaurante:  ");
    scanf ( "%d%d", &restaurant_1, &restaurant_2);

    STACK *stack_1 = createStack( number_of_vertex);
    STACK *stack_2 = createStack( number_of_vertex);

    road_between_nodes = verifyRoad (graph, number_of_vertex , stack_1, stack_2 , restaurant_1, restaurant_2);

    if ( road_between_nodes == 1)
        printf ( "\n Exista drum intre restaurantele %d si %d", restaurant_1, restaurant_2);
    else
        printf ( "\n Nu exista drum intre restaurante %d si %d", restaurant_1, restaurant_2 );

    free(graph);
    free(stack_1);
    free(stack_2);
    return 0;

}
