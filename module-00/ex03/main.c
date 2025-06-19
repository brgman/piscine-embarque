/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abergman <abergman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 13:59:05 by abergman          #+#    #+#             */
/*   Updated: 2025/06/15 15:21:43 by abergman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <avr/io.h>

#define CYCLES_PER_LOOP 3 
#define CPU_FREQUENCE 8000000
#define SLEEP	0.5
#define ITERATIONS (uint32_t)(SLEEP * (CPU_FREQUENCE / CYCLES_PER_LOOP))


//8000000 d'operations par secondes
//cb d'operations ? 
int main()
{
	DDRB |= (1 << PB1); 		//definit PB1 comme output
	uint32_t i;
	while (1)
	{
		i = 0;
		while (i < ITERATIONS)	//2 cycles /i < 133333
			++i; 				//1 cycle
		PORTB ^= (1 << PB1);	//allume ou eteint la led en definissant le bit concerne a 0(eteint) s'il est a 1(allume) et inversement
	}
}
