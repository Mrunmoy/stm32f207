#ifndef  _KERNEL_H_
#define  _KERNEL_H_


#include <stdint.h>
#include "stm32f2xx.h"                  // Device header

void    KernelLaunch(uint32_t quanta);
void    KernelInit(void);
uint8_t KernelAddThreads(void(*task0)(void), 
	                       void(*task1)(void), 
												 void(*task2)(void));

#endif /* _KERNEL_H_ */ 
