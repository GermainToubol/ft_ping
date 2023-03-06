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

#include <stdint.h>

#include "ft_packet.h"
#include "ft_ping.h"

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
}
