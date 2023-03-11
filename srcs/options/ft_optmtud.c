/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_optmtud.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 17:59:34 by gtoubol           #+#    #+#             */
/*   Updated: 2023/03/11 17:59:34 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_optmtud.c
 * @brief select the mtud value
 *
 */

#include <stdio.h>

#include "ft_options.h"
#include "ft_ping.h"
#include "libft.h"

/**
 * @fn int	ft_optmtud(const char *arg, t_server *server)
 *
 */
int	ft_optmtud(const char *arg, t_server *server)
{
	if (!ft_strcmp(arg, "do"))
	{
		server->mtud = MTUD_DO;
		return (0);
	}
	if (!ft_strcmp(arg, "dont"))
	{
		server->mtud = MTUD_DONT;
		return (0);
	}
	if (!ft_strcmp(arg, "want"))
	{
		server->mtud = MTUD_WANT;
		return (0);
	}
	dprintf(2, "%s: invalid -M argument: %s\n", "ft_ping", arg);
	return (-1);
}
