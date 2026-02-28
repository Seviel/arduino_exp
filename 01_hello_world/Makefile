# ===== Configuration =====

MCU     = atmega328p
F_CPU   = 16000000UL
PORT    = /dev/ttyUSB0
BAUD    = 115200
PROGRAMMER = arduino

CC      = avr-gcc
OBJCOPY = avr-objcopy
AVRDUDE = avrdude

CFLAGS  = -DF_CPU=$(F_CPU) -mmcu=$(MCU) -Os -Wall -Wextra -std=c11
LDFLAGS = -mmcu=$(MCU)

TARGET  = main

# ===== Targets =====

all: $(TARGET).hex

$(TARGET).elf: $(TARGET).o
	$(CC) $(LDFLAGS) $< -o $@

$(TARGET).o: $(TARGET).c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET).hex: $(TARGET).elf
	$(OBJCOPY) -O ihex -j .text -j .data -R .eeprom $< $@

flash: $(TARGET).hex
	$(AVRDUDE) -c $(PROGRAMMER) -p $(MCU) -P $(PORT) -b $(BAUD) \
	-U flash:w:$<

clean:
	rm -f *.o *.elf *.hex

.PHONY: all flash clean