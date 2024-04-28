/*Determinati daca exista sau nu drum direct intre doua
restaurante dintr-o retea de tip graf*/
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int data;
	struct Node *next;
}
/// pentru simplitate, folosim int uri pt a numi restaurantel/locatiile
/// ex: 1 - restaurantul 1 si tot asa

NODE;

typedef struct graf {
	int nmb_vertices;
	int *visited;
	struct Node **adj_list;
} GPH;

// stack
typedef struct s {
	int top;
	int cap;
	int *arr;
} STK;

NODE *create_node(int restaurant)
{
	NODE *node = malloc(sizeof(NODE));
	node->data = restaurant;
	node->next = NULL;
	return node;
}

void add_edge(GPH *graph, int src, int dest)
{
	NODE *node = create_node(dest);
	node->next = graph->adj_list[src];
	graph->adj_list[src] = node;
	
	node = create_node(src);
	node->next = graph->adj_list[dest];
	graph->adj_list[dest] = node;
}

GPH *create_graph(int nmb_vertices)
{
	GPH *graph = malloc(sizeof(GPH));

	graph->nmb_vertices = nmb_vertices;

	graph->adj_list = calloc(nmb_vertices+1, sizeof(NODE *));
	graph->visited = calloc(nmb_vertices+1, sizeof(int));

	// initial for is now useless using calloc

	return graph;
}

STK *create_stack(int stk_cap)
{
	STK *s = malloc(sizeof(STK));
	s->arr = malloc(stk_cap * sizeof(int));
	s->top = -1;
	s->cap = stk_cap;

	return s;
}

void push(int pshd, STK *s)
{
	s->top = s->top + 1;
	s->arr[s->top] = pshd;
}

void DFS(GPH *graph, STK *dfs_order, int vortex_nr)
{
	NODE *adj_list = graph->adj_list[vortex_nr];
	NODE *aux = adj_list;
	graph->visited[vortex_nr] = 1;
	push(vortex_nr, dfs_order);

	while (aux) {
		int next_vortex = aux->data;
		if (graph->visited[next_vortex] == 0)
			DFS(graph, dfs_order, next_vortex);
		aux = aux->next;
	}
}

void insert_edges(GPH *graph, int edg_nr, int nmb_vertices)
{
	int src, dest, i;
	printf("adauga %d munchii (de la 1 la %d)\n", edg_nr, nmb_vertices);
	for (i = 0; i < edg_nr; i++) {
		scanf("%d%d", &src, &dest);
		add_edge(graph, src, dest);
	}
}

void wipe(GPH *g, int nrv)
{
	for (int i = 0; i < nrv; i++) {
		g->visited[i] = 0;
	}
}

int canbe(GPH *graf, int nmb_vertices, STK *s1,
		  STK *s2, int vortex_src, int vortex_dest)	// 0 sau 1 daca poate fi sau nu ajuns
{
	int ans = 0;
	DFS(graf, s1, vortex_src);
	wipe(graf, nmb_vertices);
	DFS(graf, s2, vortex_dest);
	wipe(graf, nmb_vertices);

	for (int j = 0; j < nmb_vertices && !ans; j++)
		for (int i = 0; i < nmb_vertices && !ans; i++)
			if ((s1->arr[i] == vortex_dest) || (s2->arr[j] == vortex_src))
				ans = 1;

	s1->top = -1;
	s2->top = -1;
	return ans;
}

int main()
{
	int nmb_vertices;
	int edg_nr;
	int vortex_1;
	int vortex_2;
	int ans;
	char y = 'y';

	printf("cate noduri are graful? ");
	scanf("%d", &nmb_vertices);

	printf("cate muchii are graful? ");
	scanf("%d", &edg_nr);

	GPH *graph = create_graph(nmb_vertices);
	STK *s1 = create_stack(2 * nmb_vertices);
	STK *s2 = create_stack(2 * nmb_vertices);

	insert_edges(graph, edg_nr, nmb_vertices);
	
	while(y == 'y'){
		
		printf("\nIntre ce restaurante căutăm drum?\n");
		scanf("%d%*c%d%*c", &vortex_1, &vortex_2);
		ans = canbe(graph, nmb_vertices, s1, s2, vortex_1, vortex_2);

		if(ans == 0)
			printf("nu");

		printf(" există drum \n");

		printf(" Alta pereche de restaurante? y/n: ");
		scanf("%c", &y);
	}
}
