/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clock.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 23:28:47 by gtoubol           #+#    #+#             */
/*   Updated: 2023/03/02 23:28:47 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_clock.c
 * @brief Time management utilities
 *
 * Time management around the clock ticks
*/

#include "ft_ping.h"

/**
 * @fn void ft_clock_nexttick(t_server *server)
 * @param server: current server structure
 * @brief Servers clock increases by one tick.
 */
inline void	ft_clock_nexttick(t_server *server)
{
	server->clock++;
}
