# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abergman <abergman@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/15 16:01:02 by abergman          #+#    #+#              #
#    Updated: 2025/06/15 16:01:07 by abergman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MCU = atmega328p
F_CPU = 16000000UL
CC = avr-gcc
OBJCOPY = avr-objcopy
AVRDUDE = avrdude
CFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os -I/usr/lib/include/
AVRDUDE_FLAGS = -c arduino -p $(MCU) -b 115200 -P /dev/ttyUSB0


all: hex flash

hex: main.bin
	$(OBJCOPY) -O ihex -R .eeprom main.bin main.hex

main.bin: main.c
	$(CC) $(CFLAGS) -o main.bin main.c
	
flash: main.hex
	$(AVRDUDE) $(AVRDUDE_FLAGS) -U flash:w:main.hex:i

clean:
	rm -f main.hex main.bin

.PHONY: all hex flash clean
