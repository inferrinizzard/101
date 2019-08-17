//Sean Song ssong28 1649139 101 16.8 Graph.h main ADT h file

#ifndef _GRAPH_H_INCLUDE_
#define _GRAPH_H_INCLUDE_
#endif

#include "List.h"

#define UNDEF -1
#define NIL 0

typedef struct GraphObj *Graph;
/*** Constructors-Destructors ***/
Graph newGraph(int n);
void freeGraph(Graph *pG);
/*** Access functions ***/
int getOrder(Graph G);
int getSize(Graph G);
int getSource(Graph G);
int getParent(Graph G, int u);
int getDiscover(Graph G, int u);
int getFinish(Graph G, int u);
void getPath(List L, Graph G, int u);
/*** Manipulation procedures ***/
void makeNull(Graph G);
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
List DFS(Graph G, List);
int visit(Graph G, int x, int t, List);
void SCC(FILE *out, Graph G, List S);
void sccPrint(List L, Graph G, int x);
/*** Other operations ***/
Graph transpose(Graph);
Graph copyGraph(Graph);
void printGraph(FILE *out, Graph G);