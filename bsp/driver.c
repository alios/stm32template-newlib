#include <stdlib.h>
#include <stdbool.h>

#include "driver.h"

void enable_clocks(const driver_t* drv_p)
{
	if (drv_p->ahb_periph_clocks != 0)
		RCC_AHBPeriphClockCmd(drv_p->ahb_periph_clocks, ENABLE);
	if (drv_p->apb1_periph_clocks != 0)
		RCC_APB1PeriphClockCmd(drv_p->apb1_periph_clocks, ENABLE);
	if (drv_p->apb1_periph_clocks != 0)
		RCC_APB2PeriphClockCmd(drv_p->apb2_periph_clocks, ENABLE);
}

