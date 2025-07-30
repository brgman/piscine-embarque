/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abergman <abergman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 16:19:46 by abergman          #+#    #+#             */
/*   Updated: 2025/07/29 17:14:19 by abergman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

ISR(INT0_vect)
{
    _delay_ms(50);
    cli();
    PORTB ^= (1 << PORTB0);
    sei();
}

int main(void)
{
    DDRB |= (1 << PORTB0);
    PORTB |= (1 << PORTB0);
    
    DDRD &= ~(1 << DDD2);
    PORTD |= (1 << PORTD2);

    EICRA |= (1 << ISC00);
    EICRA |= (1 << ISC01);

    EIMSK |= (1 << INT0);
    
    sei();
    while(1);
}
