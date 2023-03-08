/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_analyse_packet.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:07:19 by gtoubol           #+#    #+#             */
/*   Updated: 2023/03/07 16:07:19 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_analyse_packet.c
 * @brief retrive informations from ip packet
 *
 */

#include <stdint.h>
#include <stdio.h>

#include "ft_packet.h"
#include "ft_ping.h"
#include "ft_utils.h"

/**
 * @var g_phandler
 * @brief table of icmp packet readers
 */
static const t_packet_handler g_phandler[17] = {
    ft_handel_response,			/*!< type 0 => echo reply */
    NULL,
    NULL,
    ft_handel_unreachable,		/*!< type 3 => unreachable */
    NULL,
    NULL,
    NULL,
    NULL,
    ft_handel_request,			/*!< type 8 => echo request */
    NULL,
    NULL,
    ft_handle_time,				/*!< type 11 => time exceeded  */
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
};

/**
 * @fn void ft_analyse_packet(const t_server *server, const void *buffer, size_t
 * size)
 *
 * @param server: current ping server
 * @param buffer: received packet memory buffer
 * @param size: size of the memory buffer
 *
 * @brief analyse the received packet from an icmp point of view
 *
 * Validate the ICMP part of the buffer, filter the response and determines the
 * response type.
 */
void	ft_analyse_packet(const t_server *server, const void *buffer, size_t size)
{
	const t_ip_packet	*ippacket = buffer;
	size_t				offset = 4 * ippacket->IHL;
	const t_icmp_packet	*icmppacket = buffer + offset;
	t_packet_handler	handler;

	if (size - offset < sizeof(*icmppacket)
		|| ft_checksum(icmppacket, size - offset) != 0)
	{
		dprintf(2, "ft_ping: recv: invalid icmp packet\n");
		return ;
	}
	if (icmppacket->type > 16 || g_phandler[icmppacket->type] == NULL)
	{
		dprintf(2, "ft_ping: icmp packet: invalid packet type\n");
		return;
	}
	handler = g_phandler[icmppacket->type];
	handler(server, ippacket, icmppacket, size - offset);
}
