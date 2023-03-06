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

int	main(int argc, const char **argv)
{
	t_server	server;
	int32_t		errcode;

	if (argc < 2) {
		dprintf(2, "HANDLE %s (l. %d)\n", __FILE__, __LINE__);
		abort();
	}
	errcode = ft_init(argc, argv, &server);
	if (errcode == 0)
	{
		// run loop
	}
	return (0);
}
