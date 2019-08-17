#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Matrix.h"

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

	int size = 0, aSize = 0, bSize = 0;
	char *token = strtok(input[0], " ");
	for (int j = 0; token != NULL; j++)
	{
		if (j == 0)
			size = atoi(token);
		else if (j == 1)
			aSize = atoi(token);
		else
			bSize = atoi(token);
		// printf("%s\n", token);
		token = strtok(NULL, " ");
	}
	// printf("%s\n", "read numlines");

	Matrix A = newMatrix(size);
	// printf("%s\n", "constructed A");
	Matrix B = newMatrix(size);
	// printf("%s\n", "constructed B");
	int b = 0;
	for (int i = 2; i < count; i++)
	{
		if (input[i][0] == '\n')
		{
			b = 1;
			continue;
		}
		int row, col;
		double data;
		char *tok = strtok(input[i], " ");
		// printf(tok);

		for (int j = 0; tok != NULL; j++)
		{
			if (j == 0)
				row = atoi(tok);
			else if (j == 1)
				col = atoi(tok);
			else
				data = atof(tok);
			// printf("%s\n", tok);
			tok = strtok(NULL, " ");
		}
		changeEntry((b ? B : A), row, col, data);
	}
	// printf("%s\n", "read file");

	// fill(A);
	// fill(B);

	fprintf(out, "%s%d%s\n", "A has ", aSize, " non-zero entries:");
	printMatrix(out, A);
	// printMatrix(stdout, A);
	printf("\n");
	// printf("%s\n", "printed A");

	fprintf(out, "\n%s%d%s\n", "B has ", bSize, " non-zero entries:");
	printMatrix(out, B);
	// printMatrix(stdout, B);
	printf("\n");
	// printf("%s\n", "printed B");

	Matrix C = scalarMult(1.5, A);
	fprintf(out, "\n%s\n", "(1.5)*A =");
	printMatrix(out, C);
	// printf("%s\n", "printed scale");
	freeMatrix(&C);

	Matrix D = sum(A, B);
	fprintf(out, "\n%s\n", "A+B =");
	printMatrix(out, D);
	// printf("%s\n", "printed sum1");
	freeMatrix(&D);

	Matrix E = sum(A, A);
	fprintf(out, "\n%s\n", "A+A =");
	printMatrix(out, E);
	// printf("%s\n", "printed sum2");
	freeMatrix(&E);

	Matrix F = diff(B, A);
	fprintf(out, "\n%s\n", "B-A =");
	printMatrix(out, F);
	// printf("%s\n", "printed diff");
	freeMatrix(&F);

	Matrix G = diff(A, A);
	fprintf(out, "\n%s\n", "A-A =");
	printMatrix(out, G);
	// printf("%s\n", "printed 0diff");
	freeMatrix(&G);

	Matrix H = transpose(A);
	fprintf(out, "\n%s\n", "Transpose(A) =");
	printMatrix(out, H);
	// printf("%s\n", "printed trans");
	freeMatrix(&H);

	Matrix I = product(A, B);
	fprintf(out, "\n%s\n", "A*B =");
	printMatrix(out, I);
	// printf("%s\n", "printed mult1");
	freeMatrix(&I);

	Matrix J = product(B, B);
	fprintf(out, "\n%s\n", "B*B =");
	printMatrix(out, J);
	// printf("%s\n", "printed mult2");
	freeMatrix(&J);

	freeMatrix(&A);
	freeMatrix(&B);

	fclose(out);
	return EXIT_SUCCESS;
}