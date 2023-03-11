/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_opttimeout.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 18:58:08 by gtoubol           #+#    #+#             */
/*   Updated: 2023/03/11 18:58:08 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/**
 * @file ft_opttimeout.c
 * @brief set the receive timeout
 *
 */

#include <stdint.h>
#include <stdio.h>

#include "ft_options.h"
#include "ft_ping.h"
#include "libft.h"

int ft_opttimeout(const char *arg, t_server *server)
{
	int errcode;
	int64_t value;

	value = ft_atoll(arg, &errcode);

	if (errcode || value < 0 || value > 2147483647)
	{
		dprintf(2, "%s: bad linger time: %s\n",
				"ft_ping", arg);
		return (-1);
	}
	server->timeout = (int32_t)value;
	return (0);
}
