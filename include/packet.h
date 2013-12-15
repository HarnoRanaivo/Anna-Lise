/**
 * \file packet.h
 * \brief Utilitaires pour créer des paquets (header)
 * \author MEYER Jérémy
 * \author RAZANAJATO Harenome
 * \date 2013
 * \copyright WTFPL version 2
 *
 */
/* This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://www.wtfpl.net/ for more details.
 */

#ifndef __PACKET_H
#define __PACKET_H

#include <netinet/ip_icmp.h>
#include <netinet/icmp6.h>
#include <netinet/ip.h>
#include <netinet/ip6.h>
#include <sys/types.h>
#include <errno.h>

#include "base.h"
#include "icmp_util.h"
#include "ip_util.h"
#include "address.h"

/**
 * \brief Paquet Ipv4 ICMP.
 */
typedef struct icmp4_packet
{
    iphdr ip_header;        /**<- Header IP. */
    icmphdr icmp_header;    /**<- Header ICMP. */
} icmp4_packet;

/**
 * \brief Construire un paquet IPv4 + ICMP.
 * \param[in,out] packet Paquet.
 * \param[in] dest_address Addresse de destination du paquet.
 * \retval 0 Pas d'erreur.
 * \retval n < 0 Erreur...
 * \relatesalso icmp4_packet
 */
int icmp4_packet_init(icmp4_packet * packet, u_int32_t dest_address);

/**
 * \brief Changer le TTL d'un paquet IPv4 + ICMP.
 * \param[in,out] packet Paquet.
 * \param[in] ttl Nouveau TTL (1 <= TTL <= MAXTTL).
 * \retval 0 Pas d'erreur.
 * \retval < 0 Erreur.
 * \relatesalso icmp4_packet
 */
int icmp4_packet_set_ttl(icmp4_packet * packet, u_int8_t ttl);

/**
 * \brief Changer la sequence d'un paquet IPv4+ICMP ECHO_REQUEST.
 * \param[in,out] packet Paquet.
 * \param[in] ttl Nouvelle séquence.
 * \retval 0 Pas d'erreur.
 * \relatesalso icmp4_packet
 */
int icmp4_packet_set_echo_seq(icmp4_packet * packet, u_int16_t sequence);

#endif /* __PACKET_H */
