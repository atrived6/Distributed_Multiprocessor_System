#include <ucontext.h>
#include <string.h>

//
// The queue items used for handling the threads is the TCB_t.
//
typedef struct TCB_t
{
    struct TCB_t* next;
    struct TCB_t* previous;
    int thread_id;
    ucontext_t context;
} TCB_t;

//
// arguments to init_TCB are
// 1. pointer to the function, to be executed
// 2. pointer to the thread stack
// 3. size of the stack
//
void init_TCB (TCB_t *tcb, void *function, void *stackP, int stack_size)
{
	memset(tcb, '\0', sizeof(TCB_t));       // wash, rinse
	getcontext(&tcb->context);              // have to get parent context
	tcb->context.uc_stack.ss_sp = stackP;
	tcb->context.uc_stack.ss_size = (size_t)stack_size;
	makecontext(&tcb->context, function, 0);// context is now cooked
}

