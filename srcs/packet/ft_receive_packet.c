/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_receive_packet.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 22:39:13 by gtoubol           #+#    #+#             */
/*   Updated: 2023/03/06 22:39:13 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_receive_packet.c
 *
 * @brief receive a packet and parse it
 */

#include <stdio.h>
#include <stdint.h>
#include <sys/socket.h>
#include <sys/types.h>

#include "ft_packet.h"
#include "libft.h"

/**
 * @fn void ft_receive_packet(const t_server *server)
 *
 * @param server: current ping server
 */
void ft_receive_packet(const t_server *server)
{
	uint8_t buffer[MAX_IPPACKET_LENGTH];
	struct iovec   iov[1];
	struct msghdr  msg;
	ssize_t size;

	ft_memset(&msg,   0, sizeof(msg));
	ft_memset(iov,    0, sizeof(iov));
	iov[0].iov_base = buffer;
	iov[0].iov_len  = sizeof(buffer);
	msg.msg_iov     = iov;
	msg.msg_iovlen  = 1;

	size = recvmsg(server->sockfd, &msg, 0);
	if (size < 0)
		return ;
	if (!ft_isvalid_ip_packet((const t_ip_packet *)buffer, size))
	{
		dprintf(2, "ft_ping: recv: invalid IP packet\n");
		return ;
	}
}
