/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dump_packet.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 11:14:58 by gtoubol           #+#    #+#             */
/*   Updated: 2023/03/17 11:14:58 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_dump_packet.c
 * @brief dump the content of a packet
 *
 */

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include "ft_packet.h"
#include "ft_utils.h"

/**
 * @fn void	ft_dump_packet(const t_ip_packet *ippacket, size_t size)
 *
 * @param ippacket: received IP packet
 * @param size: size of received packet
 *
 * @brief dump the content of the packet
 *
 */
void	ft_dump_packet(const t_ip_packet *ippacket, size_t size)
{
	const uint16_t	*buffer = (const uint16_t *)ippacket;
	size_t			i;

	dprintf(2, "Packet dump:\n");
	for (i = 0; i < size / sizeof(*buffer); i++)
	{
		dprintf(2, " %04hx", ft_swap_16bits(buffer[i]));
		if ((i & 0x7) == 7)
			dprintf(2, "\n");
	}
	if (i * sizeof(*buffer) != size)
		dprintf(2, " %02hhx", ((const uint8_t *)buffer)[i * sizeof(buffer) + 1]);
	dprintf(2, "\n");
}
