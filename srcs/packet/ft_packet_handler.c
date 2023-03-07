/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_packet_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 15:50:37 by gtoubol           #+#    #+#             */
/*   Updated: 2023/03/07 15:50:37 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_packet_handler.c
 * @brief gather all icmp packet handlers
 *
 */

#include <stddef.h>
#include <stdio.h>

#include "ft_packet.h"
#include "ft_ping.h"

/**
 * @fn void ft_handel_request(const t_server *server,
 * const t_icmp_packet *packet, size_t size)
 *
 * @param server: current ping server
 * @param packet: incomming icmp packet
 * @param size: size of the packet
 *
 * @brief drop the packet
 */
void ft_handel_request(
	const t_server *server,
	const t_icmp_packet *packet,
	size_t size)
{
	(void)server;
	(void)packet;
	(void)size;
	dprintf(2, "ft_ping: stop pinging yourself!\n");
}
