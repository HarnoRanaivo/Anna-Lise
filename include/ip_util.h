/**
 * \file ip_util.h
 * \brief Utilitaires IP (header)
 * \author MEYER Jérémy
 * \author RAZANAJATO Harenome
 * \date 2013
 * \copyright WTFPL version 2
 */
/* This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://www.wtfpl.net/ for more details.
 */

#ifndef __IP_UTIL_H
#define __IP_UTIL_H

#include <netinet/ip.h>
#include <netinet/ip6.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>

#include "base.h"
#include "checksum.h"
#include "address.h"

/**
 * \brief Header IPv4.
 */
typedef struct iphdr iphdr;

/**
 * \brief Modifier la version du header.
 * \param[in,out] header Header IP.
 * \retval 0 Pas d'erreur.
 * \retval -1 \p header pointe vers \c NULL.
 * \relatesalso iphdr
 *
 * En cas d'erreur, \c errno sera rempli à \c EINVAL.
 */
int iphdr_set_version(iphdr * header);

/**
 * \brief Modifier la longueur du header.
 * \param[in,out] header Header IP.
 * \param[in] length Longueur
 * \retval 0 Pas d'erreur.
 * \retval -1 \p header pointe vers \c NULL.
 * \retval -2 \p header n'est pas un header pour IPv4
 * \retval -3 \p length est trop petit (< 5) ou trop grand (> 15).
 * \relatesalso iphdr
 *
 * En cas d'erreur -1 ou 2, \c errno sera rempli à \c EINVAL.
 * En cas d'erreur -3, \c errno sera rempli à \c EDOM.
 */
int iphdr_set_header_length(iphdr * header, unsigned int length);

/**
 * \brief Modifier le type de service.
 * \param[in,out] header Header IP.
 * \param[in] service Type de service.
 * \retval 0 Pas d'erreur.
 * \retval -1 \p header pointe vers \c NULL.
 * \retval -2 \p header n'est pas un header pour IPv4
 * \relatesalso iphdr
 *
 * En cas d'erreur -1 ou 2, \c errno sera rempli à \c EINVAL.
 */
int iphdr_set_type_of_service(iphdr * header, u_int8_t service);

/**
 * \brief Modifier la longueur totale.
 * \param[in,out] header Header IP.
 * \param[in] length Longueur
 * \retval 0 Pas d'erreur.
 * \retval -1 \p header pointe vers \c NULL.
 * \retval -2 \p header n'est pas un header pour IPv4
 * \retval -3 \p length est trop petit (< 20) ou trop grand (> IP_MACPACKET).
 * \relatesalso iphdr
 *
 * En cas d'erreur -1 ou 2, \c errno sera rempli à \c EINVAL.
 * En cas d'erreur -3, \c errno sera rempli à \c EDOM.
 */
int iphdr_set_total_length(iphdr * header, u_int16_t length);

/**
 * \brief Modifier l'ID.
 * \param[in,out] header Header IP.
 * \param[in] id ID.
 * \retval 0 Pas d'erreur.
 * \retval -1 \p header pointe vers \c NULL.
 * \retval -2 \p header n'est pas un header pour IPv4
 * \relatesalso iphdr
 *
 * En cas d'erreur -1 ou 2, \c errno sera rempli à \c EINVAL.
 */
int iphdr_set_id(iphdr * header, u_int16_t id);

/**
 * \brief Modifier les flags.
 * \param[in,out] header Header IP.
 * \param[in] flags Flags.
 * \retval 0 Pas d'erreur.
 * \retval -1 \p header pointe vers \c NULL.
 * \retval -2 \p header n'est pas un header pour IPv4
 * \relatesalso iphdr
 *
 * En cas d'erreur -1 ou 2, \c errno sera rempli à \c EINVAL.
 */
int iphdr_set_flags(iphdr * header, unsigned int flags);

/**
 * \brief Modifier le fragment offset.
 * \param[in,out] header Header IP.
 * \param[in] offset Fragment offset.
 * \retval 0 Pas d'erreur.
 * \retval -1 \p header pointe vers \c NULL.
 * \retval -2 \p header n'est pas un header pour IPv4
 * \relatesalso iphdr
 *
 * En cas d'erreur -1 ou 2, \c errno sera rempli à \c EINVAL.
 */
int iphdr_set_fragment_offset(iphdr * header, unsigned int offset);

/**
 * \brief Modifier le TTL.
 * \param[in,out] header Header IP.
 * \param[in] ttl Time To Live.
 * \retval 0 Pas d'erreur.
 * \retval -1 \p header pointe vers \c NULL.
 * \retval -2 \p header n'est pas un header pour IPv4
 * \retval -3 \p ttl est trop petit (< 1) ou trop grand (> MAXTTL).
 * \relatesalso iphdr
 *
 * En cas d'erreur -1 ou 2, \c errno sera rempli à \c EINVAL.
 * En cas d'erreur -3, \c errno sera rempli à \c EDOM.
 */
int iphdr_set_ttl(iphdr * header, u_int8_t ttl);

/**
 * \brief Modifier le protocole.
 * \param[in,out] header Header IP.
 * \param[in] protocol Protocole.
 * \retval 0 Pas d'erreur.
 * \retval -1 \p header pointe vers \c NULL.
 * \retval -2 \p header n'est pas un header pour IPv4
 * \relatesalso iphdr
 *
 * En cas d'erreur -1 ou 2, \c errno sera rempli à \c EINVAL.
 */
int iphdr_set_protocol(iphdr * header, u_int8_t protocol);

/**
 * \brief Checksum.
 * \param[in,out] header Header IP.
 * \retval 0 Pas d'erreur.
 * \retval -1 \p header pointe vers \c NULL.
 * \retval -2 \p header n'est pas un header pour IPv4
 * \retval -3 La checksum ne s'est pas bien déroulée.
 * \relatesalso iphdr
 *
 * En cas d'erreur -1 ou 2, \c errno sera rempli à \c EINVAL.
 * Si la checksum ne s'est pas bien déroulée, \c errno contiendra \c ECANCELED.
 */
int iphdr_checksum(iphdr * header);

/**
 * \brief Modifier l'addresse source.
 * \param[in,out] header Header IP.
 * \param[in] address Adresse de la source.
 * \retval 0 Pas d'erreur.
 * \retval -1 \p header pointe vers \c NULL.
 * \retval -2 \p header n'est pas un header pour IPv4
 * \relatesalso iphdr
 *
 * En cas d'erreur -1 ou 2, \c errno sera rempli à \c EINVAL.
 */
int iphdr_set_source_address(iphdr * header, u_int32_t address);

/**
 * \brief Modifier l'addresse de destination.
 * \param[in,out] header Header IP.
 * \param[in] address Adresse de destination.
 * \retval 0 Pas d'erreur.
 * \retval -1 \p header pointe vers \c NULL.
 * \retval -2 \p header n'est pas un header pour IPv4
 * \relatesalso iphdr
 *
 * En cas d'erreur -1 ou 2, \c errno sera rempli à \c EINVAL.
 */
int iphdr_set_dest_address(iphdr * header, u_int32_t address);

/**
 * \brief Afficher le contenu d'un header.
 * \param header Header à afficher.
 */
void iphdr_print(const iphdr * header);


/**
 * \brief Header IPv6.
 */
typedef struct ip6_hdr ip6_hdr;

typedef struct ip6_hdr_first_part
{
    unsigned int version:4;
    unsigned int traffic_class:8;
    unsigned int flow_label:20;
} ip6_hdr_first_part;

int ip6_hdr_set_version(ip6_hdr * header);

int ip6_hdr_set_traffic_class(ip6_hdr * header, u_int8_t traffic_class);

int ip6_hdr_set_flow_label(ip6_hdr * header, unsigned int label);

int ip6_hdr_set_payload_length(ip6_hdr * header, uint16_t length);

int ip6_hdr_set_next_header(ip6_hdr * header, uint8_t next_header);

int ip6_hdr_set_hop_limit(ip6_hdr * header, uint8_t limit);

int ip6_hdr_set_source(ip6_hdr * header, sockaddr_in6 * address);

int ip6_hdr_set_destination(ip6_hdr * header, sockaddr_in6 * address);

typedef struct fake_ip6_hdr
{
    struct in6_addr source;
    struct in6_addr destination;
    uint32_t length;
    uint8_t zeros[3];
    uint8_t next_header;
} fake_ip6_hdr;

int fake_ip6_hdr_set_source(fake_ip6_hdr * header, sockaddr_in6 * address);

int fake_ip6_hdr_set_destination(fake_ip6_hdr * header, sockaddr_in6 * address);

int fake_ip6_hdr_set_length(fake_ip6_hdr * header, uint32_t length);

int fake_ip6_hdr_set_zeros(fake_ip6_hdr * header);

int fake_ip6_hdr_set_next_header(fake_ip6_hdr * header, uint8_t next_header);

#endif /* __IP_UTIL_H */
