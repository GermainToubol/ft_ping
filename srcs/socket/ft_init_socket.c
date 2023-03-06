/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_socket.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 09:12:54 by gtoubol           #+#    #+#             */
/*   Updated: 2023/03/06 09:12:54 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_init_socket.c
 *
 * Resolve the name and create a socket accordingly.
 *
 */

#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

#include "ft_ping.h"
#include "ft_socket.h"
#include "libft.h"

/**
 * @fn int32_t ft_init_socket(t_server *server)
 * @param server: the actual server
 * @return 1 if an error occures, 0 otherwise
 *
 * @brief name resolution and socket creation
 *
 */
int32_t ft_init_socket(t_server *server)
{
	const struct addrinfo	hint = {
		.ai_flags = 0,
		.ai_family = AF_INET,
		.ai_socktype = SOCK_RAW,
		.ai_protocol = IPPROTO_ICMP,
		.ai_addrlen = 0,
		.ai_addr = NULL,
		.ai_canonname = NULL,
		.ai_next = NULL
	};
	struct addrinfo			*pai;
	int						errcode;

	errcode = getaddrinfo(server->name, NULL, &hint, &pai);
	if (errcode == 0)
	{
		dprintf(2, "ft_ping: %s: %s\n", server->name, gai_strerror(errcode));
		return (-1);
	}
	ft_memcpy(&server->s_addr, pai->ai_addr, sizeof(*pai->ai_addr));
	server->s_addrlen = pai->ai_addrlen;
	freeaddrinfo(pai);
	server->sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (server->sockfd < 0)
	{
		dprintf(2, "ft_ping: socket: %s\n", strerror(errno));
		return (-1);
	}
	return (0);
}
