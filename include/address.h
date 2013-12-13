/**
 * \file address.h
 * \brief Utilitaires pour obtenir des addresses. (header)
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

#ifndef __ADDRESS_H
#define __ADDRESS_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "base.h"

/**
 * \brief Obtenir une adresse IPv4.
 * \param hostname Nom d'hôte.
 * \param protocol Protocole.
 * \return Adresse IPv4.
 *
 * protocol = 0 pour faire une recherche sans se préocupper du protocole.
 */
u_int32_t get_ipv4(const char * hostname, int protocol);

/**
 * \brief Obtenir l'adresse IPv4 de la machine.
 * \param protocol Protocole.
 * \return Adresse IPv4.
 *
 * protocol = 0 pour faire une recherche sans se préocupper du protocole.
 */
u_int32_t get_source_ipv4(int protocol);

#endif /* __ADDRESS_H */
