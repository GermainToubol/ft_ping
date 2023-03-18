/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_resolve.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 21:12:16 by gtoubol           #+#    #+#             */
/*   Updated: 2023/03/17 21:12:16 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_resolve.c
 * @brief get the resolved name
 *
 */

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/socket.h>

#include "ft_packet.h"
#include "ft_ping.h"
#include "libft.h"

/**
 * @fn const char *ft_resolve(const t_server *server, uint32_t ip)
 *
 * @param server: current ping server
 * @param ip: ip to resolve
 *
 * @return pointer to the resolved address, NULL on failure
 *
 * @brief Resolve the address and store it in the cache
 *
 */
const char	*ft_resolve(const t_server *server, uint32_t ip)
{
	uint8_t	i;

	for (i = 0; i < server->cache->ncache; i++)
	{
		if (ip == server->cache->ip[i])
			return (server->cache->name[i]);
	}
	if (i == CACHE_SIZE)
	{
		if (server->verbose)
			dprintf(2, "ft_ping: warning: cache full\n");
		return (inet_ntop(AF_INET, &ip, server->cache->tmp, 16));
	}
	struct sockaddr_in addr = {
		.sin_family = AF_INET,
		.sin_port = 0,
		.sin_addr = {
			.s_addr = ip
		},
		.sin_zero = {0},
	};
	int ret = getnameinfo((const struct sockaddr *)&addr, sizeof(addr),
				server->cache->name[i], NI_MAXHOST,
				NULL, 0, NI_NAMEREQD);
	if (ret != 0)
	{
		inet_ntop(AF_INET, &ip, server->cache->tmp, 16);
		ft_strlcpy(server->cache->name[i], server->cache->tmp, NI_MAXHOST);
	}
	server->cache->ncache++;
	server->cache->ip[i] = ip;
	return (server->cache->name[i]);
}
