TARGET = nadi_pranali
CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy

# CPU Specifics
CFLAGS = -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16
CFLAGS += -O0 -g -Wall

# Point to your directories
INC = -Iapp -Idrivers -Istartup -Ibsp/blackpill_f411
LDFLAGS = -T linker.ld -nostdlib

# Sources
SRCS = app/main.c \
       startup/startup.c \
       bsp/blackpill_f411/board_init.c

all: $(TARGET).elf

$(TARGET).elf: $(SRCS)
	$(CC) $(CFLAGS) $(INC) $(SRCS) $(LDFLAGS) -o $@
	$(OBJCOPY) -O binary $@ $(TARGET).bin

flash: all
	st-flash --reset write $(TARGET).bin 0x08000000

clean:
	rm -f *.elf *.bin
