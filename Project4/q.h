#include "TCB.h"
#include <stdlib.h>

//
//  returns a pointer to a new q-element, uses memory allocation
//
TCB_t* NewItem()
{
	TCB_t *Item = (TCB_t*)malloc(sizeof(TCB_t));
	return Item;
}

//
// creates a empty queue, that is the header pointer is set to null.
//
TCB_t* newQueue()
{
	return NULL;
}

//
// adds a queue item, pointed to by "item", to the queue pointed to by head.
//
void AddQueue(TCB_t** Head, TCB_t* Item)
{
	if (*Head != NULL)
	{
		Item->previous = (*Head)->previous;
		Item->next = *Head;

		(*Head)->previous->next = Item;
		(*Head)->previous = Item;
	}
	else
	{
		Item->next = Item;
		Item->previous = Item;
		*Head = Item;
	}

}

//
// deletes an item from head and returns a pointer to the deleted item.
// If the queue is already empty, flag error.
//
TCB_t* DelQueue(TCB_t **Head)
{
	if (*Head == NULL)
	{
		printf("DelQueue() Error: Queue is already empty. Exiting program.\n");
		exit(0);
	}

	TCB_t *DeleteItem;

	if ((*Head)->next == *Head)
	{
		DeleteItem = (*Head);
		*Head = NULL;
	}
	else
	{
		DeleteItem = (*Head);

		(*Head)->previous->next = (*Head)->next;
		(*Head)->next->previous = (*Head)->previous;

		*Head = (*Head)->next;
	}

	return DeleteItem;
}

