
//	Compile Command: gcc thread_test.c
//
#define _GNU_SOURCE
#include <unistd.h>
#include <stdio.h>
#include "threads.h"

int Global = 0;
//#define TEST

void Function1()
{
	int Local = 0;

	while(1)
	{
		printf("Function 1 (Global=%d Local=%d) Incrementing Global and Local..\n", Global, Local);
		++Global;
		++Local;
		sleep(1);
		printf("Function 1 (Global=%d Local=%d) Yielding\n", Global, Local);
		sleep(1);
		yield();
		printf("Function 1 (Global=%d Local=%d) Remainder\n", Global, Local);
		sleep(1);
		yield();
	}
}

void Function2()
{
	int Local = 0;

	while(1)
	{
		printf("Function 2 (Global=%d Local=%d) Incrementing Global and Local..\n", Global, Local);
		++Global;
		++Local;
		sleep(1);
		printf("Function 2 (Global=%d Local=%d) Yielding\n", Global, Local);
		sleep(1);
		yield();
		printf("Function 2 (Global=%d Local=%d) Remainder\n", Global, Local);
		sleep(1);
		yield();
	}
}

void Function3()
{
	int Local = 0;

	while(1)
	{
		printf("Function 3 (Global=%d Local=%d) Incrementing Global and Local..\n", Global, Local);
		++Global;
		++Local;
		sleep(1);
		printf("Function 3 (Global=%d Local=%d) Yielding\n", Global, Local);
		sleep(1);
		yield();
		printf("Function 3 (Global=%d Local=%d) Remainder\n", Global, Local);
		sleep(1);
		yield();
	}
}

// Test function, delete this later
// Tests the Queue
void Test()
{
	ReadyQ = newQueue();

	TCB_t* Item0 = (TCB_t*)malloc(sizeof(TCB_t));
	TCB_t* Item1 = (TCB_t*)malloc(sizeof(TCB_t));
	TCB_t* Item2 = (TCB_t*)malloc(sizeof(TCB_t));
	TCB_t* Item3 = (TCB_t*)malloc(sizeof(TCB_t));
	TCB_t* DeletedItem;
	Item0->thread_id = 1;
	Item1->thread_id = 2;
	Item2->thread_id = 3;
	Item3->thread_id = 999;

	printf("Add 3 items to the Queue:\n");
	AddQueue(&ReadyQ, Item0);
	AddQueue(&ReadyQ, Item1);
	AddQueue(&ReadyQ, Item2);
	PrintQ();
	printf("--------------------------------------------------------\n");

	printf("Delete 1 item from the front of the Queue:\n");
	DeletedItem = DelQueue(&ReadyQ);
	printf("Deleted Item has Thread ID=%d\n", DeletedItem->thread_id);
	PrintQ();
	printf("--------------------------------------------------------\n");

	printf("Add 1 item to the Queue:\n");
	AddQueue(&ReadyQ, Item3);
	PrintQ();
	printf("--------------------------------------------------------\n");

	printf("Delete 2 items from the front of the Queue:\n");
	DeletedItem = DelQueue(&ReadyQ);
	printf("Deleted Item has Thread ID=%d\n", DeletedItem->thread_id);
	DeletedItem = DelQueue(&ReadyQ);
	printf("Deleted Item has Thread ID=%d\n", DeletedItem->thread_id);
	PrintQ();
	printf("--------------------------------------------------------\n");

	printf("Delete 1 item from the front of the Queue:\n");
	DeletedItem = DelQueue(&ReadyQ);
	printf("Deleted Item has Thread ID=%d\n", DeletedItem->thread_id);
	PrintQ();

	printf("--------------------------------------------------------\n");
	printf("Delete 1 item from an empty Queue:\n");
	DeletedItem = DelQueue(&ReadyQ);
	printf("This should not be printed\n");
}

int main(int argc, char *argv[])
{
#ifndef TEST
	ReadyQ = newQueue();
	start_thread(Function1);
	start_thread(Function2);
	start_thread(Function3);
	run();
#else
	Test();
#endif
	return 0;
}

