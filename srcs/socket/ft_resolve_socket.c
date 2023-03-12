/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_resolve_socket.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 09:40:14 by gtoubol           #+#    #+#             */
/*   Updated: 2023/03/06 09:40:14 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_resolve_socket.c
 *
 * Do the reverse DNS resolution on the main address name.
 */

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>

#include "ft_ping.h"
#include "ft_socket.h"

/**
 * @fn int32_t ft_resolve_socket(t_server *server)
 * @param server: current ping server
 * @return -1 on failure,0 otherwise.
 *
 * @brief do the reverse DNS query on man address
 *
 * Do the revere DNS query and pass the resolved name to the server.
 */
int32_t	ft_resolve_socket(t_server *server)
{
	int	errcode;

	inet_ntop(AF_INET, &((struct sockaddr_in *)&server->s_addr)->sin_addr , server->ip, 16);
	errcode = getnameinfo(&server->s_addr, server->s_addrlen, server->resolved_name, NI_MAXHOST, NULL, 0, 0);
	if (errcode)
	{
		dprintf(2, "ft_ping: %s: %s\n", server->ip, gai_strerror(errcode));
		return (-1);
	}
	return (0);
}
