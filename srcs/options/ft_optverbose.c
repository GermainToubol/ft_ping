/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_optverbose.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 11:51:51 by gtoubol           #+#    #+#             */
/*   Updated: 2023/03/12 11:51:51 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_optverbose.c
 * @brief add verbose option
 *
 */

#include "ft_options.h"
#include "ft_ping.h"

/**
 * @fn int ft_optverbose(const char *arg, t_server *server)
 *
 */
int ft_optverbose(const char *arg, t_server *server)
{
	(void)arg;
	server->verbose = 1;
	return (0);
}
