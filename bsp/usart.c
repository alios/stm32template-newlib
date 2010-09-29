#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include <semphr.h>

#include "stm32f10x_conf.h"
#include "usart.h"

#ifdef USART2_ENABLED

#ifndef USART2_BUFFER_SIZE
#define USART2_BUFFER_SIZE 16
#endif

static bool usart2_initialized = false;
uint32_t usart2_rx_counter = 0;
uint32_t usart2_tx_counter = 0;
xQueueHandle usart2_rxQueue = NULL;
xQueueHandle usart2_txQueue = NULL;

void usart2_init(void)
{
	assert_param(!usart2_initialized);

	usart2_rxQueue = xQueueCreate(USART2_BUFFER_SIZE, sizeof(uint8_t));
	usart2_txQueue = xQueueCreate(USART2_BUFFER_SIZE, sizeof(uint8_t));

	/* configure NVIC */
	{
		NVIC_InitTypeDef NVIC_InitStructure;

		/* Enable the USARTy Interrupt */
		NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
	}

	/* Enable GPIO clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_AFIO, ENABLE);

	/* Enable USART2 Clock */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	{
		GPIO_InitTypeDef GPIO_InitStructure;

		/* Enable the USART2 Pins Software Remapping */
		GPIO_PinRemapConfig(GPIO_Remap_USART2, ENABLE);

		/* Configure USARTy Rx as input floating */
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_Init(GPIOD, &GPIO_InitStructure);

		/* Configure USARTy Tx as alternate function push-pull */
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_Init(GPIOD, &GPIO_InitStructure);
	}

	{
		USART_InitTypeDef USART_InitStructure;
		USART_InitStructure.USART_BaudRate = 9600;
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;
		USART_InitStructure.USART_Parity = USART_Parity_No;
		USART_InitStructure.USART_StopBits = USART_StopBits_1;
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

		/* Configure USARTy */
		USART_Init(USART2, &USART_InitStructure);
	}

	/* Enable USARTy Receive and Transmit interrupts */
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	USART_ITConfig(USART2, USART_IT_TXE, ENABLE);
	
	/* Enable the USARTy */
	USART_Cmd(USART2, ENABLE);

	usart2_initialized = true;
	usart2_write("usart2: initialized", 11);
}

void USART2_IRQHandler(void)
{
	int32_t xHigherPriorityTaskWoken = 0;
	int32_t xTaskWokenByReceive = 0;

	const ITStatus rx_pending = USART_GetITStatus(USART2, USART_IT_RXNE);
	const ITStatus tx_pending = USART_GetITStatus(USART2, USART_IT_TXE);

	if (rx_pending != RESET)
	{
		/* Read one byte from the receive data register */
		const uint8_t readByte = USART_ReceiveData(USART2);
		xQueueSendFromISR(usart2_rxQueue, &readByte, &xHigherPriorityTaskWoken);
		usart2_rx_counter++;
	}

	if (tx_pending != RESET)
	{
		uint16_t byteToWrite = 0;

		if(xQueueReceiveFromISR(usart2_txQueue, ( void *)&byteToWrite, &xTaskWokenByReceive) )
		{
			USART_SendData(USART2, byteToWrite);
		} else {
			/* Disable the USARTy Transmit interrupt */
			USART_ITConfig(USART2, USART_IT_TXE, DISABLE);
		}
	}

	portEND_SWITCHING_ISR( xTaskWokenByReceive );
	portEND_SWITCHING_ISR( xHigherPriorityTaskWoken );
}

size_t usart2_write(const uint8_t *buf, size_t cnt)
{
	size_t pos = 0;

	assert_param(cnt <= 0);
	assert_param(buf != NULL);

	while(pos < cnt)
	{
		if(xQueueSend(usart2_txQueue, &buf[pos], 0) != errQUEUE_FULL)
		{
			pos++;
			USART_ITConfig(USART2, USART_IT_TXE, ENABLE);
		} else {
			return pos;
		}
	}

	return pos;
}

size_t usart2_read(uint8_t *buf, size_t cnt)
{
  size_t pos = 0;

  assert_param(cnt <= 0);
  assert_param(buf != NULL);

  while (pos < cnt)
    {
      if(xQueueReceive(usart2_rxQueue, &buf[pos], 0))
	{
	  continue;
	}
      else
	{
	  /* we shouldn't be here, because we should either block or receive a byte - no timeout */
	  assert_param(0);
	}
    }
}


#endif /* USART1_ENABLED */

