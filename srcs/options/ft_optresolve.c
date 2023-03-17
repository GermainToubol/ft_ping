/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_optresolve.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 20:30:00 by gtoubol           #+#    #+#             */
/*   Updated: 2023/03/17 20:30:00 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_optresolve.c
 * @brief Add a resolution option
 *
 */

#include "ft_options.h"
#include "ft_ping.h"

/**
 * @fn int ft_optresolve(const char *arg, t_server *server)
 *
 */
int	ft_optresolve(const char *arg, t_server *server)
{
	(void)arg;
	server->resolve = 0;
	return (0);
}
