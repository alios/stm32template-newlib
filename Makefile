# Hey Emacs, this is a -*- makefile -*-


PROJ=stm32template-newlib

CC=arm-elf-gcc
LD=arm-elf-gcc
NM=arm-elf-nm
OBJCOPY=arm-elf-objcopy
LINT=splint

MYCFLAGS=-std=c99 -Os -gdwarf-2 -pedantic -Wall -Wcast-align -Wcast-qual \
    -Wchar-subscripts -Winline -Wpointer-arith -Wredundant-decls -Wshadow \
    -Wwrite-strings

CFLAGS=-mthumb -mcpu=cortex-m3 -mtune=cortex-m3 -ffunction-sections $(MYCFLAGS) -I.
GENDEPFLAGS=-MD -MP -MF .deps/$(@F).d
LDFLAGS=-static -Wl,-Map,$(PROJ).map,--gc-sections -nostartfiles -T stm32.ld 

OBJS = \
 main.o \
 irq.o \
 crt0.o \
 crt1.o


all: $(PROJ).elf $(PROJ).sym $(PROJ).hex $(PROJ).bin

clean:
	rm -rf .deps $(OBJS) $(PROJ).elf $(PROJ).map $(PROJ).hex $(PROJ).sym $(PROJ.bin)

$(PROJ).elf: $(OBJS) stm32.ld
	$(LD) $(LDFLAGS) $(OBJS) $(OOBJS) -o $@

%.o : %.c
	$(LINT) -posix-lib -weak $<
	$(CC) $(CFLAGS) $(GENDEPFLAGS) -o $@ -c $<

%.sym: %.elf
	$(NM) -n $< > $@

%.hex: %.elf
	$(OBJCOPY) -j .isr_vector -j .text -j .data -O ihex $< $@

%.bin: %.elf
	$(OBJCOPY) -j .isr_vector -j .text -j .data -O binary $< $@

-include $(shell mkdir -p .deps 2>/dev/null) $(wildcard .dep/*)

.PHONY : all clean

