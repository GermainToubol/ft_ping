/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_packet.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 12:49:13 by gtoubol           #+#    #+#             */
/*   Updated: 2023/03/06 12:49:13 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_packet.h
 * @brief all packet utilities
 *
 */

#ifndef FT_PACKET_H
#define FT_PACKET_H

#include <stdint.h>

#include "ft_ping.h"

#define ICMP_ECHO_DATA_LENGTH 56
#define ICMP_ECHO_PACKET_LENGTH 64

/* ************************************************************************* */
/*                                 Data types                                */
/* ************************************************************************* */

/**
 * @struct t_echo
 * @brief 2nd 32-bit field of an echo request/response
 */
typedef struct {
	uint_least16_t	id;			/*!< Identifier */
	uint_least16_t	seq;		/*!< Sequence number */
} t_echo;

/**
 * @struct t_problem
 * @brief 2nd 32-bit field of a problem response
 */
typedef struct {
	uint_least8_t	ptr;		/*!< Pointer fied */
	uint32_t		unused: 24;	/*!< Padding */
} t_problem;

/**
 * @struct t_gateway
 * @brief 2nd 32-bit field of a redirect response
 */
typedef struct {
	uint_least32_t	address;	/*!< Gateway Internet address */
} t_gateway;

/**
 * @struct t_timestamp
 * @brief 2nd 32-bit field of a timestamp message
 */
typedef struct {
	uint_least16_t	id;			/*!< Identifier */
	uint_least16_t	seq;		/*!< Sequence number */
} t_timestamp;

/**
 * @struct t_icmp_packet
 * @brief description of an icmp packet
 */
typedef struct {
	uint_least8_t		type;			/*!< ICMP type  */
	uint_least8_t		code;			/*!< ICMP code  */
	uint_least16_t		checksum;		/*!< ICMP checksum */
	union {
		uint_least32_t	unreachable;	/*!< unused in case of uncreachable */
		uint_least32_t	time_exceeded;	/*!< unused in case of time exceeded message  */
		t_problem		problem;		/*!< prointer field if problem message  */
		uint_least32_t	quench;			/*!< unused in quench message */
		t_gateway		gateway;		/*!< gateway address */
		t_echo			echo;			/*!< echo informations */
		t_timestamp		timestamp;		/*!< timestamp informations */
	};
	uint_least8_t		data[];			/*!< data field in the packet */
} t_icmp_packet;

/* ************************************************************************* */
/*                                 Functions                                 */
/* ************************************************************************* */

void ft_init_packet(t_icmp_packet *packet, const t_server *server);
void ft_mark_packet(t_icmp_packet *packet, uint_least16_t packet_number);
void ft_send_packet(const t_icmp_packet *packet, const t_server *server);
void ft_receive_packet(const t_server *server);

#endif /* FT_PACKET_H */
