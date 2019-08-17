#include <stdio.h>
#include <stdlib.h>
#include "List.h"

int main(int argc, char *argv[])
{

	List A = newList();
	List B = newList();
	List C = newList();
	double X[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
	int i, equal = 0;
	double u = -1, v = -2;

	for (i = 1; i <= 20; i++)
	{
		append(A, &X[i]);
		prepend(B, &X[i]);
	}

	for (int j = front(A); j <= length(A); j++)
		printf("%d ", *(double *)getAt(A, j));
	printf("\n");
	for (int j = front(B); j <= length(B); j++)
		printf("%d ", *(double *)getAt(B, j));
	printf("\n");

	for (int j = back(A); j > front(A); j--)
		printf("%d ", *(double *)getAt(A, j));
	printf("\n");
	for (int j = back(B); j > front(B); j--)
		printf("%d ", *(double *)getAt(B, j));
	printf("\n");

	moveFront(A);
	while (index(A) >= 0)
	{
		append(C, get(A));
		moveNext(A);
	}

	for (int j = front(C); j <= length(C); j++)
		printf("%d ", *(double *)getAt(C, j));
	printf("\n");

	equal = (length(A) == length(C));
	moveFront(A);
	moveFront(C);
	while (index(A) >= 0 && equal)
	{
		equal = (get(A) == get(C));
		moveNext(A);
		moveNext(C);
	}
	printf("A equals C is %s\n", (equal ? "true" : "false"));

	moveFront(A);
	for (i = 0; i < 5; i++)
		moveNext(A);
	insertBefore(A, &u);
	for (i = 0; i < 9; i++)
		moveNext(A);
	insertAfter(A, &v);
	for (i = 0; i < 5; i++)
		movePrev(A);
	delete (A);

	for (int j = front(A); j <= length(A); j++)
		printf("%d ", *(double *)getAt(A, j));
	printf("\n");
	for (int j = back(A); j > front(A); j--)
		printf("%d ", *(double *)getAt(A, j));
	printf("\n");

	printf("%d\n", length(A));
	clear(A);
	printf("%d\n", length(A));

	freeList(&A);
	freeList(&B);
	freeList(&C);

	return (0);
}

/*
Output of this program:
1.0 2.0 3.0 4.0 5.0 6.0 7.0 8.0 9.0 10.0 11.0 12.0 13.0 14.0 15.0 16.0 17.0 18.0 19.0 20.0
20.0 19.0 18.0 17.0 16.0 15.0 14.0 13.0 12.0 11.0 10.0 9.0 8.0 7.0 6.0 5.0 4.0 3.0 2.0 1.0
20.0 19.0 18.0 17.0 16.0 15.0 14.0 13.0 12.0 11.0 10.0 9.0 8.0 7.0 6.0 5.0 4.0 3.0 2.0 1.0
1.0 2.0 3.0 4.0 5.0 6.0 7.0 8.0 9.0 10.0 11.0 12.0 13.0 14.0 15.0 16.0 17.0 18.0 19.0 20.0
1.0 2.0 3.0 4.0 5.0 6.0 7.0 8.0 9.0 10.0 11.0 12.0 13.0 14.0 15.0 16.0 17.0 18.0 19.0 20.0
A equals C is true
1.0 2.0 3.0 4.0 5.0 -1.0 6.0 7.0 8.0 9.0 11.0 12.0 13.0 14.0 15.0 -2.0 16.0 17.0 18.0 19.0 20.0
20.0 19.0 18.0 17.0 16.0 -2.0 15.0 14.0 13.0 12.0 11.0 9.0 8.0 7.0 6.0 -1.0 5.0 4.0 3.0 2.0 1.0
21
0
*/