/**
 * \file traceroute.h
 * \brief Traceroute (header)
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

#ifndef __TRACEROUTE_H
#define __TRACEROUTE_H

#include <sys/time.h>

#include "base.h"
#include "address.h"
#include "packet.h"
#include "time_util.h"

/**
 * \brief Recevoir un paquet IPv4+ICMP (traceroute).
 * \param[in] sockfd Socket.
 * \param[in] address Adresse ciblée.
 * \param[in,out] source Adresse du paquet courant.
 * \return Type ICMP du paquet reçu.
 */
int traceroute_receive_icmp_v4(int sockfd, struct sockaddr_in * address, struct sockaddr_in * source, const struct timeval * wait_time);

/**
 * \brief Traceroute IPv4+ICMP.
 * \param hostname Nom de l'hôte ciblé.
 * \param hops_max Nombre de sauts maximum.
 * \param attempts_number Nombre de tentatives par saut.
 * \retval 0 Pas d'erreur.
 * \retval autre Erreur.
 */
int traceroute_icmp_v4(const char * hostname, int hops_max, int attempts_number, int packet_size, const struct timeval * wait_time);

int traceroute_receive_icmp_v6(int sockfd, struct sockaddr_in6 * address, struct sockaddr_in6 * source, const struct timeval * wait_time);

int traceroute_icmp_v6(const char * hostname, int hops_max, int attempts_number);

int traceroute_udp_v4(const char * hostname, int hops_max, int attempts_number);

#endif /* __TRACEROUTE_H */
