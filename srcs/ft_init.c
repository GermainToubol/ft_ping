/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 11:47:29 by gtoubol           #+#    #+#             */
/*   Updated: 2023/03/06 11:47:29 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/**
 * @file ft_init.c
 * @brief program initialisation
 *
 * Wrap around the server initialisation, option parsing
 */
#include <stdio.h>
#include <stdint.h>

#include "ft_options.h"
#include "ft_ping.h"
#include "ft_socket.h"
#include "ft_utils.h"

/**
 * @fn int32_t ft_init(int argc, const char **argv, t_server *server)
 *
 * @param argc: number of arguments passed to the program
 * @param argv: list of program's arguments
 * @param server: current ping server
 *
 * @return -1 on initialisation error, 0 otherwise
 *
 * @brief parse the arguments and initialize the server
 *
 * Gather all argument parsing steps and initialize the server accordingly
 */
int32_t	ft_init(int argc, const char **argv, t_server *server)
{
	if (ft_parseopts(argc, argv, server))
		return (-1);
	if (ft_is_ip(server->name))
		server->resolve = 0;

	/* List of OR because each function is 0 on valid and !0 otherwise */
	if (ft_init_socket(server)
		|| ft_resolve_socket(server)
		|| ft_options_socket(server))
		return (-1);
	return (0);
}
