/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getdelay.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:43:17 by gtoubol           #+#    #+#             */
/*   Updated: 2023/03/07 16:43:17 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/**
 * @file ft_getdelay.c
 * @brief time utility
 *
 */

#include <sys/types.h>

#include "ft_utils.h"

/**
 * @fn float ft_getdelay(const struct timeval *start, const struct timeval *end)
 *
 * @param start: timestamp of first event
 * @param end: timestamp of second event
 *
 * @return delay in ms between first and second event
 *
 * @brief Compute the delay in ms between two timestamps.
 */
float ft_getdelay(const struct timeval *start, const struct timeval *end)
{
	return ((float)(end->tv_sec - start->tv_sec) * 1000.f
			+ (float)(end->tv_usec - start->tv_usec) / 1000.f);
}
