#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "StringList.h"

typedef struct NodeObj
{
	int key;
	char *value;
	struct NodeObj *next, *prev;
} NodeObj;

typedef NodeObj *Node;

Node newNode(int k, char *v)
{
	Node N = malloc(sizeof(NodeObj));
	assert(N != NULL);
	N->key = k;
	N->value = v;
	N->next = N->prev = NULL;
	return N;
}

void freeNode(Node *pN)
{
	if (pN != NULL && *pN != NULL)
	{
		free(*pN);
		*pN = NULL;
	}
}

typedef struct ListObj
{
	NodeObj *head, *tail, *ptr;
	int size;
} ListObj;

typedef ListObj *List;

List newList()
{
	List L = malloc(sizeof(ListObj));
	assert(L != NULL);
	L->head = L->tail = L->ptr = NULL;
	L->size = 0;
	return L;
}

void freeList(List *pL)
{
	if (pL != NULL && *pL != NULL)
	{
		if (length(*pL) > 0)
			clear(*pL);
		free(*pL);
		*pL = NULL;
	}
}

int length(List L) { return L->size; }

int index(List L) { return L->ptr == NULL ? -1 : L->ptr->key; }

int front(List L) { return L->head->key; }

int back(List L) { return L->tail->key; }

char *get(List L) { return L->ptr == NULL ? "" : L->ptr->value; }

int equals(List A, List B)
{
	int aIndex = index(A);
	int bIndex = index(B);
	if (length(A) != length(B) || aIndex != bIndex)
		return 0;
	moveFront(A);
	moveFront(B);

	while (index(A) != -1)
	{
		if (strcmp(get(A), get(B)) != 0)
			return 0;
		moveNext(A);
		moveNext(B);
	}
	for (moveFront(A); index(A) != aIndex; moveNext(A))
		;
	for (moveFront(B); index(B) != bIndex; moveNext(B))
		;
	return 1;
}

void clear(List L)
{
	// if (L == NULL)
	// {
	// 	fprintf(stderr, "List Error: Calling makeEmpty() on NULL List reference\n");
	// 	exit(EXIT_FAILURE);
	// }

	while (L->size != 0)
		deleteFront(L);
}

void moveFront(List L) { L->ptr = L->size > 0 ? L->head : L->ptr; }

void moveBack(List L) { L->ptr = L->size > 0 ? L->tail : L->ptr; }

void movePrev(List L) { L->ptr = L->ptr != NULL ? L->ptr == L->head ? NULL : L->ptr->prev : L->ptr; }

void moveNext(List L) { L->ptr = L->ptr != NULL ? L->ptr == L->tail ? NULL : L->ptr->next : L->ptr; }

void prepend(List L, int key, char *data)
{
	Node unshift = newNode(key, data);
	if (L->head != NULL)
	{
		L->head->prev = unshift;
		unshift->next = L->head;
		L->head = unshift;
	}
	else
		L->head = L->tail = unshift;
	L->size++;
}

void append(List L, int key, char *data)
{
	Node push = newNode(key, data);
	if (L->tail != NULL)
	{
		L->tail->next = push;
		push->prev = L->tail;
		L->tail = push;
	}
	else
		L->head = L->tail = push;
	L->size++;
}

void insertBefore(List L, int key, char *data)
{
	if (L->ptr == L->head)
	{
		prepend(L, key, data);
		return;
	}
	Node insert = newNode(key, data);
	Node prev = L->ptr->prev;
	prev->next = insert;
	insert->prev = prev;
	insert->next = L->ptr;
	L->ptr->prev = insert;
	L->size++;
}

void insertAfter(List L, int key, char *data)
{
	if (L->ptr == L->tail)
	{
		append(L, key, data);
		return;
	}
	Node insert = newNode(key, data);
	Node next = L->ptr->next;
	next->prev = insert;
	insert->next = next;
	insert->prev = L->ptr;
	L->ptr->next = insert;
	L->size++;
}

void deleteFront(List L)
{
	Node del = L->head;
	if (del->next != NULL)
	{
		L->head = del->next;
		L->head->prev = NULL;
	}
	freeNode(&del);
	L->size--;
}

void deleteBack(List L)
{
	Node del = L->tail;
	if (del->prev != NULL)
	{
		L->tail = del->prev;
		L->tail->next = NULL;
	}
	freeNode(&del);
	L->size--;
}

void delete (List L)
{
	L->ptr->prev->next = L->ptr->next;
	L->ptr->next->prev = L->ptr->prev;
	freeNode(&(L->ptr));
	L->ptr = NULL;
	L->size--;
}

void printList(FILE *out, List L)
{
	for (Node ptr = L->head; ptr != NULL; ptr = ptr->next)
		// fprintf(out, "%s ", ptr->value);
		fprintf(out, "%s\n", ptr->value);
	// fprintf(out, "\n", "");

	// for (Node ptr = L->head; ptr != NULL; ptr = ptr->next)
	// 	fprintf(out, "%d ", ptr->key);
	// fprintf(out, "\n", "");
}

List copyList(List L)
{
	List copy = newList();
	for (Node ptr = L->head; ptr != NULL; ptr = ptr->next)
		append(copy, ptr->key, ptr->value);
	return copy;
}

List concatList(List A, List B)
{
	List concat = copyList(A);
	for (Node ptr = B->head; ptr != NULL; ptr = ptr->next)
		append(concat, ptr->key, ptr->value);
	return concat;
}