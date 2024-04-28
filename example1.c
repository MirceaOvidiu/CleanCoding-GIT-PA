/*Determinati daca exista sau nu drum direct intre doua restaurante dintr-o retea de tip graf*/

#include <stdlib.h>
#include <stdio.h>

typedef struct Node{
    int data;
    struct Node *next;
} NODE;

/// pentru simplitate, folosim int uri pt a numi restaurantele/locatiile
/// ex: 1 - restaurantul 1 si tot asa                                                             

typedef struct g{
    int v;
    int *vis;
    NODE **alst;
} GPH;

typedef struct s{
    int t;
    int scap;
    int *arr;
} STK;

NODE *create_node(int v){
    NODE *nn = malloc(sizeof(NODE));
    nn->data = v;
    nn->next = NULL;
    return nn;
}

void add_edge(GPH *g , int src , int dest){
    NODE *nn = create_node(dest);
    nn->next = g->alst[src];
    g->alst[src] = nn;

   /* nn = create_node(src);
    nn->next = g->alst[dest];
    g->alst[dest] = nn;*/
}

GPH *create_g(int val){

    GPH *g = malloc(sizeof(GPH));

    g->v = val;
    g->alst = malloc(val * sizeof(NODE *));
    g->vis = malloc(val * sizeof(int));

    for (int i = 0 ; i < val; i++){
        g->alst[i] = NULL;
        g->vis[i] = 0;
    }

    return g;
}

STK *create_s(int scap){
    STK *s = malloc(sizeof(STK));
    s->arr = malloc(scap * sizeof(int));

    s->t = -1;
    s->scap = scap;

    return s;
}

void push(int pshd,STK *s){
    s->t = s->t + 1;
    s->arr[s->t] = pshd;
}

void DFS(GPH *g , int v_nr) {
    g->vis[v_nr] = 1;
    NODE *aux = g->alst[v_nr];


    while (aux != NULL){
        int con_ver = aux->data;
        if (g->vis[con_ver] == 0){
            DFS(g,con_ver);
        }
        aux = aux->next;
    }
}

void insert_edges(GPH *g , int edg_nr ,int nrv){
    int src,dest;
    printf("Adauga %d munchii (de la 1 la %d)\n",edg_nr,nrv);

    for (int i = 0; i < edg_nr; i++){
       scanf("%d %d",&src,&dest);
       add_edge(g,src,dest);
    }
}

void wipe(GPH *g){
    
    for (int i = 0; i < g->v; i++){
       g->vis[i] = 0;
    }
}


int canbe(GPH *g, int src, int dest){

    wipe(g);
    DFS(g,src);
    return g->vis[dest];
}

int main(void){
    
    int nrv;
    int edg_nr;
    int src,dest;


    printf("Cate noduri are graful?\n");
    scanf("%d", &nrv);\

    GPH *g = create_g(nrv);

    printf("Cate muchii are graful? \n");
    scanf("%d", &edg_nr);

    insert_edges(g,edg_nr,nrv);

    printf("Care restaurante va intereseaza: \n");
    scanf("%d %d", &src,&dest);
    
  

    if(canbe(g, src,dest))
        printf("Este drum intre restaurante.\n");
    else
        printf("Nu este drum intre restaurante. \n");

    return 0;

}
