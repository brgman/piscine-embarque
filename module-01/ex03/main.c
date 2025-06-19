/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abergman <abergman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 16:37:22 by abergman          #+#    #+#             */
/*   Updated: 2025/06/18 15:43:30 by abergman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define PWM_TOP 65535
#define DUTY_STEP (PWM_TOP / 100)

ISR(TIMER1_COMPA_vect) { // pour etain
    // When timer matches OCR1A, clear PB0 and PB4 (end of duty cycle)
    PORTB &= ~((1 << PB0) | (1 << PB4));
}

ISR(TIMER1_OVF_vect) { // pour allume
    PORTB |= (1 << PB0) | (1 << PB4);
}

int main() {
    // Activer PB0, PB1 (OC1A), PB2 (OC1B), PB4 comme sorties
    DDRB |= (1 << PB0) | (1 << PB1) | (1 << PB2) | (1 << PB4);
    
    // Configurer PD2 (SW1) et PD4 (SW2) comme entrées avec pull-ups
    DDRD &= ~((1 << PD2) | (1 << PD4));
    PORTD |= (1 << PD2) | (1 << PD4); 
    
    // Réinitialiser les registres du Timer1
    TCCR1A = 0;
    TCCR1B = 0;
    
    // Mode 14 : PWM rapide, TOP = ICR1
    TCCR1A |= (1 << WGM11);
    TCCR1B |= (1 << WGM13) | (1 << WGM12);
    
    // Mode non-inversé pour OC1A (PB1) et OC1B (PB2)
    TCCR1A |= (1 << COM1A1) | (1 << COM1B1);

    // Prédiviseur d’horloge :
    TCCR1B |= (TCCR1B & ~(1 << CS11));
    // TCCR1B |= (1 << CS12); // 256
    // TCCR1B = (TCCR1B & ~(1 << CS11)) | (1 << CS12) | (1 << CS10); // 1024
    
    // Définir la valeur TOP pour un PWM de 1 Hz (horloge 16 MHz)
    ICR1 = PWM_TOP;
    // Définir la valeur initiale pour un cycle de travail de 50 %
    OCR1A = PWM_TOP / 2;
    OCR1B = PWM_TOP / 2;
    
    // Activer les interruptions pour Compare Match A et Overflow
    TIMSK1 |= (1 << OCIE1A) | (1 << TOIE1);
    
    // Activer les interruptions globales
    sei();
    
    uint8_t duty_cycle = 50;
    uint8_t pd2_is_pressed = 0;
    uint8_t pd4_is_pressed = 0;

    while (1) {
        // Bouton SW1 : Augmenter le cycle de travail
        if (!(PIND & (1 << PD2))) {
            if (!pd2_is_pressed) {
                pd2_is_pressed = 1;
                if (duty_cycle <= 90) {
                    duty_cycle += 10;
                    OCR1A = duty_cycle * DUTY_STEP;
                    OCR1B = OCR1A; // Synchroniser PB2 avec PB1
                }
                _delay_ms(50); // Débouncing
            }
        } else {
            pd2_is_pressed = 0;
        }
        
        // Bouton SW2 : Diminuer le cycle de travail
        if (!(PIND & (1 << PD4))) {
            if (!pd4_is_pressed) {
                pd4_is_pressed = 1;
                if (duty_cycle >= 10) {
                    duty_cycle -= 10;
                    OCR1A = duty_cycle * DUTY_STEP;
                    OCR1B = OCR1A; // Synchroniser PB2 avec PB1
                }
                _delay_ms(50); // Débouncing
            }
        } else {
            pd4_is_pressed = 0;
        }
    }
}
