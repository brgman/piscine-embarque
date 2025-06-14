/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abergman <abergman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 12:44:27 by abergman          #+#    #+#             */
/*   Updated: 2025/06/14 14:33:02 by abergman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// La machine s'eteint quand elle arrive a la fin de progromation
// ensuite quand la machine s'eteint elle se rallume
// refait la programme etc 

#include <avr/io.h>

// DDRX:    
// PORTX:   envoie des donnes sur la carte
// PINX:    recoit des donnes de la carte
// PBX:     led X dans la carte

int main(void)
{
    DDRB |= (1 << PB0); // definit la broche 0 du port "B" comme output
    PORTB |= (1 << PB0); // change l'etat a 1 de cette broche
    while (1) {}
}

