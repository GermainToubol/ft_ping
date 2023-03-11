/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_optinterval.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 16:47:17 by gtoubol           #+#    #+#             */
/*   Updated: 2023/03/11 16:47:17 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_optinterval.c
 * @brief select interval between emissions
 *
 */

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

#include "ft_options.h"
#include "ft_ping.h"
#include "libft.h"

/**
 * @fn int ft_optinterval(const char *arg, t_server *server)
 *
 * @brief set the interval between two packets
 *
 */
int ft_optinterval(const char *arg, t_server *server)
{
	int		err;
	int64_t	val;

	val = ft_atoll(arg, &err);
	if (err || val > 2147483 || val < -2147484)
	{
		dprintf(2, "%s: bad timing interval: %s\n",
				"ft_ping", arg);
		return (-1);
	}
	if (val < 1)
		return (ft_optflood(NULL, server));
	server->interval = (int32_t)val;
	return (0);
}
