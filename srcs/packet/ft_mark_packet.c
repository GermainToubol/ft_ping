/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mark_packet.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 17:31:25 by gtoubol           #+#    #+#             */
/*   Updated: 2023/03/06 17:31:25 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_mark_packet.c
 * @brief prepare packet for sending
 *
 * Put the las packet informations like packet_number and checksum
 */

#include <stddef.h>
#include <stdint.h>
#include <sys/time.h>

#include "ft_packet.h"
#include "ft_utils.h"
#include "libft.h"

/**
 * @fn void ft_mark_packet(t_icmp_packet *packet, uint_least16_t packet_number)
 *
 * @param packet: current outgoing packet
 * @param packet_number: current icm sequence number
 *
 * Apply the timestamp, packet number to the packet and recompute the packet checksum.
 */
void ft_mark_packet(t_icmp_packet *packet, uint_least16_t packet_number)
{
	struct timeval	current_time;

	packet->checksum = 0;
	packet->echo.seq = ft_swap_16bits(packet_number); /* Network is in reverse order endianness */
	gettimeofday(&current_time, NULL);
	ft_memcpy(packet->data, &current_time, sizeof(current_time));
	packet->checksum = ft_checksum(packet, ICMP_ECHO_PACKET_LENGTH);
}
