# Hey Emacs, this is a -*- makefile -*-
PROJ=stm32template-newlib

CC=arm-elf-gcc
AS=arm-elf-as
LD=arm-elf-gcc
NM=arm-elf-nm
OBJCOPY=arm-elf-objcopy
READELF=arm-elf-readelf
LINT=splint

#USE_LINT=1

LINTFLAGS=-posix-lib # -weak
LDFILE=stm32.ld

MYCFLAGS=-std=c99 -Os -gdwarf-2 -pedantic -Wall -Wcast-align -Wcast-qual \
    -Wchar-subscripts -Winline -Wpointer-arith -Wredundant-decls -Wshadow \
    -Wwrite-strings

STM32LIB_DIR=lib/stm32lib
STM32LIB_SRCS=$(STM32LIB_DIR)/src
STM32LIB_INC=$(STM32LIB_DIR)/include

STM32DSPLIB_DIR=lib/stm32dsplib
STM32DSPLIB_SRCS=$(STM32DSPLIB_DIR)/src
STM32DSPLIB_INC=$(STM32DSPLIB_DIR)/include

INCLUDE=-I. -I$(STM32LIB_INC) -I$(STM32DSPLIB_INC)
CFLAGS=-mthumb -mcpu=cortex-m3 -mtune=cortex-m3 -ffunction-sections $(MYCFLAGS) $(INCLUDE)
ASFLAGS=-mcpu=cortex-m3 -mthumb --gdwarf-2
GENDEPFLAGS=-MD -MP -MF .deps/$(@F).d
LDFLAGS=-static -Wl,-Map,$(PROJ).map,--gc-sections -nostartfiles -T $(LDFILE)

STM32LIBOBJS= \
 $(STM32LIB_SRCS)/core_cm3.o $(STM32LIB_SRCS)/system_stm32f10x.o \
 $(STM32LIB_SRCS)/misc.o $(STM32LIB_SRCS)/stm32f10x_adc.o \
 $(STM32LIB_SRCS)/stm32f10x_bkp.o $(STM32LIB_SRCS)/stm32f10x_can.o \
 $(STM32LIB_SRCS)/stm32f10x_cec.o $(STM32LIB_SRCS)/stm32f10x_crc.o \
 $(STM32LIB_SRCS)/stm32f10x_dac.o $(STM32LIB_SRCS)/stm32f10x_dbgmcu.o \
 $(STM32LIB_SRCS)/stm32f10x_dma.o $(STM32LIB_SRCS)/stm32f10x_exti.o \
 $(STM32LIB_SRCS)/stm32f10x_flash.o $(STM32LIB_SRCS)/stm32f10x_fsmc.o \
 $(STM32LIB_SRCS)/stm32f10x_gpio.o $(STM32LIB_SRCS)/stm32f10x_i2c.o \
 $(STM32LIB_SRCS)/stm32f10x_iwdg.o $(STM32LIB_SRCS)/stm32f10x_pwr.o \
 $(STM32LIB_SRCS)/stm32f10x_rcc.o $(STM32LIB_SRCS)/stm32f10x_rtc.o \
 $(STM32LIB_SRCS)/stm32f10x_sdio.o $(STM32LIB_SRCS)/stm32f10x_spi.o \
 $(STM32LIB_SRCS)/stm32f10x_tim.o $(STM32LIB_SRCS)/stm32f10x_usart.o \
 $(STM32LIB_SRCS)/stm32f10x_wwdg.o

STM32DSPLIBOBJS= \
 $(STM32DSPLIB_SRCS)/PID_C_stm32.o $(STM32DSPLIB_SRCS)/PID_stm32.o \
 $(STM32DSPLIB_SRCS)/cr4_fft_1024_stm32.o \
 $(STM32DSPLIB_SRCS)/cr4_fft_256_stm32.o \
 $(STM32DSPLIB_SRCS)/cr4_fft_64_stm32.o \
 $(STM32DSPLIB_SRCS)/fir_stm32.o \
 $(STM32DSPLIB_SRCS)/iir_stm32.o \
 $(STM32DSPLIB_SRCS)/iirarma_stm32.o

OBJS = \
 $(STM32LIBOBJS) \
 $(STM32DSPLIBOBJS) \
 $(STM32USBLIBOBJS) \
 main.o \
 irq.o \
 crt0.o \
 crt1.o \
 console.o


all: $(PROJ).elf $(PROJ).sym $(PROJ).hex $(PROJ).bin
	$(READELF) -l $(PROJ).elf
clean:
	rm -rf .deps $(OBJS) $(PROJ).elf $(PROJ).map $(PROJ).hex $(PROJ).sym $(PROJ).bin

$(PROJ).elf: $(OBJS) $(LDFILE) 
	$(LD) $(LDFLAGS) $(OBJS) $(OOBJS) -o $@

%.o : %.c
ifdef USE_LINT
	$(LINT) $(LINTFLAGS) $<
endif	
	$(CC) $(CFLAGS) $(GENDEPFLAGS) -o $@ -c $<

%.o : %.s
	$(AS) $(ASFLAGS) -o $@ $<

%.sym: %.elf
	$(NM) -n $< > $@

%.hex: %.elf
	$(OBJCOPY) -j .isr_vector -j .text -j .data -O ihex $< $@

%.bin: %.elf
	$(OBJCOPY) -j .isr_vector -j .text -j .data -O binary $< $@

-include $(shell mkdir -p .deps 2>/dev/null) $(wildcard .dep/*)

.PHONY : all clean

