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
 * \brief Obtenir le nom d'un hôte à partir de son adresse IPv4.
 * \param[in,out] buffer Tampon pour le nom de l'hôte.
 * \param[in] buffer_size Taille du tampon.
 * \param[in] address Adresse de l'hôte.
 * \retval 0 Pas d'erreur.
 * \retval n < 0 Erreur.
 */
int reverse_dns_v4(char * buffer, size_t buffer_size, struct in_addr address);

/**
 * \brief Recevoir un paquet IPv4+ICMP.
 * \param sockfd Socket.
 * \param ttl TTL courant.
 */
int receive_icmp_v4(int sockfd, struct sockaddr_in * address, icmp4_packet * packet);

int traceroute_receive_icmp_v4(int sockfd, struct sockaddr_in * address, struct sockaddr_in * source, struct timeval * time);

int traceroute_icmp_v4(const char * hostname);

#endif /* __TRACEROUTE_H */
