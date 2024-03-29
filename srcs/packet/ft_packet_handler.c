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
#include <stdint.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/time.h>

#include "ft_packet.h"
#include "ft_ping.h"
#include "ft_statistics.h"
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
	if (!server->flood)
	{
		if (!server->resolve)
			dprintf(1, "%ld bytes from %s: icmp_seq=%d ttl=%d time=%.3f ms\n",
					size, inet_ntop(AF_INET, &ip_packet->source, buffer, 16),
					ft_swap_16bits(packet->echo.seq), ip_packet->ttl, delay);
		else
			dprintf(1, "%ld bytes from %s (%s): icmp_seq=%d ttl=%d time=%.3f ms\n",
					size, ft_resolve(server, ip_packet->source),
					inet_ntop(AF_INET, &ip_packet->source, buffer, 16),
					ft_swap_16bits(packet->echo.seq), ip_packet->ttl, delay);
	}
	else
		dprintf(1, "/\r");
	ft_add_received_valid(delay);
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
	(void)packet;
	(void)size;
	ft_receive_packet(server);
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
	char		buffer[16];
	const char	reason[6][64] = {
		"Destination Network Unreachable",
		"Destination Host Unreachable",
		"Destination Protocol Unreachable",
		"Destination Port Unreachable",
		"Fragmentation needed and DF set",
		"Source Route Failed"
	};

	if (packet->code > 5)
		return ;
	if (!server->flood)
	{
		if (!server->resolve)
			dprintf(1, "%ld bytes from %s: %s\n",
					size,
					inet_ntop(AF_INET, &ip_packet->source, buffer, 16),
					reason[packet->code]);
		else
		{
			dprintf(1, "%ld bytes from %s (%s): %s\n",
					size, ft_resolve(server, ip_packet->source),
					inet_ntop(AF_INET, &ip_packet->source, buffer, 16),
					reason[packet->code]);
		}
		if (server->verbose)
			ft_dump_packet(ip_packet, size);
	}
	ft_add_received_error();
}

/**
 * @fn void ft_handle_time(const t_server *server,
 * const t_ip_packet *ip_packet, cont t_icmp_packet *packet,
 * size_t size)
 *
 * @param server: current ping server
 * @param ip_packet: incomming ip packet
 * @param packet: incomming icmp packet
 * @param size: size of the icmp packet
 *
 * @brief analyse the icmp time exceeded packet
 */
void ft_handle_time(
	const t_server *server,
	const t_ip_packet *ip_packet,
	const t_icmp_packet *packet,
	size_t size)
{
	char		buffer[16];
	const char	reason[2][64] = {
		"Time to live exceeded",
		"Fragment reassembly time exceeded"
	};

	if (packet->code > 1)
		return ;
	if (!server->flood)
	{
		if (!server->resolve)
			dprintf(1, "%ld bytes from %s: %s\n",
					size, inet_ntop(AF_INET, &ip_packet->source, buffer, 16), reason[packet->code]);
		else
			dprintf(1, "%ld bytes from %s (%s): %s\n",
					size, ft_resolve(server, ip_packet->source),
					inet_ntop(AF_INET, &ip_packet->source, buffer, 16), reason[packet->code]);
		if (server->verbose)
			ft_dump_packet(ip_packet, size);
	}
	ft_add_received_error();
}

/**
 * @fn void ft_handle_problem(const t_server *server,
 * const t_ip_packet *ip_packet, cont t_icmp_packet *packet,
 * size_t size)
 *
 * @param server: current ping server
 * @param ip_packet: incomming ip packet
 * @param packet: incomming icmp packet
 * @param size: size of the icmp packet
 *
 * @brief analyse the icmp parameter problem packet
 */
void ft_handle_problem(
	const t_server *server,
	const t_ip_packet *ip_packet,
	const t_icmp_packet *packet,
	size_t size)
{
	char		buffer[16];

	if (!server->flood)
	{
		if (!server->resolve)
			dprintf(1, "%ld bytes from %s: Problem at byte %hhu\n",
					size, inet_ntop(AF_INET, &ip_packet->source, buffer, 16), packet->problem.ptr);
		else
			dprintf(1, "%ld bytes from %s (%s): Problem at byte %hhu\n",
					size, ft_resolve(server, ip_packet->source),
					inet_ntop(AF_INET, &ip_packet->source, buffer, 16), packet->problem.ptr);

		if (server->verbose)
			ft_dump_packet(ip_packet, size);
	}
	ft_add_received_error();
}

/**
 * @fn void ft_handle_quench(const t_server *server,
 * const t_ip_packet *ip_packet, cont t_icmp_packet *packet,
 * size_t size)
 *
 * @param server: current ping server
 * @param ip_packet: incomming ip packet
 * @param packet: incomming icmp packet
 * @param size: size of the icmp packet
 *
 * @brief analyse the icmp quench packet
 */
void ft_handle_quench(
	const t_server *server,
	const t_ip_packet *ip_packet,
	const t_icmp_packet *packet,
	size_t size)
{
	char		buffer[16];

	if (packet->code != 0)
		return ;
	if (!server->flood)
	{
		if (!server->resolve)
			dprintf(1, "%ld bytes from %s: Quenched pac\n",
					size, inet_ntop(AF_INET, &ip_packet->source, buffer, 16));
		else
			dprintf(1, "%ld bytes from %s (%s): Quenched pac\n",
					size, ft_resolve(server, ip_packet->source),
					inet_ntop(AF_INET, &ip_packet->source, buffer, 16));

		if (server->verbose)
			ft_dump_packet(ip_packet, size);
	}
	ft_add_received_error();
}

/**
 * @fn void ft_handle_redirect(const t_server *server,
 * const t_ip_packet *ip_packet, const t_icmp_packet *packet,
 * size_t size)
 *
 * @param server: current ping server
 * @param ip_packet: incomming ip packet
 * @param packet: incomming icmp packet
 * @param size: size of the icmp packet
 *
 * @brief analyse the icmp redirect packet
 */
void ft_handle_redirect(
	const t_server *server,
	const t_ip_packet *ip_packet,
	const t_icmp_packet *packet,
	size_t size)
{
	char		buffer[16];
	char		buffer2[16];
	const char	reason[4][64] = {
		"Redirect datagrams for the Network",
		"Redirect datagrams for the Host",
		"Redirect datagrams for the Type of Service and Network",
		"Redirect datagrams for the Type of Service and Host"
	};

	if (packet->code > 3)
		return ;
	if (!server->flood)
	{
		if (!server->resolve)
			dprintf(1, "%ld bytes from %s: %s (%s)\n",
					size, inet_ntop(AF_INET, &ip_packet->source, buffer, 16), reason[packet->code],
					inet_ntop(AF_INET, &packet->gateway.address, buffer2, 16));
		else
			dprintf(1, "%ld bytes from %s (%s): %s (%s)\n",
					size, ft_resolve(server, ip_packet->source),
					inet_ntop(AF_INET, &ip_packet->source, buffer, 16), reason[packet->code],
					inet_ntop(AF_INET, &packet->gateway.address, buffer2, 16));
		if (server->verbose)
			ft_dump_packet(ip_packet, size);
	}
	ft_add_received_error();
}
