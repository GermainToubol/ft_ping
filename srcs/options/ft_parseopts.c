/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parseopts.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 11:08:49 by gtoubol           #+#    #+#             */
/*   Updated: 2023/03/10 11:08:49 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_parseopts.c
 * @brief
 */

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include "ft_ping.h"
#include "ft_options.h"
#include "libft.h"

static const t_options g_opts[] = {
	{"c", NULL, "<count>", "send COUNT echo requests", ft_optcount},
	{"f", NULL, NULL, "flood ping", ft_optflood},
	{"h", NULL, NULL, "print help and exit", ft_optusage},
	{"i", NULL, "<interval>", "interval between packets (s)", ft_optinterval},
	{"l", NULL, "<preload>", "number of preloaded packets", ft_optpreload},
	{"m", NULL, "<mark>", "mark the outgoing packets", ft_optmark},
	{"M", NULL, "<pmtud opt>", "define mtu discovery, can be one of <do|dont|want>", ft_optmtud},
	{"p", NULL, "<pattern>", "set the padding bytes pattern", ft_optpattern},
	{"t", NULL, "<ttl>", "set request ttl", ft_optttl},
	{"v", NULL, NULL, "verbose output", ft_optverbose},
	{"w", NULL, "<deadline>", "end the program after <deadline> seconds", ft_optdeadline},
	{"W", NULL, "<timeout>", "Stop if no response have been received in <timeout> seconds", ft_opttimeout}
    };

static int ft_parse_long(int i, const char **argv, t_server *server);
static int ft_parse_short(int i, const char **argv, t_server *server);

/**
 * @fn int32_t ft_parseopts(int argc, const char **argv, t_server *server)
 *
 * @param argc: number of command line arguments
 * @param argv: list of command line arguments
 * @param server: current ping server
 *
 * @return -1 on failure, 0 otherwise
 *
 * @brief pass the arguments from the command line to the server.
 *
 * Functions will be applyed form left to right
 */
int32_t ft_parseopts(int argc, const char **argv, t_server *server)
{
	int ret;

	for (int i = 1; i < argc; i++)
	{
		if (argv[i][0] == '-' && argv[i][1] == '-' && argv[i][2] != '\0')
		{
			ret = ft_parse_long(i, argv, server);
			if(ret < 0)
				return (-1);
			i += ret;
		}
		else if (argv[i][0] == '-' && argv[i][1] != '\0')
		{
			ret = ft_parse_short(i, argv, server);
			if (ret < 0)
				return (-1);
			i += ret;
		}
		else
			server->name = argv[i];
	}
	if (server->name == NULL)
	{
		dprintf(2, "ft_ping: usage error: Destination address required\n");
		return (-1);
	}
	return (0);
}

/**
 * @fn void ft_usage(void)
 *
 * @brief show the help
 *
 */
void	ft_usage(void)
{
	dprintf(2, "\n");
	dprintf(2, "Usage\n");
	dprintf(2, "  ping [options] <destination>\n\n");
	dprintf(2, "Options:\n");
	dprintf(2, "  %-19s%s\n", "<destination>", "dns name or ip adress");
	for (size_t i = 0; i < sizeof(g_opts) / sizeof(g_opts[0]); i++)
	{
		if (g_opts[i].parameter == NULL)
			dprintf(2, "  -%-18s%s\n", g_opts[i].shortname, g_opts[i].description);
		else
			dprintf(2, "  -%s %-16s%s\n", g_opts[i].shortname,
					g_opts[i].parameter, g_opts[i].description);
	}
	dprintf(2, "\n");
}

/**
 * @fn int ft_parse_long(int i, const char **argv, t_server *server)
 *
 * @param i: argument position
 * @param argv: arguments list
 * @param server: current ping server
 *
 * @return -1 on failure, 1 if the function consumes 1 argument, 0 otherwise
 *
 */
static int ft_parse_long(int i, const char **argv, t_server *server)
{
	for (size_t j = 0; j < sizeof(g_opts) / sizeof(g_opts[0]); j++)
	{
		if (g_opts[j].longname != NULL
			&& ft_strcmp(g_opts[j].longname , argv[i] + 2) == 0)
			return (g_opts[j].fnc(argv[i + 1], server));
	}
	dprintf(2, "ft_ping: invalid option -- '%s'\n", argv[i] + 2);
	ft_usage();
	return (-1);
}

/**
 * @fn int ft_parse_short(int i, const char **argv, t_server *server)
 *
 * @param i: argument position
 * @param argv: arguments list
 * @param server: current ping server
 *
 * @return -1 on failure, 1 if the function consumes 1 argument, 0 otherwise
 *
 */
static int ft_parse_short(int i, const char **argv, t_server *server)
{
	int ret;
	int has_opt;

	for (size_t j = 1; j < ft_strlen(argv[i]); j++)
	{
		ret = -1;
		for(size_t k = 0; k < sizeof(g_opts) / sizeof(g_opts[0]); k++)
		{
			if (g_opts[k].shortname
				&& ft_strncmp(g_opts[k].shortname, argv[i] + j, 1) == 0)
			{
				has_opt = (g_opts[k].parameter != NULL);
				if (argv[i][j + 1] == '\0')
					ret = g_opts[k].fnc(argv[i + 1], server);
				else
					ret = g_opts[k].fnc(argv[i] + j + 1, server);
				goto nextloop;
			}
		}
		dprintf(2, "ft_ping: invalid option -- '%c'\n", argv[i][j]);
		ft_usage();
		return (-1);

	nextloop:
		if (ret < 0)
			return (-1);
		if (has_opt)
			return (argv[i][j + 1] == '\0'? 1: 0);
	}
	return (0);
}
