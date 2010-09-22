.cpu cortex-m3
.fpu softvfp

.syntax unified
	
.extern SVC_Handler_main

.text	
.thumb
	
	
.global SVC_Handler
.func SVC_Handler	
.thumb_func
SVC_Handler:	
  TST	lr, #4
  ITE   EQ
  MRSEQ	r0, MSP
  MRSNE r0, PSP
  B     SVC_Handler_main
.endfunc
	
.end

