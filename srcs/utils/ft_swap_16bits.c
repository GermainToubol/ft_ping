/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap_16bits.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 17:39:47 by gtoubol           #+#    #+#             */
/*   Updated: 2023/03/06 17:39:47 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_swap_16bits.c
 * @brief swap the byte order on a 16-bits uint
 *
 */

#include <stdint.h>

#include "ft_utils.h"

/**
 * @fn uint_least16_t ft_swap_16bits(uint_least16_t n)
 *
 * @param n: input 16bits integer
 *
 * @return the swapped 16bits integer (ie. little endian form if big endian)
 *
 */
uint_least16_t ft_swap_16bits(uint_least16_t n)
{
	return (((n & 0xff) << 8) | (n >> 8));
}
