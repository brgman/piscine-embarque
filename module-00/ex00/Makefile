# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abergman <abergman@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/13 16:02:08 by abergman          #+#    #+#              #
#    Updated: 2025/06/13 16:16:45 by abergman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Nom de microcontroller
MCU = atmega328p
# Fréquence du microcontrôleur (16 Mz pour Arduino Uno)
F_CPU = 16000000UL
# Compilatour et utilites
CC = avr-gcc
OBJCOPY = avr-objcopy
AVRDUDE = avrdude
# Paramettres de compilation
CFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os
# Paramettres de avrdude
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
