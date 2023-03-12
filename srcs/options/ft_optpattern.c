/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_optpattern.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 21:11:19 by gtoubol           #+#    #+#             */
/*   Updated: 2023/03/11 21:11:19 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_optpattern.c
 * @brief padding content
 *
 */

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include "ft_options.h"
#include "ft_ping.h"
#include "libft.h"

/**
 * @fn int ft_optpattern(const char *arg, t_server *server)
 * @brief set the padding pattern
 *
 */
int	ft_optpattern(const char *s, t_server *server)
{
	uint8_t buffer[16] = {0};
	char	str[64];

	for (size_t i = 0; i != ft_strlen(s); i++)
	{
		if (ft_isdigit(s[i]) || (((uint8_t)s[i] | 32) - 'a') < 'g' - 'a')
		{
			if (i < 32)
			{
				uint8_t v = ft_isdigit(s[i])
					? s[i] - '0'
					: ((uint8_t)s[i] | 32) - 'a' + 10;
				v = v | buffer[i >> 1] << 4;
				buffer[i >> 1] = v;
			}
			continue;
		}
		dprintf(2, "%s: patterns must be specified as hex digits: %s\n",
				"ft_ping", s + i);
		return (-1);
	}
	server->pattern_length = 0;
	sprintf(str, "PATTERN: 0x");
	for (size_t i = 0; i < ft_strlen(s) && i < 32; i += 2) {
		sprintf(str + ft_strlen(str), "%02hx", buffer[i >> 1]);
		server->pattern_length++;
	}
	printf("%s\n", str);
	ft_memmove(server->pattern, buffer, server->pattern_length);
	return (0);
}
