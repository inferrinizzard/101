//Sean Song ssong28 1649139 101 16.8 FindComponents.c main c file

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
			addArc(G, u, v);
	}

	out = fopen(argv[2], "w");
	fprintf(out, "%s\n", "Adjacency list representation of G:");
	printGraph(out, G);
	fprintf(out, "\n");

	List S = newList();
	for (int i = 1; i <= size; i++)
		append(S, i);
	SCC(out, G, DFS(transpose(G), DFS(G, S)));
	fprintf(out, "\n");
	fclose(out);
}