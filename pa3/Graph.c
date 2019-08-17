//Sean Song 1649139 12B/G 13/5 Graph.c main c file
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"
#include "List.h"

typedef struct GraphObj
{
	List verts[101];
	char colour[101];
	int parent[101], dist[101];
	int size, order, s, capacity;
} GraphObj;

typedef GraphObj *Graph;

Graph newGraph(int n)
{
	Graph G = malloc(sizeof(GraphObj));
	assert(G != NULL);
	for (int i = 0; i <= n; i++)
	{
		G->verts[i] = NULL;
		G->parent[i] = NIL;
		G->dist[i] = INF;
		G->colour[i] = 'w';
	}
	G->size = 0;
	G->order = 0;
	G->s = 0;
	G->capacity = n;
	return G;
}

void freeGraph(Graph *pG)
{
	if (pG != NULL && *pG != NULL)
	{
		for (int i = 1; i <= (*pG)->order; i++)
			freeList(&(*pG)->verts[i]);
		*pG = NULL;
	}
}

int getSize(Graph G)
{
	if (G == NULL)
	{
		fprintf(stderr, "Graph Error: Calling size() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	return G->size;
}

int getOrder(Graph G)
{
	if (G == NULL)
	{
		fprintf(stderr, "Graph Error: Calling order() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	return G->order;
}

int getSource(Graph G)
{
	if (G == NULL)
	{
		fprintf(stderr, "Graph Error: Calling size() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	return G->s;
}

int getParent(Graph G, int u)
{
	if (G == NULL)
	{
		fprintf(stderr, "Graph Error: Calling parent() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	return G->parent[u];
}

int getDist(Graph G, int u)
{
	if (G == NULL)
	{
		fprintf(stderr, "Graph Error: Calling dist() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	return G->dist[u];
}

void getPath(List L, Graph G, int u)
{
	if (getSource(G) == 0)
	{
		fprintf(stderr, "%s\n", "G does not have a source");
		return;
	}
	if (G->verts[G->s] == NULL || length(G->verts[G->s]) == 0)
	{
		append(L, NIL);
		// printList(stdout, L);
		// printf("\n");
		return;
	}

	if (getParent(G, u) > 0)
		getPath(L, G, getParent(G, u));
	append(L, u);
	// printList(stdout, L);
	// printf("\n");
}

void makeNull(Graph G)
{
	if (G == NULL)
	{
		fprintf(stderr, "Graph Error: Calling makeNull() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < G->size; i++)
		clear(G->verts[i]);
	G->order = 0;
}

void addEdge(Graph G, int u, int v)
{
	addArc(G, u, v);
	addArc(G, v, u);
	G->size--;
}

void addArc(Graph G, int u, int v)
{
	if (G->verts[u] == NULL || G->verts[v] == NULL)
	{
		*(G->verts[u] == NULL ? &G->verts[u] : &G->verts[v]) = newList();
		G->order++;
	}
	if (length(G->verts[u]) == 0 || v > back(G->verts[u]))
		append(G->verts[u], v);
	else if (v < front(G->verts[u]))
		prepend(G->verts[u], v);
	else
	{
		for (moveFront(G->verts[u]); index(G->verts[u]) != -1; moveNext(G->verts[u]))
			if (get(G->verts[u]) > v)
			{
				insertBefore(G->verts[u], v);
				return;
			}
		append(G->verts[u], v);
	}

	G->size++;
}

void BFS(Graph G, int s)
{
	if (s > G->capacity)
		return;
	for (int i = 0; i <= G->capacity; i++)
	{
		G->colour[i] = 'w';
		G->parent[i] = NIL;
		G->dist[i] = INF;
	}
	G->s = s;
	G->colour[s] = 'g';
	G->dist[s] = 0;
	List Q = newList();
	append(Q, s);
	while (length(Q) > 0)
	{
		int x = front(Q);
		deleteFront(Q);
		if (length(Q) == 0)
			Q = newList();
		if (G->verts[x] != NULL)
			for (moveFront(G->verts[x]); index(G->verts[x]) != -1; moveNext(G->verts[x]))
				if (G->colour[get(G->verts[x])] == 'w')
				{
					int y = get(G->verts[x]);
					G->colour[y] = 'g';
					G->dist[y] = G->dist[x] + 1;
					G->parent[y] = x;
					append(Q, y);
				}
		G->colour[x] = 'b';
	}
}

void printGraph(FILE *out, Graph G)
{
	if (G == NULL)
	{
		fprintf(stderr, "Graph Error: Calling print() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	for (int i = 1; i <= G->capacity; i++)
		if (G->verts[i] != NULL && length(G->verts[i]) > 0)
		{
			fprintf(out, "%d: ", i);
			printList(out, G->verts[i]);
			fprintf(out, "\n");
		}
}
