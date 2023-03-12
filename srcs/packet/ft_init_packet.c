/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_packet.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:26:41 by gtoubol           #+#    #+#             */
/*   Updated: 2023/03/06 15:26:41 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_init_packet.c
 * @brief Init commun base on packets
 *
 * Pass all commun data to the packets
 *
 */

#include <stddef.h>
#include <stdint.h>

#include "ft_packet.h"
#include "ft_ping.h"
#include "libft.h"

static void ft_set_packetdata(t_icmp_packet *packet, const t_server *server);

/**
 * @fn void ft_init_packet(t_icmp_packet *packet, const t_server *server)
 *
 * @param packet: base packet
 * @param server: current ping server
 *
 * @brief Set all commun field of an ICMP packet
 *
 * Init icmp packet header and icmp packet data with commun data to any
 * ICMP packet
 */
void	ft_init_packet(t_icmp_packet *packet, const t_server *server)
{
	packet->type = 8;
	packet->code = 0;
	packet->echo.id = server->id;
	ft_set_packetdata(packet, server);
}

/**
 * @fn void ft_set_packet_data(t_icmp_packet *packet, const t_server *server)
 *
 * @param packet: base packet
 * @param server: current ping server
 *
 * @brief set the padding bytes
 *
 */
static void ft_set_packetdata(t_icmp_packet *packet, const t_server *server)
{
	ptrdiff_t ptr = (ptrdiff_t)packet->data;
	ft_bzero(packet->data, ICMP_ECHO_DATA_LENGTH);
	if (server->pattern_length < 1)
		return ;
	for (uint32_t i = 0; i < ICMP_ECHO_DATA_LENGTH / server->pattern_length; i++, ptr += (ptrdiff_t)server->pattern_length)
		ft_memcpy((void *)ptr,
				  server->pattern,
				  server->pattern_length);
	ft_memcpy((void *)ptr, server->pattern, ICMP_ECHO_DATA_LENGTH % server->pattern_length);
}
