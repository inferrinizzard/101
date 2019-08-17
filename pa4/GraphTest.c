//Sean Song ssong28 1649139 101 16.8 GraphTest.c main test file
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "List.h"
#include "Graph.h"

int main(void)
{
	int n = 8;
	List S = newList();
	Graph G = newGraph(n);

	for (int i = 1; i <= n; i++)
		append(S, i);

	printList(stdout, S);
	printf("\n%d\n", length(S));

	addArc(G, 1, 2);
	addArc(G, 2, 5);
	addArc(G, 5, 1);

	addArc(G, 3, 4);
	addArc(G, 4, 3);

	addArc(G, 6, 7);
	addArc(G, 7, 6);

	addArc(G, 8, 8);

	addArc(G, 2, 3);
	addArc(G, 2, 6);
	addArc(G, 3, 7);
	addArc(G, 4, 8);
	addArc(G, 5, 6);
	addArc(G, 7, 8);

	printGraph(stdout, G);

	List Sp = DFS(G, S);
	printList(stdout, Sp);
	printf("\n%d\n", length(Sp));

	Graph T = transpose(G);
	printGraph(stdout, T);

	Sp = DFS(T, Sp);
	printList(stdout, Sp);
	printf("\n");

	SCC(stdout, G, Sp);

	return 0;
}
