/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 21:36:34 by gtoubol           #+#    #+#             */
/*   Updated: 2023/03/02 21:36:34 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "ft_ping.h"
#include "ft_utils.h"
#include "libft.h"

int	main(int argc, const char **argv)
{
	t_server	server;
	int32_t		errcode;

	ft_bzero(&server, sizeof(server));
	server.id = ft_swap_16bits((uint_least16_t)getpid());
	server.mark = -1;
	server.preload = 1;
	server.interval = 1;
	server.mtud = NO_MTUD;
	server.deadline = 0;
	server.timeout = 0;
	server.ttl = 64;
	errcode = ft_init(argc, argv, &server);
	if (errcode == 0)
		errcode = ft_loop(&server);
	ft_close(&server);
	return (errcode);
}
