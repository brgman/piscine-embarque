/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abergman <abergman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 16:25:28 by abergman          #+#    #+#             */
/*   Updated: 2025/06/15 16:35:17 by abergman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <avr/io.h>

int main()
{
    // Configure PB1 comme sortie
    DDRB |= (1 << PB1);
    
    // Mode 14 : PWM rapide, TOP = ICR1
    TCCR1A |= (1 << WGM11);
    TCCR1B |= (1 << WGM13) | (1 << WGM12);
    
    // Mode non-inversé : allume à OCR1A, éteint à BOTTOM
    TCCR1A &= ~(1 << COM1A0);
    TCCR1A |= (1 << COM1A1);
    
    // Prédiviseur d’horloge : /1024
    TCCR1B |= (1 << CS12) | (1 << CS10);
    TCCR1B &= ~(1 << CS11);
    
    // Définit la valeur TOP pour un PWM de 1 Hz (horloge 16 MHz)
    ICR1 = 15625;
    // Définit la valeur de comparaison pour un cycle de travail de 50 %
    OCR1A = 15625 / 2; // 7812 pour 50 % de cycle de travail
    // OCR1A = ICR1 * 0.01; // alumé pendant 0.01 s
    
    while (1)
    {
    }
}