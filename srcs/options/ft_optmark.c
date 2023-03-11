/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_optmark.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 09:29:35 by gtoubol           #+#    #+#             */
/*   Updated: 2023/03/11 09:29:35 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_optmark.c
 * @brief mark the outgoing packet
 *
 */

#include <stdint.h>
#include <stdio.h>

#include "ft_ping.h"
#include "ft_options.h"
#include "libft.h"

int ft_optmark(const char *arg, t_server *server)
{
	int	errcode;
	int64_t	res;

	res = ft_atoll(arg, &errcode);
	if (errcode == 1) {
		dprintf(2, "ft_ping: invalid argument: '%s'\n",
				arg);
		return (-1);
	}
	if (errcode == 2) {
		dprintf(2, "ft_ping: invalid argument: '%s': Numerical result out of range\n",
				arg);
		return (-1);
	}
	if (res < 0 || res > 0x7fffffffLL) {
		dprintf(2, "ft_ping: invalid argument: '%s': out of range: 0 <= value <= 2147483647\n",
				arg);
		return (-1);
	}
	server->mark = (int32_t)res;
	return (0);

}
