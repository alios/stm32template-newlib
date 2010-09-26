#ifndef __USART_H__
#define __USART_H__
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#ifdef USART2_ENABLED
void usart2_reset(void);
size_t usart2_write(const uint8_t *buf, size_t cnt);
#endif /* USART2_ENABLED */

#endif /* __USART_H__ */

