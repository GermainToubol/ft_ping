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
	char			*name;		/*!< Requested server */
	char			ip[16];		/*!< Converted address to ip string */
	struct sockaddr	s_addr;		/*!< Resolved address */
	socklen_t		s_addrlen;
	char			resolved_name[NI_MAXHOST]; /*!< Reverse resolved name */
	t_clock			clock;		/*!< Hold the clock tick */
} t_server;



#endif /* FT_PING_H */
