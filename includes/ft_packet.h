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

/* ICMP packet ************************************************************* */

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

/* IP packet *****************************************************************/

/**
 * @def MAX_IPPACKET_LENGTH
 * @brief max length of a single IP packet
 *
 * Since the packet length holds on an uint16, it max length is 0xffff bytes
 */
#define MAX_IPPACKET_LENGTH 0xffff

/**
 * @enum e_ip_errors
 * @brief IP Packet errors
 *
 */
enum e_ip_errors
{
	IP_ERROR_SUCCESS = 0,
	IP_ERROR_BADSIZE,
	IP_ERROR_INVALID_HEADER_SIZE,
	IP_ERROR_BAD_VERSION,
	IP_ERROR_INVALID_CHECKSUM,
	IP_ERROR_INCOMPLETE_PACKET
};

/**
 * @struct t_ip_packet
 * @brief description of an IP packet
 */
typedef struct {
	uint8_t			IHL: 4;				/*!< IP Header Length  */
	uint8_t			version: 4;			/*!< Version number */
	uint_least8_t	unused;				/*!< Unused part in the project */
	uint_least16_t	length;				/*!< Total length */
	uint_least16_t	id;					/*!< Packet identifier */
	uint_least16_t	unused2;			/*!< Unused part in the project */
	uint_least8_t	ttl;				/*!< Time to live */
	uint_least8_t	protocol;			/*!< Protocol number */
	uint_least16_t	checksum;			/*!< Header checksum */
	uint_least32_t	source;				/*!< Source IP */
	uint_least32_t	dest;				/*!< Destination IP */
} t_ip_packet;

/* ************************************************************************* */
/*                                 Functions                                 */
/* ************************************************************************* */

void ft_init_packet(t_icmp_packet *packet, const t_server *server);
void ft_mark_packet(t_icmp_packet *packet, uint_least16_t packet_number);
void ft_send_packet(const t_icmp_packet *packet, const t_server *server);
void ft_receive_packet(const t_server *server);
int ft_isvalid_ip_packet(const t_ip_packet *packet, size_t size);
void ft_analyse_packet(const t_server *server, const void *buffer, size_t size);

/* Packet handlers ********************************************************* */

#define ICMP_ECHO_REQUEST 8
#define ICMP_ECHO_REPLY 0

typedef void (*t_packet_handler)(
	const t_server *,
	const t_ip_packet *,
	const t_icmp_packet *,
	size_t);

void ft_handel_request(
	const t_server *server,
	const t_ip_packet *ip_packet,
	const t_icmp_packet *packet,
	size_t size);
void ft_handel_unreachable(
	const t_server *server,
	const t_ip_packet *ip_packet,
	const t_icmp_packet *packet,
	size_t size);
void ft_handel_response(
	const t_server *server,
	const t_ip_packet *ip_packet,
	const t_icmp_packet *packet,
	size_t size);
void ft_handle_time(
	const t_server *server,
	const t_ip_packet *ip_packet,
	const t_icmp_packet *packet,
	size_t size);
void ft_handle_problem(
	const t_server *server,
	const t_ip_packet *ip_packet,
	const t_icmp_packet *packet,
	size_t size);
void ft_handle_quench(
	const t_server *server,
	const t_ip_packet *ip_packet,
	const t_icmp_packet *packet,
	size_t size);
void ft_handle_redirect(
	const t_server *server,
	const t_ip_packet *ip_packet,
	const t_icmp_packet *packet,
	size_t size);
void ft_dump_packet(const t_ip_packet *ippacket, size_t size);

#endif /* FT_PACKET_H */
