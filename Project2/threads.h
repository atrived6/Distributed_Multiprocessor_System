#include "q.h"

TCB_t* ReadyQ;
TCB_t* Curr_Thread;
int counter = 0;

void start_thread(void (*function)(void))
{
	void *stack = malloc(8192);
	TCB_t* newTCB = (TCB_t*)malloc(sizeof(TCB_t));
	init_TCB(newTCB, function, (void*)stack, 8192);
	++counter;
	newTCB->thread_id = counter;
	AddQueue(&ReadyQ, newTCB);
}

void run()
{
	Curr_Thread = DelQueue(&ReadyQ);
	ucontext_t parent;     // get a place to store the main context, for faking
	getcontext(&parent);   // magic sauce
	swapcontext(&parent, &(Curr_Thread->context));  // start the first thread
}

void yield()
{
	TCB_t* Prev_Thread;
	AddQueue(&ReadyQ, Curr_Thread);
	Prev_Thread = Curr_Thread;
	Curr_Thread = DelQueue(&ReadyQ);
	swapcontext(&(Prev_Thread->context), &(Curr_Thread->context));
}

// Test Function, delete it later
void PrintQ()
{
	if (ReadyQ == NULL)
	{
		printf("(Queue) Queue is empty!\n");
		return;
	}

	TCB_t *CurrentItem = ReadyQ;

	do
	{
		printf("(Queue) TCB Thread ID=%d\n", CurrentItem->thread_id);
		CurrentItem = CurrentItem->next;
	}
	while(CurrentItem != ReadyQ);
}

