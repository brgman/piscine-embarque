/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abergman <abergman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 16:37:22 by abergman          #+#    #+#             */
/*   Updated: 2025/06/15 18:55:43 by abergman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <avr/io.h>
#include <util/delay.h>

int main()
{
    // Activer PB1 (OC1A) et PB2 (OC1B) comme sorties
    DDRB |= (1 << PB0 ) | (1 << PB1) | (1 << PB2) | (1 << PB4);
    
    // Réinitialiser les registres du Timer1
    TCCR1A = 0;
    TCCR1B = 0;
    
    // Mode 14 : PWM rapide, TOP = ICR1
    TCCR1A |= (1 << WGM11);
    TCCR1B |= (1 << WGM13) | (1 << WGM12);
    
    // Mode non-inversé pour OC1A (PB1) et OC1B (PB2) : allume à OCR1x, éteint à BOTTOM
    TCCR1A |= (1 << COM1A1) | (1 << COM1B1);

    // Prédiviseur d’horloge : /256 (le commentaire "576" est incorrect)
    TCCR1B |= (1 << CS12);
    
    // Définir la valeur TOP pour un PWM de 1 Hz (horloge 16 MHz)
    ICR1 = 62500;
    // Définir la valeur initiale pour un cycle de travail de 50 %
    OCR1A = 31250;
    OCR1B = 31250; // Même cycle de travail pour PB2
    
    // Configurer PD2 (SW1) et PD4 (SW2) comme entrées
    DDRD &= ~(1 << PD2) & ~(1 << PD4);
    // Activer les pull-ups internes pour les boutons (optionnel, si pas de pull-ups externes)
    PORTD |= (1 << PD2) | (1 << PD4);
    
    uint8_t duty_cycle = 50;
    uint8_t pd2_is_pressed = 0;
    uint8_t pd4_is_pressed = 0;
    
    while (1)
    {
        if (!(PIND & (1 << PD2)))
        {
            if (!pd2_is_pressed)
            {
                pd2_is_pressed = 1;
                if (duty_cycle + 10 <= 100)
                    duty_cycle += 10;
                OCR1A = duty_cycle * 625; // Optimisation : 62500 / 100 = 625
                OCR1B = OCR1A; // Synchroniser PB2 avec PB1
                _delay_ms(50); // Débouncing
            }
        }
        else
            pd2_is_pressed = 0;
        
        if (!(PIND & (1 << PD4)))
        {
            if (!pd4_is_pressed)
            {
                pd4_is_pressed = 1;
                if (duty_cycle >= 10)
                    duty_cycle -= 10;
                OCR1A = duty_cycle * 625;
                OCR1B = OCR1A; // Synchroniser PB2 avec PB1
                _delay_ms(50); // Débouncing
            }
        }
        else
            pd4_is_pressed = 0;
    }
}
