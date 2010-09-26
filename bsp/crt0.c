#include <stdlib.h>
#include <string.h>
#include <stm32f10x_conf.h>
#include "irq.h"

#include "usart.h"

extern int main();

extern void* _estack;
extern void* _sdata;
extern void* _edata;
extern void* _sidata;
extern void* _sbss;
extern void* _ebss;
extern void* _eusrstack;

void _start();
extern void _init_crt1();

extern void xPortPendSVHandler( void ) __attribute__ (( naked ));
extern void xPortSysTickHandler( void );
extern void vPortSVCHandler( void ) __attribute__ (( naked ));

/* IRQ vector table */
__attribute__ ((section(".isr_vector")))
struct configword_struct
{
	const void* stackpointer;
	void (* const vectors[165])(void);
} configword =
{
	&_estack,
	{
		_start,
		NMIException,
		HardFaultException,
		MemManageException,
		BusFaultException,
		UsageFaultException,
		NULL,
		NULL,
		NULL,
		NULL,
		vPortSVCHandler,
		DebugMon_Handler,
		NULL,
		xPortPendSVHandler,
		xPortSysTickHandler,
		WWDG_IRQHandler,
		PVD_IRQHandler,
		TAMPER_IRQHandler,
		RTC_IRQHandler,
		FLASH_IRQHandler,
		RCC_IRQHandler,
		EXTI0_IRQHandler,
		EXTI1_IRQHandler,
		EXTI2_IRQHandler,
		EXTI3_IRQHandler,
		EXTI4_IRQHandler,
		DMA1_Channel1_IRQHandler,
		DMA1_Channel2_IRQHandler,
		DMA1_Channel3_IRQHandler,
		DMA1_Channel4_IRQHandler,
		DMA1_Channel5_IRQHandler,
		DMA1_Channel6_IRQHandler,
		DMA1_Channel7_IRQHandler,
		ADC1_2_IRQHandler,
		USB_HP_CAN1_TX_IRQHandler,
		USB_LP_CAN1_RX0_IRQHandler,
		CAN1_RX1_IRQHandler,
		CAN1_SCE_IRQHandler,
		EXTI9_5_IRQHandler,
		TIM1_BRK_IRQHandler,
		TIM1_UP_IRQHandler,
		TIM1_TRG_COM_IRQHandler,
		TIM1_CC_IRQHandler,
		TIM2_IRQHandler,
		TIM3_IRQHandler,
		TIM4_IRQHandler,
		I2C1_EV_IRQHandler,
		I2C1_ER_IRQHandler,
		I2C2_EV_IRQHandler,
		I2C2_ER_IRQHandler,
		SPI1_IRQHandler,
		SPI2_IRQHandler,
		USART1_IRQHandler,
		USART2_IRQHandler,
		USART3_IRQHandler,
		EXTI15_10_IRQHandler,
		RTCAlarm_IRQHandler,
		USBWakeUp_IRQHandler,
		TIM8_BRK_IRQHandler,
		TIM8_UP_IRQHandler,
		TIM8_TRG_COM_IRQHandler,
		TIM8_CC_IRQHandler,
		ADC3_IRQHandler,
		FSMC_IRQHandler,
		SDIO_IRQHandler,
		TIM5_IRQHandler,
		SPI3_IRQHandler,
		UART4_IRQHandler,
		UART5_IRQHandler,
		TIM6_IRQHandler,
		TIM7_IRQHandler,
		DMA2_Channel1_IRQHandler,
		DMA2_Channel2_IRQHandler,
		DMA2_Channel3_IRQHandler,
		DMA2_Channel4_5_IRQHandler,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL
	}
};

void null_driver_reset()
{
}

static const driver_t null_driver =
	{ "null", NULL, 0, 0, 0 };

static const driver_t*	 drivers[] =
{
#ifdef USART1_ENABLED
		&usart1_driver,
#endif
		&null_driver
};

void _start()
{
	/* copy data segment from flash to ram */
	{
		const size_t datalen = (size_t) &_edata - (unsigned int) &_sdata;
		memcpy(&_sdata, &_sidata, datalen);
	}

	/* zero out bss segment */
	{
		const size_t bsslen = (size_t) &_ebss - (unsigned int) &_sbss;
		memset(&_sbss, 0x0, bsslen);
	}

	SystemInit();

	/* set process stack */
	__set_PSP((uint32_t) &_eusrstack);

	/* enable drivers */
	/*for (size_t i = 0; i < sizeof(drivers); i++)
	{
		const driver_t* drv_p = drivers[i];
		if (drv_p->driver_reset != NULL)
		  drv_p->driver_reset();
		enable_clocks(drv_p);

	}
	*/

	(void) _init_crt1();
	(void) main();
}

