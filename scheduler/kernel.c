

// Sccheduler
// TCB
// Stack

#include "kernel.h"

#define SYSPRI3		(*((volatile uint32_t *)0xE000ED20))

#define NUM_OF_THREADS (3)
#define STACKSIZE			 (100)

#define BUS_FREQ				(16000000)


typedef struct tcb_t {
	int32_t *stack;
	struct tcb_t *next;
}tcb_t;

tcb_t tcbs[NUM_OF_THREADS];
tcb_t *current_tcb;



static uint32_t MILLIS_PRESCALER;
static int32_t TCB_STACK[NUM_OF_THREADS][STACKSIZE];


void SchedulerLaunch(void);



static void KernelStackInit(int i) {
	tcbs[i].stack = &TCB_STACK[i][STACKSIZE-16];
	TCB_STACK[i][STACKSIZE-1] = 0x01000000;
}


void    KernelLaunch(uint32_t quanta) {
	SysTick->CTRL = 0;
	SysTick->VAL = 0;
	SYSPRI3 = (SYSPRI3 & 0x00FFFFFF) | 0xE0000000; // Priority 7
	
	SysTick->LOAD = (quanta*MILLIS_PRESCALER) - 1;
	SysTick->CTRL = 0x00000007; // set to use bus clock
	
	SchedulerLaunch();
}

void    KernelInit(void) {
	__disable_irq();	
	
	MILLIS_PRESCALER = BUS_FREQ/1000;
	
}


uint8_t KernelAddThreads(void(*task0)(void), void(*task1)(void), void(*task2)(void)) {
	__disable_irq();

	tcbs[0].next = &tcbs[1];
	tcbs[1].next = &tcbs[2];
	tcbs[2].next = &tcbs[0];

	KernelStackInit(0);
	TCB_STACK[0][STACKSIZE-2] = (int32_t)task0;

	KernelStackInit(1);
	TCB_STACK[1][STACKSIZE-2] = (int32_t)task1;

	KernelStackInit(2);
	TCB_STACK[2][STACKSIZE-2] = (int32_t)task2;
	
	current_tcb = &tcbs[0];
	
	__enable_irq();
	
	return 1;
}
