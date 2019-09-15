#include "kernel.h"

#define QUANTA		(10)

static uint32_t c0, c1, c2;


void Task0(void) {
	while(1) {
		c0++;
	}
}


void Task1(void) {
	while(1) {
		c1++;
	}
}


void Task2(void) {
	while(1) {
		c2++;
	}
}


int main(void) {
	c0 = c1 = c2 = 0;
	
	KernelInit();
	KernelAddThreads(&Task0, &Task1, &Task2);
	KernelLaunch(QUANTA);
}

