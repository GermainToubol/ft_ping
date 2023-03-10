/**
 * @file ft_options_socket.c
 * @brief apply the socket-related options
 *
 */

#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>

#include "ft_ping.h"
#include "ft_socket.h"

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
	int errcode;

	struct timeval delta = {.tv_sec = 0x7fffffff, .tv_usec = 0};
	if (server->flood)
	{
		delta.tv_sec = 0;
		delta.tv_usec = 10000;
	}
	errcode = setsockopt(server->sockfd, SOL_SOCKET, SO_RCVTIMEO, &delta, sizeof(delta));
	if (errcode)
	{
		dprintf(2, "ft_ping: socket: %s\n", strerror(errno));
		return (-1);
	}
	return (0);
}
