#ifndef __DRIVER_H__
#define __DRIVER_H__

#include <stm32f10x.h>

typedef struct driver
{
	const char* driver_name;
	void (*driver_reset)();
	const uint32_t ahb_periph_clocks;
	const uint32_t apb1_periph_clocks;
	const uint32_t apb2_periph_clocks;
} driver_t;


#endif /* __DRIVER_H__ */
