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

#include "ft_ping.h"
#include "libft.h"

int	main(int argc, const char **argv)
{
	t_server	server;
	int32_t		errcode;

	ft_bzero(&server, sizeof(server));
	server.mark = -1;
	server.preload = 1;
	server.interval = 1;
	server.mtud = NO_MTUD;
	server.deadline = 0;
	errcode = ft_init(argc, argv, &server);
	if (errcode == 0)
		errcode = ft_loop(&server);
	ft_close(&server);
	return (errcode);
}
