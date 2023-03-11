/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_optdeadline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 18:28:57 by gtoubol           #+#    #+#             */
/*   Updated: 2023/03/11 18:28:57 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_optdeadline.c
 * @brief set a delay to complete the ping sequence
 *
 */

#include <stdint.h>
#include <stdio.h>

#include "ft_options.h"
#include "ft_ping.h"
#include "libft.h"

/**
 * @fn int	ft_optdeadline(const char *arg, t_server *server)
 * @brief set the deadline in second
 *
 */
int	ft_optdeadline(const char *arg, t_server *server)
{
	int	errcode;
	int64_t	value;

	value = ft_atoll(arg, &errcode);
	if (errcode == 1)
	{
		dprintf(2, "%s: invalid argument: '%s'\n",
				"ft_ping", arg);
		return (-1);
	}
	if (errcode == 2)
	{
		dprintf(2, "%s: invalid argument: '%s': Numerical result out of range\n",
				"ft_ping", arg);
		return (-1);
	}
	if (value < 0 || value > 2147483647)
	{
		dprintf(2, "%s: invalid argument: '%s': out of range: 0 <= value <= 2147483647\n",
				"ft_ping", arg);
		return (-1);
	}
	server->deadline = (int32_t)value;
	return (0);
}
