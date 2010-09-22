# Hey Emacs, this is a -*- makefile -*-
PROJ=stm32template-newlib

CC=arm-eabi-gcc
AS=arm-eabi-as
LD=arm-eabi-gcc
NM=arm-eabi-nm
AR=arm-eabi-ar
OBJCOPY=arm-eabi-objcopy
READELF=arm-eabi-readelf
LINT=splint


#USE_LINT=1

LINTFLAGS=-posix-lib # -weak
LDFILE=stm32.ld

MYCFLAGS=-std=c99 -Os -gdwarf-2 -pedantic -Wall -Wcast-align -Wcast-qual \
    -Wchar-subscripts -Winline -Wpointer-arith -Wredundant-decls -Wshadow \
    -Wwrite-strings -DSTM32F10X_XL -DUSE_STDPERIPH_DRIVER -DDEBUG -USE_FULL_ASSERT


all: libs $(PROJ).elf $(PROJ).sym $(PROJ).hex $(PROJ).bin
	$(READELF) -l $(PROJ).elf

LIB_STM32_DIR=lib/stm32lib
LIB_STM32_INCDIR=$(LIB_STM32_DIR)/include
LIB_STM32_SRCS=$(wildcard $(LIB_STM32_DIR)/src/*.c)
LIB_STM32_OBJS=$(patsubst %c, %o, $(LIB_STM32_SRCS))
LIB_STM32_TARGET=$(LIB_STM32_DIR)/libstm32.a
$(LIB_STM32_TARGET): $(LIB_STM32_OBJS)
	$(AR) rDfs $(LIB_STM32_TARGET) $(LIB_STM32_OBJS)


LIB_BSP_DIR=bsp
LIB_BSP_INCDIR=$(LIB_BSP_DIR)
LIB_BSP_SRCS=$(wildcard $(LIB_BSP_DIR)/*.c)
LIB_BSP_OBJS=$(patsubst %c, %o, $(LIB_BSP_SRCS))
LIB_BSP_TARGET=bsp.a
$(LIB_BSP_TARGET): $(LIB_BSP_OBJS)
	$(AR) rDfs $(LIB_BSP_TARGET) $(LIB_BSP_OBJS)

LIB_CRT_DIR=crt
LIB_CRT_INCDIR=$(LIB_CRT_DIR)
LIB_CRT_SRCS=$(wildcard $(LIB_CRT_DIR)/*.c)
LIB_CRT_OBJS=$(patsubst %c, %o, $(LIB_CRT_SRCS))
LIB_CRT_TARGET=crt.a

$(LIB_CRT_TARGET): $(LIB_CRT_OBJS)
	$(AR) rDfs $(LIB_CRT_TARGET) $(LIB_CRT_OBJS)


LIB_STM32DSP_DIR=lib/stm32dsplib
LIB_STM32DSP_INCDIR=$(LIB_STM32DSP_DIR)/include
LIB_STM32DSP_CSRCS=$(wildcard $(LIB_STM32DSP_DIR)/src/*.c)
LIB_STM32DSP_SSRCS=$(wildcard $(LIB_STM32DSP_DIR)/src/*.s)
LIB_STM32DSP_COBJS=$(patsubst %c, %o, $(LIB_STM32DSP_CSRCS))
LIB_STM32DSP_SOBJS=$(patsubst %s, %o, $(LIB_STM32DSP_SSRCS))
LIB_STM32DSP_OBJS=$(LIB_STM32DSP_COBJS) $(LIB_STM32DSP_SOBJS)
LIB_STM32DSP_TARGET=$(LIB_STM32DSP_DIR)/libstm32dsp.a
$(LIB_STM32DSP_TARGET): $(LIB_STM32DSP_OBJS)
	$(AR) rDfs $(LIB_STM32DSP_TARGET) $(LIB_STM32DSP_OBJS)


CSRCS=$(wildcard *.c)
SSRCS=$(wildcard *.s)
COBJS=$(patsubst %c, %o, $(CSRCS))
SOBJS=$(patsubst %s, %o, $(SSRCS))
OBJS=$(COBJS) $(SOBJS)

LIBS = $(LIB_STM32_TARGET) $(LIB_STM32DSP_TARGET) $(LIB_BSP_TARGET) $(LIB_CRT_TARGET)

libs : $(LIBS)

libsclean : 
	rm -f $(LIB_STM32_TARGET) $(LIB_STM32_OBJS) \
		 $(LIB_STM32DSP_TARGET) $(LIB_STM32DSP_OBJS) \
		 $(LIB_BSP_TARGET) $(LIB_BSP_OBJS) \
		 $(LIB_CRT_TARGET) $(LIB_CRT_OBJS) 

INCLUDE=-I. -I$(LIB_STM32_INCDIR) -I$(LIB_STM32DSP_INCDIR) \
	-I$(LIB_BSP_INCDIR) -I$(LIB_CRT_INCDIR)



CFLAGS=-mthumb -mcpu=cortex-m3 -mtune=cortex-m3 -ffunction-sections $(MYCFLAGS) $(INCLUDE)
ASFLAGS=-mcpu=cortex-m3 -mthumb --gdwarf-2
GENDEPFLAGS=-MD -MP -MF .deps/$(@F).d
LDFLAGS=-static -Wl,-Map,$(PROJ).map,--gc-sections -nostartfiles -T $(LDFILE) 

$(PROJ).elf: $(OBJS) $(LIBS) $(LDFILE) 
	$(LD) $(LDFLAGS) $(OBJS) $(LIBS) -o $@

clean: libsclean
	rm -f $(OBJS) $(PROJ).map $(PROJ).elf $(PROJ).sym $(PROJ).hex $(PROJ).bin

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

.PHONY : all clean libs libclean

