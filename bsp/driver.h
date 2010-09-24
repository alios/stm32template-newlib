#ifndef __DRIVER_H__
#define __DRIVER_H__

#include <stm32f10x.h>

typedef struct driver {
  const char* driver_name;
  void (*driver_reset)(void);
  uint32_t ahb_periph_clocks;
  uint32_t apb1_periph_clocks;
  uint32_t apb2_periph_clocks;
} driver_t;


void enable_clocks(const driver_t* drv_p);

#endif /* __DRIVER_H__ */
