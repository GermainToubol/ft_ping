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

#include <arpa/inet.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <signal.h>

#include "ft_packet.h"
#include "ft_ping.h"
#include "ft_statistics.h"

static int		g_continue = 1;
static int		g_alarmed = 1;
static int32_t	g_clock = 0;

void tmp_quit(int i)
{
	(void)i;
	g_continue = 0;
}

void tmp_alarm(int i)
{
	(void)i;
	g_alarmed = 1;
	g_clock++;
	alarm(1);
}

void tmp_stats(int i)
{
	(void)i;
	ft_print_intermediate_stats();
}

static int ft_can_send_packet(const t_server *server);
static int ft_send_timing(const t_server *server);
static int ft_check_timeout(const t_server *server, int32_t delay);
static uint_least16_t	ft_preload(const t_server *server, t_icmp_packet *packet);

/**
 * @fn int32_t ft_loop(const t_server *server)
 *
 * @param server: current ping server
 *
 * @return -1 on failure, 0 otherwise
 *
 * @brief main loop wrapper
 *
 */
int32_t	ft_loop(const t_server *server)
{
	uint_least8_t	buffer[256];
	t_icmp_packet	*packet = (t_icmp_packet *)buffer;
	uint_least16_t	packet_number;
	int32_t			last_reception;
	uint64_t		buff_reception = 0;

	signal(SIGINT, tmp_quit);
	signal(SIGQUIT, tmp_stats);
	signal(SIGALRM, tmp_alarm);

	ft_init_packet(packet, server);
	last_reception = 0;
	alarm(1);
	if (server->verbose)
		dprintf(1, "PING %s (%s) 56(84) bytes of data idx = %hu\n", server->name, server->ip, server->id);
	else
		dprintf(1, "PING %s (%s) 56(84) bytes of data\n", server->name, server->ip);
	packet_number = ft_preload(server, packet);
	while (g_continue
		   && (server->deadline == 0
			   || server->deadline > g_clock)
		   && ft_check_timeout(server, g_clock - last_reception)
		   && (server->count == 0
			   || server->count != (int64_t)ft_get_received()))
	{
		ft_mark_packet(packet, packet_number);
		if (ft_send_timing(server) && ft_can_send_packet(server))
		{
			if (server->flood){
				dprintf(2, ".\r");
			}
			ft_send_packet(packet, server);
			packet_number++;
		}
		g_alarmed = 0;
		ft_receive_packet(server);
		if (buff_reception != ft_get_received())
		{
			buff_reception = ft_get_received();
			last_reception = g_clock;
		}
	}
	alarm(0);
	dprintf(1, "\n--- %s ping statistics ---\n", server->name);
	ft_print_final_stats();
	return (0);
}

/**
 * @fn int ft_can_send_packet(const t_server *server)
 *
 * @param server: current ping server
 *
 * @return 1 if sending is allowed, 0 otherwise
 *
 * @brief check if sending packet is allowed.
 *
 */
static int ft_can_send_packet(const t_server *server)
{
	return (server->count == 0 || (uint64_t)server->count > ft_get_send());
}

/**
 * @fn int ft_send_timing(const t_server *server)
 *
 * @param server: current ping server
 *
 * @return 1 on send timing, 0 otherwise
 *
 */
static int ft_send_timing(const t_server *server)
{
	return (server->flood
			|| (g_alarmed
				&& g_clock % server->interval == 0));
}

/**
 * @fn int ft_check_timeout(const t_server *server, int32_t delay)
 *
 * @param server: current ping server
 * @param delay: current delay since last packet reception
 *
 * @return 1 if timeout did not expired, 0 otherwise
 *
 */
static int ft_check_timeout(const t_server *server, int32_t delay)
{
	if (server->timeout != 0 && (server->timeout <= delay && ft_get_send() != ft_get_received()))
	{
		dprintf(2, "ft_ping: reception timeout expired\n");
		return (0);
	}
	return (1);
}

/**
 * @fn uint_least16_t ft_preload(const t_server *server, t_packet *packet)
 *
 * @param server: current ping server
 * @param packer: base packet
 *
 * @return the next packet number
 *
 * @brief send the (n-1) preloaded packets
 *
 */
static uint16_t	ft_preload(const t_server *server, t_icmp_packet *packet)
{
	uint_least16_t	packet_number = 1;

	for (int i = 0; i < server->preload - 1 && ft_can_send_packet(server); i++)
	{
		ft_mark_packet(packet, packet_number);
		ft_send_packet(packet, server);
		packet_number++;
	}
	return (packet_number);
}
