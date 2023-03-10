/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_statistics.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 09:15:33 by gtoubol           #+#    #+#             */
/*   Updated: 2023/03/10 09:15:33 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_statistics.c
 * @brief gather the counters and statistical properties
 *
 */

#include <stdint.h>
#include <stdio.h>
#include <math.h>

#include "ft_statistics.h"

static t_stats g_stats = {
    .n_send = 0,
    .n_received = 0,
    .n_errors = 0,
	.min = -1.0f,
	.max = -1.0f,
    .avg = 0.f,
    .avg2 = 0.f
    };

/**
 * @fn void ft_add_send(void)
 *
 * @brief Count one packet send
 *
 */
void	ft_add_send(void)
{
	g_stats.n_send += 1;
}

/**
 * @fn void ft_add_received_valid(float delay)
 *
 * @param delay: packet delay
 *
 * @brief Count one valid packet received
 *
 */
void	ft_add_received_valid(float delay)
{
	g_stats.n_received++;
	g_stats.avg += delay;
	g_stats.avg2 += delay * delay;
	if (g_stats.min < 0.f)
		g_stats.min = delay;
	if (g_stats.min > delay)
		g_stats.min = delay;
	if (g_stats.max < delay)
		g_stats.max = delay;
}

/**
 * @fn void ft_received_error(void)
 *
 * @brief Count one error packet received
 *
 */
void	ft_add_received_error(void)
{
	g_stats.n_errors += 1;
}

/**
 * @fn void ft_print_intermediate_stats(void)
 *
 * @brief Print the statistics at an intermediate state
 *
 */
void	ft_print_intermediate_stats(void)
{
	float	avg;
	float	mdev;
	float	prop;
	float	div;

	if (g_stats.n_received == 0)
	{
		dprintf(1, "0/%u packets, 100%% loss\n", g_stats.n_send);
		return;
	}
	div = 1.f / (float)g_stats.n_send;
	avg = g_stats.avg / g_stats.n_received;
	mdev = sqrtf((g_stats.avg2 - g_stats.avg * g_stats.avg * div) * div);
	prop = (float)(g_stats.n_send - g_stats.n_received) * div * 100.f;
	dprintf(1, "%u/%u packets, %.0f%% loss, min/avg/max/mdev %.3f/%.3f/%.3f/%.3f ms\n",
			g_stats.n_received, g_stats.n_send, prop, g_stats.min, avg,
			g_stats.max, mdev);
}

/**
 * @fn void ft_print_final_stats(void)
 *
 * @brief Print summary
 *
 */
void	ft_print_final_stats(void)
{
	float	avg;
	float	mdev;
	float	prop;
	float	div;

	if (g_stats.n_received == 0 && g_stats.n_errors == 0)
	{
		dprintf(1, "%u packets transmitted, 0 received, 100%% packet loss\n",
				g_stats.n_send);
		return;
	}
	if (g_stats.n_received == 0)
	{
		dprintf(1, "%u packets transmitted, 0 received, +%u errors, 100%% \
packet loss\n", g_stats.n_send, g_stats.n_errors);
		return;
	}
	div = 1.f / (float)g_stats.n_send;
	avg = g_stats.avg / g_stats.n_received;
	mdev = sqrtf((g_stats.avg2 - g_stats.avg * g_stats.avg * div) * div);
	prop = (float)(g_stats.n_send - g_stats.n_received) * div * 100.f;
	if (g_stats.n_errors == 0)
	{
                dprintf(1, "%u packets transmitted, %u received, %.0f%% loss, \
min/avg/max/mdev %.3f/%.3f/%.3f/%.3f ms\n",
				g_stats.n_send, g_stats.n_received, prop, g_stats.min, avg,
				g_stats.max, mdev);
		return ;
	}
        dprintf(1,
                "%u packets transmitted, %u received, %+d errors, %.0f%% loss, \
min/avg/max/mdev %.3f/%.3f/%.3f/%.3f ms\n",
			g_stats.n_send, g_stats.n_received, g_stats.n_errors, prop,
			g_stats.min, avg, g_stats.max, mdev);
}
