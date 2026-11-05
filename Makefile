CC = arm-none-eabi-gcc
LD_SCRIPT = stm32l47.ld
LD_FLAGS  = -T $(LD_SCRIPT)
LD_FLAGS += -nostdlib
CC_FLAGS  = -mcpu=cortex-m4
CC_FLAGS += -mthumb
CC_FLAGS += -mfloat-abi=soft

objects = main.o startup_stm32l476.o

all: $(objects)
	$(CC) $(CC_FLAGS) $(LD_FLAGS) $(objects) -o firmware.elf
	arm-none-eabi-objcopy -O binary firmware.elf firmware.bin

main.o:
	$(CC) $(CC_FLAGS) -c main.c -o main.o

startup_stm32l476.o: startup_stm32l476.c
	$(CC) $(CC_FLAGS) -c startup_stm32l476.c -o startup_stm32l476.o

flash:
	st-flash --reset write firmware.bin 0x08000000

clean:
	rm -f *.o firmware.elf firmware.bin
