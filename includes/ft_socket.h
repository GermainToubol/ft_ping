/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_socket.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 11:57:35 by gtoubol           #+#    #+#             */
/*   Updated: 2023/03/06 11:57:35 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_socket.h
 * @brief utilities arround sockets
 *
 */

#ifndef FT_SOCKET_H
#define FT_SOCKET_H

#include <stdint.h>

#include "ft_ping.h"

int32_t ft_init_socket(t_server *server);
int32_t ft_resolve_socket(t_server *server);
void ft_clean_socket(t_server *server);
int32_t ft_options_socket(const t_server *server);

#endif /* FT_SOCKET_H */
