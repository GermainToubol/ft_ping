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

#include <arpa/inet.h>
#include <stddef.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/time.h>

#include "ft_packet.h"
#include "ft_ping.h"
#include "ft_utils.h"

/**
 * @fn void ft_handel_response(const t_server *server,
 * const t_ip_packet *ip_packet, const t_icmp_packet *packet,
 * size_t size)
 *
 * @param server: current ping server
 * @param packer: incomming icmp packet (type 0)
 * @param size: size of packet
 *
 * @brief analyse the response
 */
void ft_handel_response(
	const t_server *server,
	const t_ip_packet *ip_packet,
	const t_icmp_packet *packet,
	size_t size)
{
	struct timeval	*sendtime;
	struct timeval	recvtime;
	float			delay;
	char			buffer[16];

	if (size != ICMP_ECHO_PACKET_LENGTH
		|| server->id != packet->echo.id)
		return;
	gettimeofday(&recvtime, NULL);
	sendtime = (struct timeval *)packet->data;
	delay = ft_getdelay(sendtime, &recvtime);
	dprintf(2, "%ld bytes from %s: icmp_seq=%d ttl=%d time=%.3f ms\n",
			size, inet_ntop(AF_INET, &ip_packet->source, buffer, 16), ft_swap_16bits(packet->echo.seq), ip_packet->ttl, delay);
}

/**
 * @fn void ft_handel_request(const t_server *server,
 * const t_ip_packet *ip_packet, const t_icmp_packet *packet,
 * size_t size)
 *
 * @param server: current ping server
 * @param packet: incomming icmp packet (type 8)
 * @param size: size of the packet
 *
 * @brief drop the packet
 */
void ft_handel_request(
	const t_server *server,
	const t_ip_packet *ip_packet,
	const t_icmp_packet *packet,
	size_t size)
{
	(void)ip_packet;
	(void)server;
	(void)packet;
	(void)size;
	dprintf(2, "ft_ping: stop pinging yourself!\n");
}

/**
 * @fn void ft_handel_unreachable(const t_server *server,
 * const t_ip_packet *ip_packet, const t_icmp_packet *packet,
 * size_t size)
 *
 * @param server: current ping server
 * @param ip_packet: incomming ip packet
 * @param packet: incomming icmp packet
 * @param size: size of the icmp packet
 *
 * @brief analyse the icmp unreachable packet
 */
void ft_handel_unreachable(
	const t_server *server,
	const t_ip_packet *ip_packet,
	const t_icmp_packet *packet,
	size_t size)
{
	char buffer[16];
	const char reason[6][64] = {"net unreachable", "host unreachable", "protocol unreachable", "port unreachable", "fragmentation needed and DF set", "source route failed"};

	if (packet->code > 5)
		return ;
	dprintf(2, "From %s %s\n", inet_ntop(AF_INET, &ip_packet->source, buffer, 16), reason[packet->code]);
	(void)packet;
	(void)server;
	(void)size;
}
