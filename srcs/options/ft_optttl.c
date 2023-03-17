/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_optttl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 11:37:32 by gtoubol           #+#    #+#             */
/*   Updated: 2023/03/17 11:37:32 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_optttl.c
 * @brief set the ttl of the packet
 *
 */

#include <stdint.h>
#include <stdio.h>

#include "ft_options.h"
#include "ft_ping.h"
#include "libft.h"

/**
 * @fn int ft_optttl(const char *s, t_server *server)
 *
 */
int ft_optttl(const char *s, t_server *server)
{
	int 	err;
	int64_t	val;

	val = ft_atoll(s, &err);
	if (err == 1)
	{
		dprintf(2, "%s: invalid argument: '%s'\n",
				"ft_ping", s);
		return (-1);
	}
	if (err == 2)
	{
		dprintf(2, "%s: invalid argument: '%s': Numerical result out of range\n",
				"ft_ping", s);
		return (-1);
	}
	if (val < 0 || val > 255)
	{
		dprintf(2, "%s: invalid argument: '%s': out of range: 0 <= value <= 255\n",
				"ft_ping", s);
		return (-1);
	}
	server->ttl = (uint8_t)val;
	return (0);
}
