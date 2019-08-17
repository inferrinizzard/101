//Sean Song ssong28 1649139 101 16.8 Graph.c main ADT file
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
	int parent[101], disc[101], fin[101];
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
		G->disc[i] = UNDEF;
		G->fin[i] = UNDEF;
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

int getDiscover(Graph G, int u)
{
	if (G == NULL)
	{
		fprintf(stderr, "Graph Error: Calling disc() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	return G->disc[u];
}

int getFinish(Graph G, int u)
{
	if (G == NULL)
	{
		fprintf(stderr, "Graph Error: Calling fin() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	return G->fin[u];
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

List DFS(Graph G, List S)
{
	if (length(S) < G->order)
	{
		fprintf(stderr, "Graph Error: List S does not contain right number of vertices for DFS\n");
		fprintf(stderr, "%s%d%s%d\n", "S has ", length(S), " and G has ", G->order);
		return NULL;
	}
	for (int i = 1; i <= length(S); i++)
	{
		G->colour[i] = 'w';
		G->parent[i] = NIL;
	}
	int time = 0;
	List dec = newList();
	for (moveFront(S); get(S) != -1; moveNext(S))
		if (G->colour[get(S)] == 'w')
			time = visit(G, get(S), time, dec);
	for (moveFront(dec); index(dec) != -1; moveNext(dec))
	{
		deleteFront(S);
		append(S, get(dec));
	}
	return dec;
}

int visit(Graph G, int x, int t, List L)
{
	int dtime = t;
	G->disc[x] = ++dtime;
	G->colour[x] = 'g';
	if (G->verts[x] != NULL)
		for (moveFront(G->verts[x]); index(G->verts[x]) != -1; moveNext(G->verts[x]))
			if (G->colour[get(G->verts[x])] == 'w')
			{
				int y = get(G->verts[x]);
				G->parent[y] = x;
				dtime = visit(G, y, dtime, L);
			}
	G->colour[x] = 'b';
	G->fin[x] = ++dtime;
	prepend(L, x);
	return dtime;
}

void SCC(FILE *out, Graph G, List S)
{
	for (int i = 1; i <= G->order; i++)
		G->colour[i] = 'w';

	List L = newList();
	int scc = 0;
	while (length(S) > 0)
	{
		int x = front(S);
		deleteFront(S);
		if (G->colour[x] == 'w')
		{
			scc++;
			sccPrint(L, G, x);
			append(L, 0);
		}
	}
	List newL = newList();
	for (moveFront(L); index(L) != -1; moveNext(L))
	{
		List sort = newList();
		if (get(L) == 0)
			moveNext(L);
		else
		{
			for (; get(L) > 0; moveNext(L))
				append(sort, get(L));
			append(sort, front(sort));
			deleteFront(sort);
			newL = concatList(newL, sort);
			append(newL, 0);
		}
		freeList(&sort);
	}

	fprintf(out, "%s%d%s%s", "G contains ", scc, " strongly connected component", scc == 1 ? ":" : "s:");
	int num = 1;
	for (moveBack(newL); index(newL) != -1; movePrev(newL))
		if (get(newL) == 0)
			fprintf(out, "\n%s%d%s", "Component ", num++, ":");
		else
			fprintf(out, " %d", get(newL));
	freeList(&L);
}

void sccPrint(List L, Graph G, int x)
{
	G->colour[x] = 'b';
	append(L, x);
	if (G->verts[x] != NULL && length(G->verts[x]) > 0)
		for (moveFront(G->verts[x]); index(G->verts[x]) != -1; moveNext(G->verts[x]))
			if (G->colour[get(G->verts[x])] == 'w')
				sccPrint(L, G, get(G->verts[x]));
}

Graph transpose(Graph G)
{
	Graph T = newGraph(G->order);
	for (int i = 1; i <= G->order; i++)
		for (moveFront(G->verts[i]); index(G->verts[i]) != -1; moveNext(G->verts[i]))
			addArc(T, get(G->verts[i]), i);
	return T;
}

Graph copyGraph(Graph G)
{
	Graph C = newGraph(G->order);
	for (int i = 1; i <= G->order; i++)
		for (moveFront(G->verts[i]); index(G->verts[i]) != -1; moveNext(G->verts[i]))
			addArc(C, i, get(G->verts[i]));
	return C;
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
		else
			fprintf(out, "%d:\n", i);
}
