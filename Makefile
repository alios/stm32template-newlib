PROJ=stm32template

CC=arm-elf-gcc
LD=arm-elf-gcc

MYCFLAGS=-std=c99 -Os -gdwarf-2-pedantic -Wall -Wcast-align -Wcast-qual \
    -Wchar-subscripts -Winline -Wpointer-arith -Wredundant-decls -Wshadow \
    -Wwrite-strings

CFLAGS=-mthumb -mcpu=cortex-m3 -mtune=cortex-m3 -ffunction-sections -I.
GENDEPFLAGS=-MD -MP -MF .deps/$(@F).d
LDFLAGS=-static -Wl,-Map,$(PROJ).map,--gc-sections -nostartfiles -T stm32.ld 



OBJS = \
 main.o \
 irq.o \
 crt0.o


all: $(PROJ).elf

clean:
	rm -f $(OBJS) $(PROJ).elf $(PROJ).map

$(PROJ).elf: $(OBJS) stm32.ld
	$(LD) $(LDFLAGS) $(OBJS) $(OOBJS) -o $@

%.o : %.c
	$(CC) $(CFLAGS) $(GENDEPFLAGS) -o $@ -c $<

include .depend

