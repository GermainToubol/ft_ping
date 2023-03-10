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
#include <sys/socket.h>
#include <unistd.h>
#include <signal.h>

#include "ft_packet.h"
#include "ft_ping.h"
#include "ft_statistics.h"

int g_continue = 1;
int g_alarmed = 1;

void tmp_quit(int i)
{
	(void)i;
	g_continue = 0;
}

void tmp_alarm(int i)
{
	(void)i;
	g_alarmed = 1;
	alarm(1);
}

void tmp_stats(int i)
{
	(void)i;
	ft_print_intermediate_stats();
}

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

	signal(SIGINT, tmp_quit);
	signal(SIGQUIT, tmp_stats);
	signal(SIGALRM, tmp_alarm);

	ft_init_packet(packet, server);
	struct timeval delta = {.tv_sec = 0x7fffffff, .tv_usec = 0};
	setsockopt(server->sockfd, SOL_SOCKET, SO_RCVTIMEO, &delta, sizeof(delta));
	packet_number = 1;
	alarm(1);
	while (g_continue)
	{
		ft_mark_packet(packet, packet_number);
		if (g_alarmed)
		{
			ft_send_packet(packet, server);
			packet_number++;
		}
		g_alarmed = 0;
		ft_receive_packet(server);
	}
	ft_print_final_stats();
	return (0);
}
