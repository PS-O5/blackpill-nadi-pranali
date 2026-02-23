TARGET = main
CC = arm-none-eabi-gcc

CFLAGS = -mcpu=cortex-m4 -mthumb -O0 -g
LDFLAGS = -T linker.ld -nostdlib

all:
	$(CC) $(CFLAGS) startup.c main.c $(LDFLAGS) -o $(TARGET).elf
	arm-none-eabi-objcopy -O binary $(TARGET).elf $(TARGET).bin

flash: all
	st-flash --reset write $(TARGET).bin 0x08000000

clean:
	rm -f *.elf *.bin
