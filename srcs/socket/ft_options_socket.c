/**
 * @file ft_options_socket.c
 * @brief apply the socket-related options
 *
 */

#include <errno.h>
#include <netinet/in.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>

#include "ft_ping.h"
#include "ft_socket.h"

static int ft_apply_recvtimeo(const t_server *server);
static int ft_apply_mark(const t_server *server);
static int ft_apply_mtu(const t_server *server);
static int ft_apply_ttl(const t_server *server);

/**
 * @fn int32_t ft_options_socket(const t_server *server)
 *
 * @param server: current ping server
 *
 * @return -1 on failure, 0 otherwise
 *
 * @brief apply socket-related options from the server
 *
 */
int32_t	ft_options_socket(const t_server *server)
{
	if (ft_apply_recvtimeo(server))
		return (-1);
	if (ft_apply_mark(server))
		return (-1);
	if (ft_apply_mtu(server))
		return (-1);
	if (ft_apply_ttl(server))
		return (-1);
	return (0);
}

static int ft_apply_recvtimeo(const t_server *server)
{
	struct timeval delta = {.tv_sec = 0x7fffffff, .tv_usec = 0};

	if (server->flood)
		delta = (struct timeval){0, 10000};
	if(setsockopt(server->sockfd, SOL_SOCKET, SO_RCVTIMEO, &delta, sizeof(delta)))
	{
		dprintf(2, "ft_ping: socket: %s\n", strerror(errno));
		return (-1);
	}
	return (0);
}

static int ft_apply_mark(const t_server *server)
{
	if (server->mark < 0)
		return (0);
	if (setsockopt(server->sockfd, SOL_SOCKET, SO_MARK, &server->mark,
				   sizeof(server->mark)))
	{
		dprintf(2, "ft_ping: Warning: Failed to set mark: %d: %s\n",
				server->mark, strerror(errno));
	}
	return (0);
}

static int ft_apply_mtu(const t_server *server)
{
	const int opt[3] = {
		IP_PMTUDISC_DO,
		IP_PMTUDISC_DONT,
		IP_PMTUDISC_WANT
	};

	if (server->mtud == NO_MTUD)
		return (0);
	if (setsockopt(server->sockfd, SOL_IP, IP_MTU_DISCOVER, opt + 1,
				   sizeof(opt[0])))
	{
		dprintf(2, "ft_ping: socket: failed to apply pmtud: %s\n",
				strerror(errno));
		return (-1);
	}
	return (0);
}

static int ft_apply_ttl(const t_server *server)
{
	if (setsockopt(server->sockfd, IPPROTO_IP, IP_TTL, &server->ttl,
				   sizeof(server->ttl)))
	{
		dprintf(2, "ft_ping: socket: Failed to set ttl: %hhu: %s\n",
				server->ttl, strerror(errno));
		return (-1);
	}
	return (0);
}
