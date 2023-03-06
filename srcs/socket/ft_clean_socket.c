/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_socket.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 12:07:26 by gtoubol           #+#    #+#             */
/*   Updated: 2023/03/06 12:07:26 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_clean_socket.c
 * @brief Socket level cleanup
 *
 */

#include <unistd.h>

#include "ft_ping.h"
#include "ft_socket.h"

/**
 * @fn void ft_clean_socket(t_server *server)
 *
 * @param server: current ping server
 *
 * @brief cleanup the ping socket
 */
void	ft_clean_socket(t_server *server)
{
	close(server->sockfd);
}
