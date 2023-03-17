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
 * @enum t_mtud
 * @brief define the kind of pmtud option
 *
 */
typedef enum {
	MTUD_DO = 0,
	MTUD_DONT = 1,
	MTUD_WANT = 2,
	NO_MTUD
} t_mtud;

#define CACHE_SIZE 3

/**
 * @struct t_cache
 * @brief cache the address resolution
 *
 * Serves as DNS resolution cache. Cache does not
 * expire.
 */
typedef struct {
	uint8_t		ncache;			 				/*!< Number of current cached addresses */
	uint32_t	ip[CACHE_SIZE];					/*!< Resolved IPs */
	char		name[CACHE_SIZE][NI_MAXHOST];	/*!< Resolved names */
}	t_cache;

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
	int32_t			mark;						/*!< Mark outgoing packets */
	int32_t			preload;					/*!< Number of preloaded packets */
	int32_t			interval;					/*!< Interval between sending */
	t_mtud			mtud;						/*!< Mtud otpion */
	int32_t			deadline;					/*!< Program deadline */
	int32_t			timeout;					/*!< Reception timeout */
	uint8_t			pattern[16];				/*!< Padding pattern */
	uint32_t		pattern_length;				/*!< Pattern length */
	int				verbose;					/*!< Verbosity option */
	uint8_t			ttl;						/*!< Echo request ttl */
	int				resolve;					/*!< Resolve option */
	t_cache			*cache;						/*!< Current address cache */
} t_server;

int32_t ft_init(int argc, const char **argv, t_server *server);
int32_t ft_loop(const t_server *server);
void ft_close(t_server *server);

#endif /* FT_PING_H */
