/*Determinati daca exista sau nu drum direct intre doua restaurante dintr-o retea de tip graf*/

#include <stdlib.h>
#include <stdio.h>

typedef struct Node
{
    int data;
    struct Node *next;
}NODE;
/// pentru simplitate, folosim int uri pt a numi restaurantel/locatiile
/// ex: 1 - restaurantul 1 si tot asa

typedef struct Graph
{
    int vertices;
    int *visited;
    struct Node **adjacency_lists;
} GPH;

typedef struct s
{
    int t;
    int scap;
    int *arr;
} STK;

NODE *create_node(int data)
{
    NODE *newNode = malloc(sizeof(NODE));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void add_edge(GPH *graph, int src, int dest)
{
    NODE *newNode = create_node(dest);
    newNode->next = graph->adjacency_lists[src];
    graph->adjacency_lists[src] = newNode;

    newNode = create_node(src);
    newNode->next = graph->adjacency_lists[dest];
    graph->adjacency_lists[dest] = newNode;
}

GPH *create_g(int v)
{
    int i;
    GPH *graph = malloc(sizeof(GPH));
    graph->vertices = v;
    graph->adjacency_lists = malloc(sizeof(NODE *));
    graph->visited = malloc(sizeof(int) * v);

    for (int i = 0; i < v; i++)
        {
            graph->adjacency_lists[i] = NULL;
            graph->visited[i] = 0;
        } /*/*/
    return graph;
}

STK *create_s(int scap)
{
    STK *s = malloc(sizeof(STK));
    s->arr = malloc(scap * sizeof(int));
    s->t = -1;
    s->scap = scap;

    return s;
}

void push(int pshd, STK *s)
{
    s->t = s->t + 1;
    s->arr[s->t] = pshd;
}

void DFS(GPH *graph, STK *s, int v_nr)
{
    NODE *adj_list = graph->adjacency_lists[v_nr];
    NODE *aux = adj_list;
    graph->visited[v_nr] = 1;
    printf("%d ", v_nr);
    push(v_nr, s);
    while (aux != NULL)
    {
        int con_ver = aux->data;
        if (graph->visited[con_ver] == 0)
            {
                 DFS(graph, s, con_ver);
            }
        aux = aux->next;
    }
}

void insert_edges(GPH *graph, int edg_nr, int nrv)
{
    int src, dest, i;
    printf("adauga %d munchii (de la 1 la %d)\n", edg_nr, nrv);
    for (i = 0; i < edg_nr; i++)
    {
        scanf("%d%d", &src, &dest);
        add_edge(graph, src, dest);
    }
}

void wipe(GPH *graph, int nrv)
{
    for (int i = 0; i < nrv; i++)
    {
        graph->visited[i] = 0;
    }
}

void canbe(GPH *g, int nrv, STK *s1, STK *s2) // 0 sau 1 daca poate fi sau nu ajuns
{
    int *canbe = calloc(5, sizeof(int));
    for (int i = 0; i < nrv; i++) // aici i tine loc de numar adica de restaurant{for (int j = 0; j < 5; j++)
    {
        DFS(g, s1, i);
        wipe(g, nrv);
        DFS(g, s2, i);
        for (int j = 0; j < nrv; j++)
            for (int i = 0; i < nrv; i++)
                if ((s1->arr[i] == j) && (s2->arr[j] == i))
                    *(canbe) = 1;
    }
}

int main()
{

    int nrv;
    int edg_nr;
    int src, dest;
    int i;
    int vortex_1;
    int virtex_2;
    int ans;

    printf("cate noduri are girafa?");
    scanf("%d", &nrv);

    printf("cate muchii are giraful?");
    scanf("%d", &edg_nr);

    GPH *g = create_g(nrv);

    STK *s1 = create_s(2 * nrv);
    STK *s2 = create_s(2 * nrv);

    insert_edges(g, edg_nr, nrv);

    canbe(g, nrv, s1, s2);
}
