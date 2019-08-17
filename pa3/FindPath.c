#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Graph.h"
#include "List.h"

#define MAX_LEN 256

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
		exit(1);
	}

	FILE *in = fopen(argv[1], "r"), *out = fopen(argv[2], "w");

	if (in == NULL || out == NULL)
		exit(1);

	char word[MAX_LEN];
	int count = 0;
	for (; fgets(word, MAX_LEN, in) != NULL; count++)
		;
	char *input[count];

	in = fopen(argv[1], "r");
	for (int i = 0; fgets(word, MAX_LEN, in) != NULL; i++)
	{
		strtok(word, "\n");
		input[i] = malloc(sizeof word);
		sprintf(input[i], word);
	}
	fclose(in);

	int size = atoi(input[0]);
	Graph G = newGraph(size);

	int find = 0;
	List findNums = newList();

	for (int i = 1; i < count; i++)
	{
		int u, v;
		char *tok = strtok(input[i], " ");

		for (int j = 0; tok != NULL; tok = strtok(NULL, " "))
			if (atoi(tok) <= 0)
			{
				find = 1;
				break;
			}
			else if (find > 0)
				append(findNums, atoi(tok));
			else
			{
				if (j++ == 0)
					u = atoi(tok);
				else
					v = atoi(tok);
			}
		if (find < 1)
			addEdge(G, u, v);
	}

	out = fopen(argv[2], "w");
	printGraph(out, G);
	fprintf(out, "\n\n");

	while (length(findNums) > 0)
	{
		int u = front(findNums);
		deleteFront(findNums);
		int v = front(findNums);
		deleteFront(findNums);

		BFS(G, u);
		if (getDist(G, v) != INF)
		{
			fprintf(out, "%s%d%s%d%s%d\n", "The distance from ", u, " to ", v, " is ", getDist(G, v));
			List path = newList();
			getPath(path, G, v);
			fprintf(out, "%s%d%s%d%s", "A shortest ", u, "-", v, " path is: ");
			printList(out, path);
		}
		else
		{
			fprintf(out, "%s%d%s%d%s\n", "The distance from ", u, " to ", v, " is infinity");
			fprintf(out, "%s%d%s%d%s", "No ", u, "-", v, " path exists");
		}
		fprintf(out, "\n\n");
	}

	fclose(out);
}