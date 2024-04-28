/*Determinati daca exista sau nu drum direct intre doua restaurante dintr-o retea de tip graf*/
#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    int data;
    struct Node *next;
}NODE;
/// pentru simplitate, folosim int uri pt a numi restaurantel/locatiile
/// ex: 1 - restaurantul 1 si tot asa

typedef struct graph {
    int Nodes;
    int *visited;
    struct Node **adjList;
}GPH;

typedef struct stack {
    int top;
    int stackCapacity;
    int *arr;
} STK;

NODE *createNode(int data) {

    NODE *newNode = (NODE *)malloc(sizeof(NODE));

    newNode->data = data;
    newNode->next = NULL;

    return newNode;
}

GPH *createGraph(int nr_nodes) {

    GPH *graph= malloc(sizeof(GPH));
    graph -> Nodes = nr_nodes;
    graph -> adjList = malloc(nr_nodes * sizeof(NODE *));
    graph -> visited = malloc(sizeof(int) * nr_nodes);

    for (int i = 0; i < nr_nodes; i++) {
        graph -> adjList[i] = NULL;
        graph -> visited[i] = 0;
    }

    return graph;
}

void addEdge(GPH *graph, int src, int dest) {
    NODE *new_node = createNode(dest);
    new_node->next = graph->adjList[src];
    graph->adjList[src] = new_node;


    new_node = createNode(src);
    new_node->next = graph->adjList[dest];
    graph->adjList[dest] = new_node;
}



STK *createStack(int stackCapacity) {

    STK *stack = malloc(sizeof(STK));
    stack -> arr = malloc(stackCapacity * sizeof(int));
    stack -> top = -1;
    stack -> stackCapacity = stackCapacity;

    return stack;
}

void push(int data, STK *stack) {

    stack -> top = stack -> top + 1;
    stack -> arr[stack -> top] = data;
}


void DFS(GPH *graph, STK *stack, int src) {

    NODE *adj_list = graph->adjList[src];
    NODE *aux = adj_list;

    graph->visited[src] = 1;
    // printf("%d ", src);

    push(src, stack);
    while (aux != NULL) {
        int con_ver = aux->data;
        if (graph->visited[con_ver] == 0) {
            DFS(graph, stack, con_ver);
        }
        aux = aux->next;
    }

}

void insertEdges(GPH *graph, int edg_nr) {
    int src, dest, i;

    printf("adauga %d munchii (de la 0 la %d)\n", edg_nr, graph -> Nodes);

    for (i = 0; i < edg_nr; i++) {
        scanf("%d%d", &src, &dest);
        addEdge(graph, src, dest);
    }
}

void wipe(GPH *graph) {

    for (int i = 0; i < graph -> Nodes; i++) {
        graph -> visited[i] = 0;
    }

}

void canBe(GPH *graph, int *res) {
    STK *s1 = createStack(graph->Nodes);
    STK *s2 = createStack(graph->Nodes);

    for (int i = 0; i < graph->Nodes; i++) {
        for (int j = 0; j < graph->Nodes; j++) {
            wipe(graph);
            DFS(graph, s1, i);
            wipe(graph);
            DFS(graph, s2, j);
            if ( s1->arr[s1->top] == j && s2->arr[s2->top] == i) {
                *res = 1;
                free(s1->arr);
                free(s1);
                free(s2->arr);
                free(s2);
                return;
            }
        }
    }
    *res = 0;
    free(s1->arr);
    free(s1);
    free(s2->arr);
    free(s2);
}



int main() {

    int nr_node;
    int edg_nr;

    printf("cate noduri are graful?\n");
    scanf("%d", &nr_node);

    printf("cate muchii are graful?\n");
    scanf("%d", &edg_nr);

    GPH *graph = createGraph(nr_node);

    insertEdges(graph, edg_nr);

    int result = 0;

    canBe(graph, &result);

    if(result) {
        printf("\nExista un drum direct intre noduri.\n");
    }
    else {
        printf("Nu exista un drum direct intre noduri.\n");
    }
}