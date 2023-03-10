/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_optusage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 13:09:28 by gtoubol           #+#    #+#             */
/*   Updated: 2023/03/10 13:09:28 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_optusage.c
 * @brief option -h
 *
 */

#include <stdint.h>
#include <stdlib.h>

#include "ft_options.h"
#include "ft_ping.h"

/**
 * @fn int ft_optusage(const char *arg, t_server *server)
 *
 * @param arg: ignored parameter
 * @param server: current ping server
 *
 * show usage and quit
 *
 */
int ft_optusage(const char *arg, t_server *server)
{
	(void)arg;
	(void)server;
	ft_usage();
	exit(0);
}
