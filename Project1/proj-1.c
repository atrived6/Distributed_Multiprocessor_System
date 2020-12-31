
//	Compile Command: gcc -pthread proj-1.c
//
#define _GNU_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "sem.h"

#define ARRAY_SIZE 3

semaphore_t g_Mutex;
semaphore_t g_AddMutex[ARRAY_SIZE];
semaphore_t g_PrintMutex;
int g_iArray[ARRAY_SIZE];
int g_AddCount = 0;

void ChildFunction(int *iChildIndex)
{
	while(1)
	{
		P(&g_AddMutex[*iChildIndex]);

		++g_iArray[*iChildIndex];

		P(&g_Mutex);

        	++g_AddCount;

		if (g_AddCount == ARRAY_SIZE)
		{
			// Unblock the parent from printing			
			V(&g_PrintMutex);
		}

		V(&g_Mutex);
	}
}

int main()
{
	int iChildID[3] = {0, 1, 2};

	init_sem(&g_Mutex, 1);
	init_sem(&g_PrintMutex,0);

	// Initialize the integer array with zero's
	// Start each child thread
	for(int ix = 0; ix < ARRAY_SIZE; ++ix)
	{
		g_iArray[ix] = 0;
		init_sem(&g_AddMutex[ix], 1);
		start_thread(ChildFunction, &iChildID[ix]);
	}

	while(1)
	{
		P(&g_PrintMutex);

		// Print out the values of the integer Array
		for(int ix = 0; ix < ARRAY_SIZE; ++ix)
		{
			printf("Array[%d] = %d\n", ix, g_iArray[ix]);
		}

		// Sleep a little bit, so the output is readable
		sleep(1);
 
		// Unblock the children from adding
		g_AddCount = 0;
		for(int ix = 0; ix < ARRAY_SIZE; ++ix)
		{
			V(&g_AddMutex[ix]);
		}
	}
}

