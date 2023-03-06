/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 12:43:31 by gtoubol           #+#    #+#             */
/*   Updated: 2023/03/06 12:43:31 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_loop.c
 * @brief main execution loop
 *
 * Main utility looping arround sending and reading packets
 */

#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

#include "ft_packet.h"
#include "ft_ping.h"

/**
 * @fn int32_t ft_loop(t_server *server)
 *
 * @param server: current ping server
 *
 * @return -1 on failure, 0 otherwise
 *
 * @brief main loop wrapper
 *
 */
int32_t	ft_loop(t_server *server)
{
	t_icmp_packet	packet;

	ft_init_packet(&packet, server);
	(void)packet;
	(void)server;
	return (0);
}
