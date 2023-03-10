/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_statistics.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 09:16:48 by gtoubol           #+#    #+#             */
/*   Updated: 2023/03/10 09:16:48 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_statistics.h
 * @brief toolbox around packet statistics
 *
 */

#ifndef FT_STATISTICS_H
#define FT_STATISTICS_H

#include <stdint.h>

/**
 * @struct t_stats
 * @brief gather the statistical properties
 *
 */
typedef struct {
	uint32_t	n_send;			/*!< Number of sended packets */
	uint32_t	n_received;		/*!< Number of received packets */
	uint32_t	n_errors;		/*!< Error counter */
	float		min;			/*!< Minimal response time */
	float		max;			/*!< Maximal response time */
	float		avg;			/*!< Cummulative sum of response times */
	float 		avg2;			/*!< Cummulative sum of squared response time */
} t_stats;

void ft_add_send(void);
void ft_add_received_valid(float delay);
void ft_add_received_error(void);
void ft_print_intermediate_stats(void);
void ft_print_final_stats(void);

#endif /* FT_STATISTICS_H */
