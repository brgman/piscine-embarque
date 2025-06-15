/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abergman <abergman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 13:59:05 by abergman          #+#    #+#             */
/*   Updated: 2025/06/15 14:29:55 by abergman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <avr/io.h>
#include <util/delay.h>

int main (void)
{
    DDRB |= (1 << PB0); // Consfigure PB0 (broche 8 sur l'ATmega328B) comme sortie.
    DDRD &= ~(1 << PD2); // Configure PD2 (broche 2) comme entrée.
    PORTD |= (1 << PD2); // Active la résistance de pull-up sur PD2

    _delay_ms(10); // Attendre la stabilisation
    uint8_t state = PIND & (1 << PD2); // Lit l'état initial de PD2 (entrée, probablement un bouton).
    while (1) // Boucle infinie
    {
        uint8_t stateInBoucle = PIND & (1 << PD2); // Lit l'état actuel de PD2
        if (state != stateInBoucle) // Si l'état change...
        {
            PORTB ^=(1 << PB0); // ...bascule PB0
            _delay_ms(50); // ...et attend 20 microsecond pour le débouncing
            state = PIND & (1 << PD2); // Met à jour state avec le nouvel état
        }
    }
}


// Le délai de 20 ms est une bonne pratique pour le débouncing d'un bouton, mais il pourrait être insuffisant pour certains boutons mécaniques (certains nécessitent 50-100 ms). Testez avec votre matériel pour confirmer. 

// uint8_t 