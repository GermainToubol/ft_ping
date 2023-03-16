/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isvalid_ip_packet.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 11:36:49 by gtoubol           #+#    #+#             */
/*   Updated: 2023/03/07 11:36:49 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_isvalid_ip_packet.c
 * @brief ip packet checker
 *
 */

#include <stdint.h>

#include "ft_packet.h"
#include "ft_utils.h"

/**
 * @fn int ft_isvalid_ip_packet(const t_ip_packet *packet, size_t size)
 *
 * @param packet: received ip packet
 * @param size: size of the packet buffer
 *
 * @return 1 if the packet is a valid IP packet, 0 otherwise
 *
 * @brief inspect the current packet
 *
 * Check the packet header and packet length to verify the packet is valid
 * as IP packet.
 */
int	ft_isvalid_ip_packet(const t_ip_packet *packet, size_t size)
{
	size_t	ihl;

	if (size < sizeof(*packet))
		return (IP_ERROR_BADSIZE);
	ihl = packet->IHL * 4;		/* 4 octets by 32 bits parts */
	if (size < ihl)
		return (IP_ERROR_INVALID_HEADER_SIZE);
	if (packet->version != 4)
		return (IP_ERROR_BAD_VERSION);
	if (ft_checksum(packet, ihl) != 0)
		return (IP_ERROR_INVALID_CHECKSUM);
	if (ft_swap_16bits(packet->length) != size)
		return (IP_ERROR_INCOMPLETE_PACKET);
	return (IP_ERROR_SUCCESS);
}
