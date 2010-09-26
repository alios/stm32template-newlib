#include "stm32f10x_conf.h"
#include "ringbuffer.h"
#include "driver.h"
#include "usart.h"

#ifndef USART_BUFFER_SIZE
#define USART_BUFFER_SIZE 64
#endif /* USART_BUFFER_SIZE */

#ifdef USART1_ENABLED
static uint8_t _usart1rx_buffer[USART_BUFFER_SIZE];
static ringbuffer_t usart1_rx;
static uint8_t _usart1tx_buffer[USART_BUFFER_SIZE];
static ringbuffer_t usart1_tx;

static void usart1_reset(void)
{
	initRingBuffer(&usart1_rx, _usart1rx_buffer, USART_BUFFER_SIZE);
	initRingBuffer(&usart1_tx, _usart1tx_buffer, USART_BUFFER_SIZE);
}

const GPIO_InitTypeDef usart_gpios[] =
	{ { GPIO_Pin_10, GPIO_Speed_50MHz, GPIO_Mode_IN_FLOATING }
	, { GPIO_Pin_9, GPIO_Speed_50MHz, GPIO_Mode_AF_PP }
	};

const driver_t usart1_driver =
	{ "usart1"
	, usart1_reset
	, 0
	, 0
	, 0
	};


#endif /* USART1_ENABLED */

