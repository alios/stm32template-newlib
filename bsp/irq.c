#include <stdint.h>
#include "irq.h"

void SVC_Handler_main(uint32_t* svc_args)
{
	uint32_t svc_number;

	svc_number = ((char *) svc_args[6])[-2];

	switch (svc_number)
	{
	case 0:
		break;
	default:
		break;
	}
}

void NMIException(void)
{
	for (;;)
		;
}
void HardFaultException(void)
{
	for (;;)
		;
}
void MemManageException(void)
{
	for (;;)
		;
}
void BusFaultException(void)
{
	for (;;)
		;
}
void UsageFaultException(void)
{
	for (;;)
		;
}
void DebugMon_Handler(void)
{
	for (;;)
		;
}
void PendSV_Handler(void)
{
	for (;;)
		;
}
void SysTick_Handler(void)
{
	for (;;)
		;
}
void WWDG_IRQHandler(void)
{
	for (;;)
		;
}
void PVD_IRQHandler(void)
{
	for (;;)
		;
}
void TAMPER_IRQHandler(void)
{
	for (;;)
		;
}
void RTC_IRQHandler(void)
{
	for (;;)
		;
}
void FLASH_IRQHandler(void)
{
	for (;;)
		;
}
void RCC_IRQHandler(void)
{
	for (;;)
		;
}
void EXTI0_IRQHandler(void)
{
	for (;;)
		;
}
void EXTI1_IRQHandler(void)
{
	for (;;)
		;
}
void EXTI2_IRQHandler(void)
{
	for (;;)
		;
}
void EXTI3_IRQHandler(void)
{
	for (;;)
		;
}
void EXTI4_IRQHandler(void)
{
	for (;;)
		;
}
void DMA1_Channel1_IRQHandler(void)
{
	for (;;)
		;
}
void DMA1_Channel2_IRQHandler(void)
{
	for (;;)
		;
}
void DMA1_Channel3_IRQHandler(void)
{
	for (;;)
		;
}
void DMA1_Channel4_IRQHandler(void)
{
	for (;;)
		;
}
void DMA1_Channel5_IRQHandler(void)
{
	for (;;)
		;
}
void DMA1_Channel6_IRQHandler(void)
{
	for (;;)
		;
}
void DMA1_Channel7_IRQHandler(void)
{
	for (;;)
		;
}
void ADC1_2_IRQHandler(void)
{
	for (;;)
		;
}
void USB_HP_CAN1_TX_IRQHandler(void)
{
	for (;;)
		;
}
void USB_LP_CAN1_RX0_IRQHandler(void)
{
	for (;;)
		;
}
void CAN1_RX1_IRQHandler(void)
{
	for (;;)
		;
}
void CAN1_SCE_IRQHandler(void)
{
	for (;;)
		;
}
void EXTI9_5_IRQHandler(void)
{
	for (;;)
		;
}
void TIM1_BRK_IRQHandler(void)
{
	for (;;)
		;
}
void TIM1_UP_IRQHandler(void)
{
	for (;;)
		;
}
void TIM1_TRG_COM_IRQHandler(void)
{
	for (;;)
		;
}
void TIM1_CC_IRQHandler(void)
{
	for (;;)
		;
}
void TIM2_IRQHandler(void)
{
	for (;;)
		;
}
void TIM3_IRQHandler(void)
{
	for (;;)
		;
}
void TIM4_IRQHandler(void)
{
	for (;;)
		;
}
void I2C1_EV_IRQHandler(void)
{
	for (;;)
		;
}
void I2C1_ER_IRQHandler(void)
{
	for (;;)
		;
}
void I2C2_EV_IRQHandler(void)
{
	for (;;)
		;
}
void I2C2_ER_IRQHandler(void)
{
	for (;;)
		;
}
void SPI1_IRQHandler(void)
{
	for (;;)
		;
}
void SPI2_IRQHandler(void)
{
	for (;;)
		;
}
void USART1_IRQHandler(void)
{
	for (;;)
		;
}
void USART2_IRQHandler(void)
{
	for (;;)
		;
}
void USART3_IRQHandler(void)
{
	for (;;)
		;
}
void EXTI15_10_IRQHandler(void)
{
	for (;;)
		;
}
void RTCAlarm_IRQHandler(void)
{
	for (;;)
		;
}
void USBWakeUp_IRQHandler(void)
{
	for (;;)
		;
}
void TIM8_BRK_IRQHandler(void)
{
	for (;;)
		;
}
void TIM8_UP_IRQHandler(void)
{
	for (;;)
		;
}
void TIM8_TRG_COM_IRQHandler(void)
{
	for (;;)
		;
}
void TIM8_CC_IRQHandler(void)
{
	for (;;)
		;
}
void ADC3_IRQHandler(void)
{
	for (;;)
		;
}
void FSMC_IRQHandler(void)
{
	for (;;)
		;
}
void SDIO_IRQHandler(void)
{
	for (;;)
		;
}
void TIM5_IRQHandler(void)
{
	for (;;)
		;
}
void SPI3_IRQHandler(void)
{
	for (;;)
		;
}
void UART4_IRQHandler(void)
{
	for (;;)
		;
}
void UART5_IRQHandler(void)
{
	for (;;)
		;
}
void TIM6_IRQHandler(void)
{
	for (;;)
		;
}
void TIM7_IRQHandler(void)
{
	for (;;)
		;
}
void DMA2_Channel1_IRQHandler(void)
{
	for (;;)
		;
}
void DMA2_Channel2_IRQHandler(void)
{
	for (;;)
		;
}
void DMA2_Channel3_IRQHandler(void)
{
	for (;;)
		;
}
void DMA2_Channel4_5_IRQHandler(void)
{
	for (;;)
		;
}
