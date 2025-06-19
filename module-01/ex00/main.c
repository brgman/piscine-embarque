/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abergman <abergman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 15:27:00 by abergman          #+#    #+#             */
/*   Updated: 2025/06/16 13:00:19 by abergman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <avr/io.h>

#define CYCLES_PER_LOOP 3
#define CPU_FREQUENCE 16000000
#define SLEEP .1
#define ITERATIONS (uint32_t)(SLEEP * (CPU_FREQUENCE / CYCLES_PER_LOOP))

int main (void)
{
    DDRB |= (1 << PB1);
    DDRB |= (1 << PB0);
    
    uint32_t index;
    while (1)
    {
        index = 0;
        PORTB ^=(1 << PB0);
        while (index < ITERATIONS)
        {
            ++index;
        }
        PORTB ^=(1 << PB1);
    }
}