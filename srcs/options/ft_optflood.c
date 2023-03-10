/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_optflood.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 14:49:03 by gtoubol           #+#    #+#             */
/*   Updated: 2023/03/10 14:49:03 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/**
 * @file ft_optflood.c
 * @brief allow to flood
 *
 */

#include <stdio.h>
#include <unistd.h>

#include "ft_options.h"
#include "ft_ping.h"

/**
 * @fn int ft_optflood(const char *arg, t_server *server)
 *
 */
int	ft_optflood(const char *arg, t_server *server)
{
	(void)arg;
	server->flood = 1;
	if (getuid() == 0)
		return (0);
	dprintf(2, "ft_ping: cannot flood; minimal interval allowed for user is 200ms");
	return (-1);
}
