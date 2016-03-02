.global init_ess_peripheral
.global init_ess_watchDogOff
.global init_ess_icacheOn
.global init_ess_intOff
.global init_ess_intOn

.equ periphral,0x70000000
.equ WATCON,0x7E004000
.equ iVIC0INTCLEAR,0x71200014
.equ iVIC1INTCLEAR,0x71300014

init_ess_peripheral:
	ldr r0,=periphral
	orr r0,r0,#0x13
	mcr p15,0,r0,c15,c2,4
	mov pc,lr

init_ess_watchDogOff:	
	ldr r0,=WATCON
	mov r1,#0
	str r1,[r0]
	mov pc,lr

init_ess_icacheOn:
	mrc p15,0,r0,c1,c0,0
#ifdef CONFIG_SYS_ICACHE_OFF
	bic r0,r0,#0x00001000
#else
	orr r0,r0,#0x00001000
#endif
	mcr p15,0,r0,c1,c0,0
	mov pc,lr

init_ess_intOff:
	mrs r0,cpsr
	orr r0,#0x60
	msr cpsr,r0
	ldr r0,=iVIC0INTCLEAR
	mvn r1,#0
	str r1,[r0]
	ldr r0,=iVIC1INTCLEAR
	str r1,[r0]
	mov pc,lr

init_ess_intOn:
	mrs r0,cpsr
	bic r0,#0x60
	msr cpsr,r0
	mov pc,lr
