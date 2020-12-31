#include "threads.h"

//
// The semaphore is a counter and a queue of TCBs.
//
typedef struct Semaphore_t
{
	int Count;
	TCB_t* Queue;
} Semaphore_t;

//
// mallocs a semaphore structure, initializes it to the InitValue and returns
// the pointer to the semaphore.
//
Semaphore_t* CreateSem(int InputValue)
{
	Semaphore_t* sem = (Semaphore_t*)(malloc(sizeof(Semaphore_t)));
	sem->Count = InputValue;
	sem->Queue = newQueue();
	return sem;
}

//
// takes a pointer to a semaphore and performs P, i.e. decrements the
// semaphore, and if the value is less than zero then blocks the thread in the
// queue associated with the semaphore.
//
void P(Semaphore_t* sem)
{
	--sem->Count;
	if (sem->Count < 0)
	{
		TCB_t* Prev_Thread;
		AddQueue(&sem->Queue, Curr_Thread);
		Prev_Thread = Curr_Thread;
		Curr_Thread = DelQueue(&ReadyQ);
		swapcontext(&(Prev_Thread->context), &(Curr_Thread->context));
	}
}

//
// increments the semaphore, and if the value is 0 or negative, then takes a
// PCB out of the semaphore queue and puts it into the ReadyQ.
//
void V(Semaphore_t* sem)
{
	++sem->Count;
	if (sem->Count <= 0)
	{
		AddQueue(&ReadyQ, DelQueue(&sem->Queue));
	}
	yield();
}

