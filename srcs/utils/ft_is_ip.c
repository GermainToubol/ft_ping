/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_ip.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 20:38:16 by gtoubol           #+#    #+#             */
/*   Updated: 2023/03/17 20:38:16 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_is_ip.c
 * @brief test if the given string is a valid ip
 *
 */

#include "ft_utils.h"
#include "libft.h"
#include <stdio.h>

static int ft_rec_ip(const char *s);

/**
 * @fn int ft_is_ip(const char *ipstr)
 *
 * @param ipstr: tested string
 *
 * @return 1 if the string corresponds to an IP, 0 otherwise
 *
 * @brief test if the string has a valid IPV4 format
 *
 */
int	ft_is_ip(const char	*s)
{
	int numeric_field = 0;

	if (ft_strlen(s) > 15 || ft_strlen(s) == 0)
		return (0);

	numeric_field = ft_rec_ip(s);
	if (numeric_field >= 1 && numeric_field <= 4)
		return (1);
	return (0);
}

static int ft_rec_ip(const char *s)
{
	char buff[16];
	int n;
	size_t len;

	if (s[0] == '\0')
		return (0);
	n = ft_atoi(s);
	sprintf(buff, "%d", n);
	len = ft_strlen(buff);
	if (n > 255 || n < 0 || ft_strncmp(s, buff, len) != 0)
		return (0);
	if (s[len] == '\0')
		return (1);
	if (s[len] == '.')
	{
		n = ft_rec_ip(s + len + 1);
		if (n <= 0)
			return (-1);
		return (n + 1);
	}
	return (-1);
}
