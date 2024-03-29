/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 17:44:52 by gtoubol           #+#    #+#             */
/*   Updated: 2023/03/06 17:44:52 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_utils.h
 * @brief small utilitaries
 *
 */

#ifndef FT_UTILS_H
#define FT_UTILS_H

#include <stddef.h>
#include <stdint.h>
#include <sys/types.h>

uint_least16_t ft_swap_16bits(uint_least16_t n);
uint_least16_t ft_checksum(const void *data, size_t size);
float ft_getdelay(const struct timeval *start, const struct timeval *end);
int ft_is_ip(const char *ipstr);

#endif /* FT_UTILS_H */
