#include <stdint.h>
#include <stdio.h>
#include <malloc.h>

#include <stm32f10x.h>

int main(void)
{
	fprintf(stdout, "hello world!");
	putchar('a');
	for(;;);
}

