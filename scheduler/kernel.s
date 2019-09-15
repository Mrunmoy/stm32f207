			AREA |.text|,CODE,READONLY,ALIGN=2
			THUMB
			EXTERN current_tcb
			EXPORT SysTick_Handler
			EXPORT SchedulerLaunch

SysTick_Handler						; auto saves r0, r1, r2, r3, r12, lr, pc, psr
	CPSID		I
	PUSH		{R4-R11} 			; save r4, r5, r6, r7, r8, r9, r10, r11
	LDR			R0,=current_tcb		; R0 points to current_tcb
	LDR			R1,[R0]				; R1 = current_tcb
	STR			SP,[R1]				; save stack pointer
									; load next context
	LDR			R1,[R1,#4]			; navigate to second entry in tcb, current_tcb->next
	STR			R1,[R0]				; current_tcb = r1
	LDR			SP,[R1]				; load stack pointer of new thread, SP = current_tcb->stack
	POP			{R4-R11}			; pop top of stack
	CPSIE		I					; enable interrupt
	BX			LR					; restore auto stack registers and return
	

SchedulerLaunch
	LDR			R0,=current_tcb		; R0 points to current_tcb
	LDR			R2,[R0]				; R2 = current_tcb
	LDR			SP,[R2]				; SP = current_tcb->stack
	POP			{R4-R11}			; load from stack
	POP			{R0-R3}				;
	POP			{R12}				;
	ADD			SP,SP,#4			; Add 4 to stack pointer to skip LR
	POP			{LR}				; throw away the value from the stack pop operation
	ADD			SP,SP,#4			; Add 4 to skip PSR
	CPSIE		I					; enable interrupt
	BX			LR
	
	ALIGN
	END
	
