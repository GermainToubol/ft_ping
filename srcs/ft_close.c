/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 12:19:13 by gtoubol           #+#    #+#             */
/*   Updated: 2023/03/06 12:19:13 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/**
 * @file ft_close.c
 * @brief clear the ping server
 *
 */

#include "ft_ping.h"
#include "ft_socket.h"

/**
 * @fn void ft_close(t_server *server)
 *
 * @param server: current ping server
 *
 * @brief cleanup the current server
 *
 * Wrapper around all cleanup utilities to close the server
 */
void	ft_close(t_server *server)
{
	ft_clean_socket(server);
}
