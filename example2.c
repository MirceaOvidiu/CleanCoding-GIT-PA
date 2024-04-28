/*parcurgerge  graf cu DFS/BFS*/

//Imi cer scuze in avans

#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    int data;
    struct Node *next;
} NODE;

typedef struct Graph {
    int Nodes;
    int *visited;
    struct Node **adjacency_lists;
} GPH;

/// utils
NODE *createNode(int data) {

    NODE *new_node = (NODE*)malloc(sizeof(NODE));
    new_node -> data = data;
    new_node -> next = NULL;
    return new_node;
}

GPH *createGraph(int nr_Nodes) {

    GPH *graph = malloc(sizeof(GPH));

    graph->Nodes = nr_Nodes;
    graph->adjacency_lists = malloc(nr_Nodes * sizeof(NODE *));
    graph->visited = malloc(sizeof(int) * nr_Nodes);

    for (int i = 0; i < nr_Nodes; i++) {
        graph->adjacency_lists[i] = NULL;
        graph->visited[i] = 0;
    }

    return graph;
}

void addEdge(GPH *graph, int src, int dest) {
    NODE *new_node = createNode(dest);
    new_node->next = graph->adjacency_lists[src];
    graph->adjacency_lists[src] = new_node;

    new_node = createNode(src);
    new_node->next = graph->adjacency_lists[dest];
    graph->adjacency_lists[dest] = new_node;
}

void insertEdges(GPH *graph, int edg_nr) {
    int src, dest, i;

    printf("adauga %d munchii (de la 0 la %d)\n", edg_nr, graph -> Nodes);

    for (i = 0; i < edg_nr; i++) {
        scanf("%d%d", &src, &dest);
        addEdge(graph, src, dest);
    }
}

/// bfs utils
int isEmpty(NODE *queue) {
    return queue == NULL;
}

void enqueue(NODE **queue, int data) {

    NODE *new_node = createNode(data);

    if (isEmpty(*queue)){
        *queue = new_node;
    }
    else {
        NODE *temp = *queue;
        while (temp->next)
        { temp = temp->next;
        }
        temp->next = new_node;
    }
}

int dequeue(NODE **queue) {

    int data = (*queue)->data;
    NODE *temp = *queue;
    *queue = (*queue)->next; // pointeaza catre urmatorul nod din coada
    free(temp);

    return data;
}

void printGraph(GPH *graph) {
    for (int i = 0; i < graph->Nodes; i++) {
        printf("Lista de adiacenta pentru nodul %d: ", i);
        NODE *temp = graph->adjacency_lists[i];
        while (temp) {
            printf("%d ", temp->data);
            temp = temp->next;
        }
        printf("\n");
    }
}


void wipeVisitedList(GPH *graph) {

    for (int i = 0; i < graph ->Nodes; i++) {
        graph->visited[i] = 0;
    }
}

// parcurgeri
void DFS(GPH *graph, int vertex_nr) {

    NODE *adj_list = graph->adjacency_lists[vertex_nr];
    NODE *temp = adj_list;

    graph->visited[vertex_nr] = 1;
    printf("%d ", vertex_nr);

    while (temp != NULL) {
        int connected_vertex = temp->data;

        if (graph->visited[connected_vertex] == 0) {
            DFS(graph, connected_vertex);
        }
        temp = temp->next;
    }

}


void BFS(GPH *graph, int start) {

    NODE *queue = NULL;

    graph->visited[start] = 1;
    enqueue(&queue, start);

    while (!isEmpty(queue)) {

        int current = dequeue(&queue);
        printf("%d ", current);

        NODE *temp = graph->adjacency_lists[current];

        while (temp) {
            int adj_vertex = temp->data;

            if (graph->visited[adj_vertex] == 0) {

                graph->visited[adj_vertex] = 1;
                enqueue(&queue, adj_vertex);
            }
            temp = temp->next;
        }
    }
}

int main() {

    int nr_of_vertices;
    int nr_of_edges;
//    int src, dest;
//    int i;
    int starting_vertex;
//    int *adj_matrix;

    printf("cate noduri are graful?\n");
    scanf("%d", &nr_of_vertices);

    printf("cate muchii are graful?\n");
    scanf("%d", &nr_of_edges);

    GPH *graph = createGraph(nr_of_vertices);
    insertEdges(graph, nr_of_edges);
    printf("Graful este:\n");
    printGraph(graph);

    printf("de unde plecam in DFS?\n");
    scanf("%d", &starting_vertex);


    printf("parcurgere cu DFS:\n");
    DFS(graph, starting_vertex);

    wipeVisitedList(graph);
    printf("\n");

    printf("de unde plecam in BFS?\n");
    scanf("%d", &starting_vertex);

    printf("parcurgere cu BFS:\n");
    BFS(graph, starting_vertex);

    return 0;
}