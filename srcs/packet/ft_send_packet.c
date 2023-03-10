/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_send_packet.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 21:39:16 by gtoubol           #+#    #+#             */
/*   Updated: 2023/03/06 21:39:16 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_send_packet.c
 *
 * @brief
 *
 */

#include <stdint.h>
#include <sys/socket.h>
#include <unistd.h>

#include "ft_packet.h"
#include "ft_ping.h"
#include "ft_statistics.h"

/**
 * @fn void ft_send_packet(const t_icmp_packet *packet, const t_server *server)
 *
 * @param packet: packet to send
 * @param server: current ping server
 *
 *
 */
void ft_send_packet(const t_icmp_packet *packet, const t_server *server)
{
	sendto(server->sockfd, packet, ICMP_ECHO_PACKET_LENGTH, 0, &server->s_addr, server->s_addrlen);
	ft_add_send();
}
