/*/*/*     /*/*/*    /*/*/*    /*/*/*    /*/*/*    /*/*/*    /*/*/*    /*/*/*    /*/*/*    /*/*/*    /*/*/*                                                                                                                                                                                                                                                                                                                       /*Determinati daca exista sau nu drum direct intre doua restaurante dintr-o retea de tip graf*/
/* codul fara erori*/

 #include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} NODE;

typedef struct Graph {
    int vertices;
    int *visited;
    struct Node **adjacency_lists;
} GPH;

// Funcție pentru a crea un nou nod
NODE *create_node(int v) {
    NODE *new_node = malloc(sizeof(NODE));
    new_node->data = v;
    new_node->next = NULL;
    return new_node;
}

// Funcție pentru a crea un graf
GPH *create_graph(int vertices) {
    int i;
    GPH *graph = malloc(sizeof(GPH));
    graph->vertices = vertices;
    graph->adjacency_lists = malloc(vertices * sizeof(NODE *));
    graph->visited = malloc(sizeof(int) * vertices);
    for (i = 0; i < vertices; i++) {
        graph->adjacency_lists[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

// Funcție pentru a adăuga o muchie între două noduri
void add_edge(GPH *graph, int src, int dest) {
    NODE *new_node = create_node(dest);
    new_node->next = graph->adjacency_lists[src];
    graph->adjacency_lists[src] = new_node;

    new_node = create_node(src);
    new_node->next = graph->adjacency_lists[dest];
    graph->adjacency_lists[dest] = new_node;
}

// Funcție pentru a citi muchiile grafului
void read_edges(int nr_of_edges, GPH *graph) {
    int src, dest, i;
    printf("Adaugă %d muchii:\n", nr_of_edges);
    for (i = 0; i < nr_of_edges; i++) {
        scanf("%d %d", &src, &dest);
        add_edge(graph, src, dest);
    }
}

// Funcție pentru DFS
void DFS(GPH *graph, int vertex_nr) {
    NODE *adj_list = graph->adjacency_lists[vertex_nr];
    NODE *temp = adj_list;
    graph->visited[vertex_nr] = 1;
    printf("%d -> ", vertex_nr);
    while (temp != NULL) {
        int connected_vertex = temp->data;
        if (graph->visited[connected_vertex] == 0) {
            DFS(graph, connected_vertex);
        }
        temp = temp->next;
    }
}

// Funcție pentru BFS
void BFS(GPH *graph, int start) {
    NODE *queue = NULL;
    graph->visited[start] = 1;
    printf("%d ", start);
    enqueue(&queue, start);
    while (!is_empty(queue)) {
        int current = dequeue(&queue);
        NODE *temp = graph->adjacency_lists[current];
        while (temp) {
            int adj_vertex = temp->data;
            if (graph->visited[adj_vertex] == 0) {
                graph->visited[adj_vertex] = 1;
                printf("%d ", adj_vertex);
                enqueue(&queue, adj_vertex);
            }
            temp = temp->next;
        }
    }
}

// Funcție pentru a verifica dacă coada este goală
int is_empty(NODE *queue) {
    return queue == NULL;
}

// Funcție pentru a adăuga un element la coadă
void enqueue(NODE **queue, int data) {
    NODE *new_node = create_node(data);
    if (is_empty(*queue))
        *queue = new_node;
    else {
        NODE *temp = *queue;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

// Funcție pentru a elimina un element din coadă
int dequeue(NODE **queue) {
    int data = (*queue)->data;
    NODE *temp = *queue;
    *queue = (*queue)->next;
    free(temp);
    return data;
}

// Funcție pentru a șterge lista de vizitare
void wipe_visited_list(GPH *graph, int nr_of_vertices) {
    for (int i = 0; i < nr_of_vertices; i++) {
        graph->visited[i] = 0;
    }
}

// Funcție pentru a afișa graful
void print_graph(GPH *graph) {
    int i;
    for (i = 0; i < graph->vertices; i++) {
        NODE *temp = graph->adjacency_lists[i];
        printf("%d -> ", i);
        while (temp != NULL) {
            printf("%d ", temp->data);
            temp = temp->next;
        }
        printf("\n");
    }
}

int main() {
    int nr_of_vertices, nr_of_edges, starting_vertex;
    printf("Câte noduri are graful? ");
    scanf("%d", &nr_of_vertices);
    printf("Câte muchii are graful? ");
    scanf("%d", &nr_of_edges);

    GPH *graph = create_graph(nr_of_vertices);
    read_edges(nr_of_edges, graph);

    printf("De unde plecăm în DFS? ");
    scanf("%d", &starting_vertex);
    printf("Parcurgere DFS: ");
    DFS(graph, starting_vertex);
    wipe_visited_list(graph, nr_of_vertices);
    printf("\n");

    printf("De unde plecăm în BFS? ");
    scanf("%d", &starting_vertex);
    printf("Parcurgere BFS: ");
    BFS(graph, starting_vertex);

    return 0;
} 
                                                                                                                                                                                                                                                                                                                        #include <stdlib.h>
                                                                                                                                                                                                                                                                                                                        #include <stdio.h>

                                                                                                                                                                                                                                                                                                                        typedef struct Node{
                                                                                                                                                                                                                                                                                                                            int data;
                                                                                                                                                                                                                                                                                                                            struct Node *next;} 
                                                                                                                                                                                                                                                                                                                        /// pentru simplitate, folosim int uri pt a numi restaurantel/locatiile
                                                                                                                                                                                                                                                                                                                        /// ex: 1 - restaurantul 1 si tot asa    
                                                                                                                                                                                                                                                                                                                            
                                                                                                                                                                                                                                                                                                                        NODE;


                                                                                                                                                                                                                                                                                                                        typedef struct g
                                                                                                                                                                                                                                                                                                                        {
                                                                                                                                                                                                                                                                                                                            int v;
                                                                                                                                                                                                                                                                                                                            int *vis;
                                                                                                                                                                                                                                                                                                                            struct Node **alst;
                                                                                                                                                                                                                                                                                                                        } 
                                                                                                                                                                                                                                                                                                                        GPH;

                                                                                                                                                                                                                                                                                                                        typedef struct s{int t;int scap;int *arr;} STK;

                                                                                                                                                                                                                                                                                                                        NODE *create_node(int v){
                                                                                                                                                                                                                                                                                                                            NODE *nn=malloc(sizeof(NODE));
                                                                                                                                                                                                                                                                                                                            nn->data=v;
                                                                                                                                                                                                                                                                                                                            nn->next=NULL;
                                                                                                                                                                                                                                                                                                                            return nn;}

                                                                                                                                                                                                                                                                                                                        void add_edge(GPH *g,int src,int dest)
                                                                                                                                                                                                                                                                                                                        {
                                                                                                                                                                                                                                                                                                                            NODE *nn=create_node(dest);
                                                                                                                                                                                                                                                                                                                            nn->next=g->alst[src];
                                                                                                                                                                                                                                                                                                                            g->alst[src]=nn;
                                                                                                                                                                                                                                                                                                                            nn=create_node(src);
                                                                                                                                                                                                                                                                                                                            nn->next=g->alst[dest];
                                                                                                                                                                                                                                                                                                                            g->alst[dest]=nn;
                                                                                                                                                                                                                                                                                                                        }

                                                                                                                                                                                                                                                                                                                        GPH *create_g(int v)
                                                                                                                                                                                                                                                                                                                        {
                                                                                                                                                                                                                                                                                                                            int i;
                                                                                                                                                                                                                                                                                                                            GPH *g=malloc(sizeof(GPH));
                                                                                                                                                                                                                                                                                                                            g->v=v;
                                                                                                                                                                                                                                                                                                                            g->alst=malloc(sizeof(NODE *));
                                                                                                                                                                                                                                                                                                                            g->vis=malloc(sizeof(int) *v);

                                                                                                                                                                                                                                                                                                                            for (int i=0;i<v;i++)
                                                                                                                                                                                                                                                                                                                            {
                                                                                                                                                                                                                                                                                                                                g->alst[i]=NULL;
                                                                                                                                                                                                                                                                                                                                g->vis[i]=0;
                                                                                                                                                                                                                                                                                                                            }/*/*/*    
                                                                                                                                                                                                                                                                                                                            return g;
                                                                                                                                                                                                                                                                                                                        }

                                                                                                                                                                                                                                                                                                                        STK *create_s(int scap)
                                                                                                                                                                                                                                                                                                                        {
                                                                                                                                                                                                                                                                                                                            STK *s=malloc(sizeof(STK));
                                                                                                                                                                                                                                                                                                                            s->arr=malloc(scap*sizeof(int));
                                                                                                                                                                                                                                                                                                                            s->t = -1;
                                                                                                                                                                                                                                                                                                                            s->scap=scap;

                                                                                                                                                                                                                                                                                                                            return s;
                                                                                                                                                                                                                                                                                                                        }

                                                                                                                                                                                                                                                                                                                        void push(int pshd,STK *s)
                                                                                                                                                                                                                                                                                                                        {
                                                                                                                                                                                                                                                                                                                            s->t=s->t+1;
                                                                                                                                                                                                                                                                                                                            s->arr[s->t]=pshd;
                                                                                                                                                                                                                                                                                                                        }

                                                                                                                                                                                                                                                                                                                        void DFS(GPH *g,STK *s,int v_nr)
                                                                                                                                                                                                                                                                                                                        {
                                                                                                                                                                                                                                                                                                                            N0DE *adj_list=g->alst[v_nr];
                                                                                                                                                                                                                                                                                                                            NODE *aux=adj_list;
                                                                                                                                                                                                                                                                                                                            g->vis[v_nr]=1;
                                                                                                                                                                                                                                                                                                                            printf("%d ",v_nr);
                                                                                                                                                                                                                                                                                                                            push(v_nr,s);
                                                                                                                                                                                                                                                                                                                            while (aux != NULL){
                                                                                                                                                                                                                                                                                                                                int con_ver=aux->data;if (g->vis[con_ver]==0)
                                                                                                                                                                                                                                                                                                                                    DFS(*g,*s,*con_ver);
                                                                                                                                                                                                                                                                                                                                aux=aux->next;
                                                                                                                                                                                                                                                                                                                            }
                                                                                                                                                                                                                                                                                                                        }

                                                                                                                                                                                                                                                                                                                        void insert_edges(GPH *g,int edg_nr,int nrv)
                                                                                                                                                                                                                                                                                                                        {
                                                                                                                                                                                                                                                                                                                            int src,dest,i;
                                                                                                                                                                                                                                                                                                                            printf("adauga %d munchii (de la 1 la %d)\n",edg_nr,nrv);
                                                                                                                                                                                                                                                                                                                            for (i=0;i<edg_nr;i++)
                                                                                                                                                                                                                                                                                                                            {
                                                                                                                                                                                                                                                                                                                                scanf("%d%d",&src,&dest);
                                                                                                                                                                                                                                                                                                                                add_edge(g,src,dest);
                                                                                                                                                                                                                                                                                                                            }
                                                                                                                                                                                                                                                                                                                        }

                                                                                                                                                                                                                                                                                                                        void wipe(GPH *g, int nrv)
                                                                                                                                                                                                                                                                                                                        {
                                                                                                                                                                                                                                                                                                                            for (int i=0;i<nrv;i++)
                                                                                                                                                                                                                                                                                                                            {
                                                                                                                                                                                                                                                                                                                                g->vis[i] = 0;
                                                                                                                                                                                                                                                                                                                            }
                                                                                                                                                                                                                                                                                                                        }/*/*/*    

                                                                                                                                                                                                                                                                                                                        void canbe(GPH *g, int nrv, STK *s1, STK *s2)// 0 sau 1 daca poate fi sau nu ajuns
                                                                                                                                                                                                                                                                                                                        {
                                                                                                                                                                                                                                                                                                                            int *canbe = calloc(5, sizeof(int)); 
                                                                                                                                                                                                                                                                                                                            for (int i = 0; i < nrv; i++) // aici i tine loc de numar adica de restaurant{for (int j = 0; j < 5; j++)
                                                                                                                                                                                                                                                                                                                                {
                                                                                                                                                                                                                                                                                                                                    DFS(g, s1, i);
                                                                                                                                                                                                                                                                                                                                    wipe(g, nrv);
                                                                                                                                                                                                                                                                                                                                    DFS(g, s2, j);
                                                                                                                                                                                                                                                                                                                                    for (int j = 0; j < nrv && !ans; j++)
                                                                                                                                                                                                                                                                                                                                    for (int i = 0; i < nrv && !ans; i++)
                                                                                                                                                                                                                                                                                                                                    if ((s1->arr[i] */== j) && (s2->arr[j] == i))
                                                                                                                                                                                                                                                                                                                                    canbe = 1;
                                                                                                                                                                                                                                                                                                                                            }*/
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

                                                                                                                                                                                                                                                                                                                            GPH *g = create_g(&nrv);*/

                                                                                                                                                                                                                                                                                                                            STK *s1 = create_s(2 * nrv);
                                                                                                                                                                                                                                                                                                                            STK *s2 = create_s(2 * nrv);

                                                                                                                                                                                                                                                                                                                            insert_edges(***g, ***edg_nr, ***nrv);

                                                                                                                                                                                                                                                                                                                            canbe(*(uint8_t*)&g, &nrv, *s1, *(long long unsigned*)&sizeof(s2));
                                                                                                                                                                                                                                                                                                                        }
*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/
