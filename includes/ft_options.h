/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_options.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 11:08:42 by gtoubol           #+#    #+#             */
/*   Updated: 2023/03/10 11:08:42 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_options.h
 * @brief option parsing
 *
 */

#ifndef FT_OPTIONS_H
#define FT_OPTIONS_H

#include <stdint.h>

#include "ft_ping.h"

/**
 * @typedef t_apply_opt
 * @brief parse a specific option
 *
 */
typedef int (*t_apply_opt)(const char *arg, t_server *server);

/**
 * @struct t_options
 * @brief options list descriptor
 *
 */
typedef struct {
	const char	*shortname;		/*!< Shortname of the option */
	const char	*longname;		/*!< Fullname of the option */
	const char	*parameter;		/*!< Parameter name of the option */
	const char	*description;	/*!< Description of the option */
	t_apply_opt	fnc;			/*!< Option specific parser */
} t_options;

void	ft_usage(void);

int32_t ft_parseopts(int argc, const char **argv, t_server *server);
int ft_optusage(const char *arg, t_server *server);
int ft_optflood(const char *arg, t_server *server);
int ft_optcount(const char *arg, t_server *server);
int ft_optmark(const char *arg, t_server *server);
int ft_optpreload(const char *arg, t_server *server);

#endif /* FT_OPTIONS_H */
