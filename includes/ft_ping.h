/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 22:03:51 by gtoubol           #+#    #+#             */
/*   Updated: 2023/03/02 22:03:51 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_ping.h
 * @brief General requirement header
 *
 */

#ifndef FT_PING_H
#define FT_PING_H

#include <netdb.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/socket.h>

typedef uint64_t t_clock;

/**
 * @struct t_server
 * @brief Server core
 *
 * Gather all the properties of the server.
 */
typedef struct {
	const char		*name;						/*!< Requested server */
	char			ip[16];						/*!< Converted address to ip string */
	struct sockaddr	s_addr;						/*!< Resolved address */
	socklen_t		s_addrlen;
	char			resolved_name[NI_MAXHOST];	/*!< Reverse resolved name */
	int				sockfd;						/*!< Socket fd */

	t_clock			clock;						/*!< Hold the clock tick */

	uint_least16_t	id;							/*!< Packet identifier */
	int				flood;						/*!< Flood label */
	int64_t			count;						/*!< Counter */
} t_server;

int32_t ft_init(int argc, const char **argv, t_server *server);
int32_t ft_loop(const t_server *server);
void ft_close(t_server *server);

#endif /* FT_PING_H */
