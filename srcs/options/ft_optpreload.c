/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_optpreload.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 10:48:42 by gtoubol           #+#    #+#             */
/*   Updated: 2023/03/11 10:48:42 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_optpreload.c
 * @brief Set the number of preloaded packets
 *
 */

#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

#include "ft_options.h"
#include "ft_ping.h"
#include "libft.h"

int	ft_optpreload(const char *arg, t_server *server)
{
	int	err;
	int64_t	val;

	val = ft_atoll(arg, &err);
	if (err == 1)
	{
		dprintf(2, "%s: invalid argument: '%s'\n",
				"ft_ping", arg);
		return (-1);
	}
	if (err == 2)
	{
		dprintf(2, "%s: invalid argument: '%s': Numerical result out of range\n",
				"ft_ping", arg);
		return (-1);
	}
	if (val < 1 || val > 65536)
	{
		dprintf(2, "%s: invalid argument: '%s': out of range: 1 <= value <= 65536\n",
				"ft_ping", arg);
		return (-1);
	}
	if (val > 3 && getuid() != 0)
	{
		dprintf(2, "%s: cannot set preload to value greater than 3: %ld\n",
				"ft_ping", val);
		return (-1);
	}
	server->preload = (int32_t)val;
	return (0);
}
