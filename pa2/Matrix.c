//Sean Song 1649139 12B/M 13/5 Matrix.c main c file
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Matrix.h"
#include "List.h"

typedef struct EntryObj
{
	int key;
	double value;
	struct EntryObj *next, *prev;
} EntryObj;

typedef EntryObj *Entry;

Entry newEntry(int k, double v)
{
	Entry E = malloc(sizeof(EntryObj));
	assert(E != NULL);
	E->key = k;
	E->value = v;
	E->next = E->prev = NULL;
	return E;
}

void freeEntry(Entry *pE)
{
	if (pE != NULL && *pE != NULL)
	{
		free(*pE);
		*pE = NULL;
	}
}

// const static int rowSize = 101;

typedef struct MatrixObj
{
	List rows[101];
	int size;
} MatrixObj;

typedef MatrixObj *Matrix;

// Matrix newMatrix()
// {
// 	Matrix M = malloc(sizeof(MatrixObj));
// 	assert(M != NULL);
// 	for (int i = 0; i < rowSize; i++)
// 		M->rows[i] = NULL;
// 	M->size = 0;
// 	return M;
// }

Matrix newMatrix(int size)
{
	Matrix M = malloc(sizeof(MatrixObj));
	assert(M != NULL);
	printf("malloced\n");
	for (int i = 0; i <= size; i++)
		M->rows[i] = NULL;
	printf("lo0op\n");
	M->size = size;
	printf("set size\n");
	return M;
}

void freeMatrix(Matrix *pM)
{
	if (pM != NULL && *pM != NULL)
	{
		for (int i = 0; i <= (*pM)->size; i++)
			freeList(&(*pM)->rows[i]);

		free(*pM);
		*pM = NULL;
	}
}

int size(Matrix M)
{
	if (M == NULL)
	{
		fprintf(stderr, "Matrix Error: Calling size() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}
	return M->size;
}

int NNZ(Matrix M)
{
	if (M == NULL)
	{
		fprintf(stderr, "Matrix Error: Calling isEmpty() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}
	int count = 0;
	for (int i = 0; i < size(M); i++)
		if (M->rows[i] != NULL)
			count += length(M->rows[i]);
	return count;
}

int equals(Matrix A, Matrix B)
{
	if (size(A) != size(B))
		return 0;
	for (int i = 1; i <= size(A); i++)
	{
		if (length(A->rows[i]) != length(B->rows[i]))
			return 0;
		if (length(A->rows[i]) > 0 && length(B->rows[i]) > 0)
		{
			moveFront(A->rows[i]);
			moveFront(B->rows[i]);
			while (index(A->rows[i]) != -1)
			{
				if (((Entry)get(A->rows[i]))->value - ((Entry)get(B->rows[i]))->value > .01)
					return 0;
				moveNext(A->rows[i]);
				moveNext(B->rows[i]);
			}
		}
	}
	return 1;
}

void makeZero(Matrix M)
{
	if (M == NULL)
	{
		fprintf(stderr, "Matrix Error: Calling makeZero() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < size(M); i++)
		if (M->rows[i] != NULL)
			clear(M->rows[i]);
	M->size = 0;
}

void changeEntry(Matrix M, int i, int j, double x)
{
	if (M == NULL)
	{
		fprintf(stderr, "Matrix Error: Calling changeEntry() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}
	if ((10 * x) != 0)
	{
		if (M->rows[i] == NULL)
		{
			M->rows[i] = newList();
			// M->size++;
		}
		if (j > length(M->rows[i]) || getAt(M->rows[i], j) == NULL)
			insertAt(M->rows[i], j, newEntry(j, x));
		else
			((Entry)getAt(M->rows[i], j))->value = x;
	}
}

Matrix copy(Matrix M)
{
	Matrix C = newMatrix(size(M));
	for (int i = 1; i <= size(M); i++)
		if (M->rows[i] != NULL && length(M->rows[i]) > 0)
			for (moveFront(M->rows[i]); index(M->rows[i]) != -1; moveNext(M->rows[i]))
				changeEntry(C, i, index(M->rows[i]), ((Entry)get(M->rows[i]))->value);
	return C;
}

Matrix transpose(Matrix M)
{
	Matrix T = newMatrix(size(M));
	for (int i = 1; i <= size(M); i++)
		if (M->rows[i] != NULL)
			for (moveFront(M->rows[i]); index(M->rows[i]) != -1; moveNext(M->rows[i]))
				changeEntry(T, index(M->rows[i]), i, ((Entry)get(M->rows[i]))->value);
	return T;
}

Matrix scalarMult(double x, Matrix M)
{
	Matrix K = newMatrix(size(M));
	for (int i = 1; i <= size(M); i++)
		if (M->rows[i] != NULL)
			for (moveFront(M->rows[i]); index(M->rows[i]) != -1; moveNext(M->rows[i]))
				changeEntry(K, i, index(M->rows[i]), ((Entry)get(M->rows[i]))->value * x);
	return K;
}

Matrix sum(Matrix A, Matrix B)
{
	Matrix S = newMatrix(size(A) > size(B) ? size(A) : size(B));
	for (int i = 1; i <= (size(A) > size(B) ? size(A) : size(B)); i++)
		if (A->rows[i] != NULL && length(A->rows[i]) > 0 && B->rows[i] != NULL && length(B->rows[i]) > 0)
		{
			moveFront(A->rows[i]);
			moveFront(B->rows[i]);
			while (!(index(A->rows[i]) == -1 && index(B->rows[i]) == -1)) //not running until completion
				if (index(A->rows[i]) == index(B->rows[i]))
				{
					if ((10 * (((Entry)get(A->rows[i]))->value + ((Entry)get(B->rows[i]))->value)) != 0)
						changeEntry(S, i, index(A->rows[i]), ((Entry)get(A->rows[i]))->value + ((Entry)get(B->rows[i]))->value);
					moveNext(A->rows[i]);
					if (A->rows[i] != B->rows[i])
						moveNext(B->rows[i]);
				}
				else if (index(B->rows[i]) == -1 || (index(A->rows[i]) != -1 && ((Entry)get(A->rows[i]))->key < ((Entry)get(B->rows[i]))->key))
				{
					changeEntry(S, i, index(A->rows[i]), ((Entry)get(A->rows[i]))->value);
					moveNext(A->rows[i]);
				}
				else if (index(A->rows[i]) == -1 || ((Entry)get(B->rows[i]))->key < ((Entry)get(A->rows[i]))->key)
				{
					changeEntry(S, i, index(B->rows[i]), ((Entry)get(B->rows[i]))->value);
					moveNext(B->rows[i]);
				}
		}
		else if (A->rows[i] == NULL && B->rows[i] == NULL)
			continue;
		else if (A->rows[i] == NULL || length(A->rows[i]) == 0)
			for (moveFront(B->rows[i]); index(B->rows[i]) != -1; moveNext(B->rows[i]))
				changeEntry(S, i, index(B->rows[i]), ((Entry)get(B->rows[i]))->value);
		else if (B->rows[i] == NULL || length(B->rows[i]) == 0)
			for (moveFront(A->rows[i]); index(A->rows[i]) != -1; moveNext(A->rows[i]))
				changeEntry(S, i, index(A->rows[i]), ((Entry)get(A->rows[i]))->value);
	return S;
}

Matrix diff(Matrix A, Matrix B) { return sum(A, scalarMult(-1, B)); }

double dot(List row, List col)
{
	double product = 0;
	// for (moveFront(row); index(row) != -1; moveNext(row))
	// 	printf("(%d,%.1f) ", index(row), ((Entry)get(row))->value);
	// printf("\n");
	// for (moveFront(col); index(col) != -1; moveNext(col))
	// 	printf("(%d,%.1f) ", index(col), ((Entry)get(col))->value);
	// printf("\n");
	if (row != NULL && col != NULL)
	{
		moveFront(row);
		moveFront(col);
		while (index(row) != -1 || index(col) != -1)
			if (index(row) == -1)
				moveNext(col);
			else if (index(col) == -1)
				moveNext(row);
			else if (index(row) == index(col))
			{
				product += ((Entry)get(row))->value * ((Entry)get(col))->value;
				moveNext(row);
				if (row != col)
					moveNext(col);
			}
			else if (((Entry)get(row))->key < ((Entry)get(col))->key)
				moveNext(row);
			else if (((Entry)get(col))->key < ((Entry)get(row))->key)
				moveNext(col);
	}
	return product;
}

Matrix product(Matrix A, Matrix B)
{
	Matrix T = transpose(B);
	Matrix P = newMatrix(size(A) > size(B) ? size(A) : size(B));
	// printMatrix(stdout, A);
	// printMatrix(stdout, T);
	for (int i = 1; i <= (size(A) > size(T) ? size(A) : size(T)); i++)
		for (int j = 1; j <= (size(A) > size(T) ? size(A) : size(T)); j++)
			changeEntry(P, i, j, dot(A->rows[i], T->rows[j]));
	return P;
}

void printMatrix(FILE *out, Matrix M)
{
	if (M == NULL)
	{
		fprintf(stderr, "Matrix Error: Calling print() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i <= size(M); i++)
	{
		if (M->rows[i] != NULL && length(M->rows[i]) > 0)
		{
			fprintf(out, "%d:", i);
			for (moveFront(M->rows[i]); index(M->rows[i]) != -1; moveNext(M->rows[i]))
				fprintf(out, " (%d, %.1f)", ((Entry)get(M->rows[i]))->key, ((Entry)get(M->rows[i]))->value);
			fprintf(out, "\n");
		}
	}
}
