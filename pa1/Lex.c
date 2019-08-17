//Sean Song CMPS101 pa1 25/6/19 README README
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"
// #include "List.c"

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

	List lex = newList();
	for (int i = 0; i < count; i++)
		if (length(lex) < 1)
			append(lex, i);
		else
		{
			moveFront(lex);
			if (strcmp(input[get(lex)], input[i]) > 0)
				prepend(lex, i);
			else
			{
				while (strcmp(input[get(lex)], input[i]) < 0 && index(lex) != back(lex))
				{
					moveNext(lex);
					if (!(strcmp(input[get(lex)], input[i]) < 0))
					{
						movePrev(lex);
						break;
					}
				}
				insertAfter(lex, i);
			}
		}

	// printList(out, lex);
	for (moveFront(lex); index(lex) != -1; moveNext(lex))
		fprintf(out, "%s\n", input[get(lex)]);

	fclose(out);

	return 0;
}