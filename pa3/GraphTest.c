#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "List.h"
#include "Graph.h"

int main(void)
{
	int n = 35;
	// 	Graph G = newGraph(n);

	// addEdge(G, 1, 2);
	// addEdge(G, 1, 4);
	// addEdge(G, 1, 3);

	// printGraph(stdout, G);
	// exit(0);
	// addEdge(G, 1, 3);
	// addEdge(G, 2, 4);
	// addEdge(G, 2, 5);
	// addEdge(G, 2, 6);
	// addEdge(G, 3, 4);
	// addEdge(G, 4, 5);
	// addEdge(G, 5, 6);
	// addEdge(G, 6, 7);
	// addEdge(G, 8, 7);
	// addEdge(G, 8, 9);
	// addEdge(G, 10, 9);
	// addEdge(G, 10, 11);
	// addEdge(G, 8, 11);
	Graph G = newGraph(n);

	for (int i = 1; i < n; i++)
	{
		if (i % 7 != 0)
			addEdge(G, i, i + 1);
		if (i <= 28)
			addEdge(G, i, i + 7);
	}
	addEdge(G, 9, 31);
	addEdge(G, 17, 13);
	addEdge(G, 14, 33);

	printGraph(stdout, G);

	printf("%s%d\n", "G has order: ", getOrder(G));
	printf("%s%d\n", "G has size: ", getSize(G));

	// printf("%s\n", "printing?");
	// printGraph(stdout, G);
	// printf("%s\n", "printed?");

	// printf("%s\n", "start BFS");
	// BFS(G, 1);
	// printf("%s\n", "BFS done");

	List E = newList();

	for (int s = 1; s <= n; s++)
	{
		BFS(G, s);
		int max = getDist(G, 1);
		if (s == 13 || s == 17 || s == 18 || 2 == 24 || s == 25 || s == 31 || s == 32 || s == 33)
			printf("%d ", max);
		for (int i = 2; i <= n; i++)
		{
			int d = getDist(G, i);
			max = (max < d ? d : max);
			if (s == 13 || s == 17 || s == 18 || 2 == 24 || s == 25 || s == 31 || s == 32 || s == 33)
				printf("%d:%d ", max, i);
		}
		if (s == 13 || s == 17 || s == 18 || 2 == 24 || s == 25 || s == 31 || s == 32 || s == 33)
			printf("\n");
		append(E, max);
	}

	printList(stdout, E);
	printf("\n");

	List C = newList(), P = newList();

	append(C, 1);
	append(P, 1);
	int min = front(E), max = front(E);
	moveFront(E);
	moveNext(E);
	for (int i = 2; i <= n; i++)
	{
		int d = get(E);
		if (d == min)
			append(C, i);
		else if (d < min)
		{
			min = d;
			clear(C);
			append(C, i);
		}
		if (d == max)
			append(P, i);
		else if (d > max)
		{
			max = d;
			clear(P);
			append(P, i);
		}
		moveNext(E);
	}

	printf("%s%d %s%d\n", "min: ", min, "max: ", max);
	printList(stdout, C);
	printf("\n");
	printList(stdout, P);
	printf("\n");

	// int nums[8] = {13, 17, 18, 24, 25, 31, 32, 33};
	// for (int i = 0; i < 8; i++)
	// {
	// 	BFS(G, nums[i]);
	// 	printf("dist:");
	// 	for (int j = 0; j <= n; j++)
	// 		printf(" [%d:%d]", j, getDist(G, j));
	// 	printf("\n");
	// }

	printf("%s%d\n", "G has source: ", getSource(G));
	printf("%s%d\n", "source has parent: ", getParent(G, getSource(G)));

	int source = getSource(G);
	int test = 11;

	printf("%s%d%s%d%s%d\n", "The distance from ", source, " to ", test, " is ", getDist(G, test));
	List path = newList();
	getPath(path, G, test);
	printf("%s%d%s%d%s", "A shortest ", source, "-", test, " path is: ");
	printList(stdout, path);

	return 0;
}
