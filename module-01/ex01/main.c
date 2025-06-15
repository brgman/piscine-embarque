/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abergman <abergman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 16:02:14 by abergman          #+#    #+#             */
/*   Updated: 2025/06/15 16:23:33 by abergman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <avr/io.h>

int main()
{
	DDRB |= (1 << PB1);
	
	// Mode 15: compte de 0 à ICR1 // Fast PWM, 16-bit mode
	// Les bits WGM10, WGM11, WGM12, et WGM13 sont à 1, ce qui correspond
	// au mode PWM rapide où le compteur compte de 0 à la valeur de ICR1 avant 
	// de se réinitialiser.
	
	TCCR1A |= (1 << WGM11) | (1 << WGM10);
	TCCR1B |= (1 << WGM13) | (1 << WGM12);

	//switch LED 0/1
	TCCR1A |= (1 << COM1A0);
	TCCR1A &= ~(1 << COM1A1);
	
	//pre-division clock/1024
	TCCR1B |= (1 << CS10) | (1 << CS12);
	TCCR1B &= ~(1 << CS11);
	
	// Définit la valeur TOP pour un PWM de 1 Hz (horloge 16 MHz)
	ICR1 = 15625;
	// Définit la valeur de comparaison pour un cycle de travail de 50 %
	OCR1A = 7812;

	while (1)
	{
	}
}
