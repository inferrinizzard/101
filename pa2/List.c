//Sean Song CMPS101 pa1 25/6/19 README README
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "List.h"

typedef struct NodeObj
{
	int key;
	void *value;
	struct NodeObj *next, *prev;
} NodeObj;

typedef NodeObj *Node;

Node newNode(int k, void *v)
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

void *get(List L) { return L->ptr == NULL ? NULL : L->ptr->value; }

void clear(List L)
{
	// if (L == NULL)
	// {
	// 	fprvoid*f(stderr, "List Error: Calling makeEmpty() on NULL List reference\n");
	// 	exit(EXIT_FAILURE);
	// }

	while (L->size != 0)
		deleteFront(L);
	L->ptr = NULL;
}

void moveFront(List L) { L->ptr = L->size > 0 ? L->head : L->ptr; }

void moveBack(List L) { L->ptr = L->size > 0 ? L->tail : L->ptr; }

void movePrev(List L) { L->ptr = L->ptr != NULL ? L->ptr == L->head ? NULL : L->ptr->prev : L->ptr; }

void moveNext(List L) { L->ptr = L->ptr != NULL ? L->ptr == L->tail ? NULL : L->ptr->next : L->ptr; }

void prepend(List L, void *data)
{
	Node unshift = newNode(0, data);
	if (L->head != NULL)
	{
		L->head->prev = unshift;
		unshift->next = L->head;
		L->head = unshift;
		for (Node p = unshift->next; p != NULL; p = p->next)
			p->key++;
	}
	else
		L->head = L->tail = unshift;
	L->size++;
}

void append(List L, void *data)
{
	Node push = newNode(L->size, data);
	if (L->tail != NULL)
	{
		L->tail->next = push;
		push->prev = L->tail;
		L->tail = push;
	}
	else
		L->head = L->tail = push;
	L->size++;
	// printf("%.1f\n", *(double *)push->value);
}

void insertBefore(List L, void *data)
{
	if (L->ptr == L->head)
	{
		prepend(L, data);
		return;
	}
	Node insert = newNode(index(L), data);
	Node prev = L->ptr->prev;
	prev->next = insert;
	insert->prev = prev;
	insert->next = L->ptr;
	L->ptr->prev = insert;
	for (Node p = insert; p != NULL; p = p->next)
		p->key++;
	L->size++;
}

void insertAfter(List L, void *data)
{
	if (L->ptr == L->tail)
	{
		append(L, data);
		return;
	}
	Node insert = newNode(index(L), data);
	Node next = L->ptr->next;
	next->prev = insert;
	insert->next = next;
	insert->prev = L->ptr;
	L->ptr->next = insert;
	// for (Node p = insert->next; p != NULL; p = p->next)
	// 	p->key++;
	L->size++;
}

void *getAt(List L, int key)
{
	for (Node ptr = L->head; ptr != NULL; ptr = ptr->next)
		if (ptr->key == key)
			return ptr->value;
	return NULL;
}

void insertAt(List L, int key, void *data)
{
	Node insert = newNode(key, data);
	if (length(L) > 0)
	{
		if (key > L->tail->key)
		{
			L->tail->next = insert;
			insert->prev = L->tail;
			L->tail = insert;
		}
		else if (key < L->head->key)
		{
			L->head->prev = insert;
			insert->next = L->head;
			L->head = insert;
		}
		else
		{

			for (moveFront(L); index(L) != -1; moveNext(L))
				if (index(L) == key)
				{
					fprintf(stderr, "List Error: Calling insertAt() with duplicate key\n");
					exit(EXIT_FAILURE);
				}
			for (moveFront(L); index(L) < key && index(L) != -1; moveNext(L))
				;

			insert->prev = L->ptr->prev;
			L->ptr->prev->next = insert;
			L->ptr->prev = insert;
			insert->next = L->ptr;
		}
	}
	else
	{
		L->head = insert;
		L->tail = insert;
		L->ptr = insert;
	}
	L->size++;
}

void deleteFront(List L)
{
	Node del = L->head;
	if (del->next != NULL)
	{
		L->head = del->next;
		L->head->prev = NULL;
		// for (Node p = del->next; p != NULL; p = p->next)
		// 	p->key--;
	}
	if (L->ptr == del)
		L->ptr = NULL;
	freeNode(&del);
	// L->ptr = L->head;
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
	if (L->ptr == del)
		L->ptr = NULL;
	freeNode(&del);
	// L->ptr = L->tail;
	L->size--;
}

void delete (List L)
{
	if (L->ptr == L->head)
	{
		deleteFront(L);
		return;
	}
	if (L->ptr == L->tail)
	{
		deleteBack(L);
		return;
	}
	L->ptr->prev->next = L->ptr->next;
	L->ptr->next->prev = L->ptr->prev;
	freeNode(&(L->ptr));
	L->ptr = NULL;
	L->size--;
}
