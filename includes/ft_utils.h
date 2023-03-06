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

uint_least16_t ft_swap_16bits(uint_least16_t n);
uint_least16_t ft_checksum(void *data, size_t size);

#endif /* FT_UTILS_H */
