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
 * \brief Changer la taille d'un paquet.
 * \param[in,out] packet Paquet.
 * \param[in] length Taille.
 * \retval 0 Pas d'erreur.
 * \retval n < 0 Erreur.
 * \relatesalso icmp4_packet
 */
int icmp4_packet_set_length(icmp4_packet * packet, u_int16_t length);

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

/**
 * \brief Afficher un paquet.
 * \param packet Paquet à afficher.
 *
 * Surtout pour du debug...
 */
void icmp4_packet_print(const icmp4_packet * packet);

/**
 * \brief Recevoir un paquet IPv4+ICMP.
 * \param sockfd Socket.
 * \param address Adresse ciblée.
 * \param wait_time Temps d'attente maximum.
 * \param packet Packet reçu.
 * \retval 0 Pas d'erreur.
 * \retval autre Erreur.
 */
int receive_icmp_v4(int sockfd, struct sockaddr_in * address, struct timeval * wait_time, icmp4_packet * packet);

/**
 * \brief Paquet IPv6+ICMP
 */
typedef struct icmp6_packet
{
    ip6_hdr ip_header;      /**<- Header IP. */
    icmp6_hdr icmp_header;  /**<- Header ICMP. */
} icmp6_packet;

typedef struct icmp6_checksum_packet
{
    fake_ip6_hdr ip_header;
    icmp6_hdr icmp_header;
} icmp6_checksum_packet;

/**
 * \brief Construire un paquet IPv6 + ICMP.
 * \param[in,out] packet Paquet.
 * \param[in] dest_address Addresse de destination du paquet.
 * \retval 0 Pas d'erreur.
 * \retval n < 0 Erreur...
 * \relatesalso icmp6_packet
 */
int icmp6_packet_init(icmp6_packet * packet, struct sockaddr_in6 * address);

/**
 * \brief Checksum d'un paquet IPv6+ICMP
 * \param[in,out] packet Paquet.
 * \retval 0 Pas d'erreur.
 * \retval -1 \p header pointe vers \c NULL.
 * \retval -2 La checksum ne s'est pas bien déroulée.
 * \relatesalso icmp6_packet
 */
int icmp6_packet_checksum(icmp6_packet * packet);

/**
 * \brief Changer la taille d'un paquet.
 * \param[in,out] packet Paquet.
 * \param[in] length Taille.
 * \retval 0 Pas d'erreur.
 * \retval n < 0 Erreur.
 * \relatesalso icmp6_packet
 */
int icmp6_packet_set_length(icmp6_packet * packet, u_int16_t length);

/**
 * \brief Changer le TTL d'un paquet IPv4 + ICMP.
 * \param[in,out] packet Paquet.
 * \param[in] ttl Nouveau TTL (1 <= TTL <= MAXTTL).
 * \retval 0 Pas d'erreur.
 * \retval < 0 Erreur.
 * \relatesalso icmp6_packet
 */
int icmp6_packet_set_ttl(icmp6_packet * packet, u_int8_t ttl);

/**
 * \brief Changer la sequence d'un paquet IPv4+ICMP ECHO_REQUEST.
 * \param[in,out] packet Paquet.
 * \param[in] ttl Nouvelle séquence.
 * \retval 0 Pas d'erreur.
 * \relatesalso icmp6_packet
 */
int icmp6_packet_set_echo_seq(icmp6_packet * packet, u_int16_t sequence);

/**
 * \brief Afficher un paquet.
 * \param packet Paquet à afficher.
 *
 * Surtout pour du debug...
 */
void icmp6_packet_print(const icmp6_packet * packet);

/**
 * \brief Recevoir un paquet IPv4+ICMP.
 * \param sockfd Socket.
 * \param address Adresse ciblée.
 * \param wait_time Temps d'attente maximum.
 * \param packet Packet reçu.
 * \retval 0 Pas d'erreur.
 * \retval autre Erreur.
 */
int receive_icmp_v6(int sockfd, struct sockaddr_in6 * address, struct timeval * wait_time, icmp6_packet * packet);

void icmp6_checksum_packet_print(icmp6_checksum_packet * packet);

#endif /* __PACKET_H */
