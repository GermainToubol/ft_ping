/**
 * @file ft_optcount.c
 * @brief set the packet count
 *
 */

#include <stdint.h>
#include <stdio.h>

#include "ft_options.h"
#include "ft_ping.h"
#include "libft.h"

/**
 * @fn int ft_optcount(const char *arg, t_server *server)
 *
 */
int ft_optcount(const char *arg, t_server *server)
{
	int	errcode;
	int64_t res;

	res = ft_atoll(arg, &errcode);
	if (errcode == 1) {
		dprintf(2, "%s: invalid argument: '%s'\n",
				"ft_ping", arg);
		return (-1);
	}
	if (errcode == 2) {
		dprintf(2, "%s: invalid argument: '%s': Numerical result out of range\n",
				"ft_ping", arg);
		return (-1);
	}
	if (res <= 0)
	{
		dprintf(2, "%s: invalid argument: '%s': out of range: 1 <= value <= 9223372036854775807\n",
				"ft_ping", arg);
		return (-1);
	}
	server->count = res;
	return (0);

}
