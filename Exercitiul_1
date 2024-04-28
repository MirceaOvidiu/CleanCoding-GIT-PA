/*Determinati daca exista sau nu drum intre doua restaurante dintr-o retea de tip graf*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *next;
} NODE;
// pentru simplitate, folosim int uri pt a numi restaurantele/locatiile
// ex: 1 - restaurantul 1 si tot asa

typedef struct Graph
{
    int number_of_restaurants;
    int *visited_restaurants;
    struct Node **adjacency_list;
} GPH;

typedef struct Stack
{
    int t;
    int scap;
    int *stack_array;
} STK;

NODE *create_node(int value)
{
    NODE *node = malloc(sizeof(NODE));
    node->data = value;
    node->next = NULL;
    return node;
}

void add_edge(GPH *graph, int source, int destination)
{
    NODE *node = create_node(destination);
    node->next = graph->adjacency_list[source];
    graph->adjacency_list[source] = node;

    node = create_node(source);
    node->next = graph->adjacency_list[destination];
    graph->adjacency_list[destination] = node;
}

GPH *create_graph(int node_number)
{
    GPH *graph = malloc(sizeof(GPH));
    graph->number_of_restaurants = node_number;
    graph->adjacency_list = malloc(node_number * sizeof(NODE *)); // CORECTAT
    graph->visited_restaurants = malloc(node_number * sizeof(int));

    for (int i = 0; i < node_number; i++)
    {
        graph->adjacency_list[i] = NULL;
        graph->visited_restaurants[i] = 0;
    }
    return graph;
}

STK *create_stack(int scap)
{
    STK *s = malloc(sizeof(STK));
    s->stack_array = malloc(scap * sizeof(int));
    s->t = -1;
    s->scap = scap;
    return s;
}

void push(int pushed_value, STK *stack)
{
    stack->t = stack->t + 1;
    stack->stack_array[stack->t] = pushed_value;
}

void visit_restaurants_DFS(GPH *graph, STK *stack, int current_restaurant)
{
    NODE *adj_list = graph->adjacency_list[current_restaurant];
    NODE *aux = adj_list;

    graph->visited_restaurants[current_restaurant] = 1;
    printf("%d -> ", current_restaurant);
    push(current_restaurant, stack);
    while (aux != NULL)
    {
        int near_restaurant = aux->data;
        if (graph->visited_restaurants[near_restaurant] == 0)
        {
            visit_restaurants_DFS(graph, stack, near_restaurant);
        }
        aux = aux->next;
    }
}

void insert_edges(GPH *graph, int edge_number, int node_number)
{
    int source, destination, i;
    printf("adauga %d muchii (de la 1 la %d)\n",
           edge_number, node_number);
    for (i = 0; i < edge_number; i++)
    {
        scanf("%d%d", &source, &destination);
        add_edge(graph, source, destination);
    }
}

void wipe(GPH *graph, int node_number)
{
    for (int i = 0; i < node_number; i++)
    {
        graph->visited_restaurants[i] = 0;
    }
}

void could_it_be_visited(GPH *graph, int node_number) // 0 sau 1 - daca poate fi sau nu ajuns PENTRU GRAPH->VISITED_RESTAURANTS + AFISARI ADECVATE (completare)
{
    for (int i = 0; i < node_number; i++)
    {
        STK *stack = create_stack(node_number);
        wipe(graph, node_number);
        printf("\n");
        visit_restaurants_DFS(graph, stack, i);
        for (int j = 0; j < node_number; j++)
        {
            if (i != j)
            {
                if (graph->visited_restaurants[j])
                {
                    printf("\nExista drum intre restaurantele %4d si %d", i, j);
                }
                else
                {
                    printf("\nNU exista drum intre restaurantele %d si %d", i, j);
                }
            }
        }
        free(stack->stack_array);
        free(stack);
        printf("\n");
    }
}

int main()
{
    int node_number;
    int edge_number;

    printf("cate noduri are graful? ");
    scanf("%d", &node_number);

    printf("cate muchii are graful? ");
    scanf("%d", &edge_number);

    GPH *graph = create_graph(node_number);

    insert_edges(graph, edge_number, node_number);

    could_it_be_visited(graph, node_number);
}
//Modificari mai importante aduse functiei canbe() (actuala could_it_be_visited())
//A se citi detaliile din fisierul pdf!
