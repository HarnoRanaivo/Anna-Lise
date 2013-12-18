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
 * \brief Obtenir une adresse IP.
 * \param[in] hostname Nom d'hôte.
 * \param[in] family Type d'adresse.
 * \param[in] socktype Type de socket.
 * \param[in] protocol Protocole.
 * \param[in,out] address sockaddr
 * \retval 0 Pas d'erreur.
 * \retval -1 Erreur.
 */
int get_ip(const char * hostname, int family, int socktype, int protocol, struct sockaddr * address);

/**
 * \brief Obtenir une adresse IPv4.
 * \param hostname Nom d'hôte.
 * \param protocol Protocole.
 * \return Adresse IPv4.
 *
 * protocol = 0 pour faire une recherche sans se préocupper du protocole.
 */
int get_ipv4(const char * hostname, int protocol, struct sockaddr_in * address);

/**
 * \brief Obtenir l'adresse IPv4 de la machine.
 * \param protocol Protocole.
 * \return Adresse IPv4.
 *
 * protocol = 0 pour faire une recherche sans se préocupper du protocole.
 */
int get_source_ipv4(int protocol, struct sockaddr_in * address);

/**
 * \brief Extraire une IPv4.
 * \param address sockaddr_in.
 * \return Addresse IPv4.
 */
u_int32_t extract_ipv4(const struct sockaddr_in * address);

/**
 * \brief Créer une socket.
 * \param[in] family Type d'adresse.
 * \param[in] socktype Type de socket.
 * \param[in] protocol Protocole.
 * \param[in,out] sockfd Descripteur de socket.
 * \retval 0 Pas d'erreur.
 * \retval -1 Erreur.
 */
int create_raw_socket(int family, int socktype, int protocol, int * sockfd);

/**
 * \brief Obtenir socket et adresse pour un hôte.
 * \param[in] hostname Nom de l'hôte.
 * \param[in] protocol Protocole.
 * \param[in] socktype Type de socket.
 * \param[in,out] sockfd Descripteur de socket.
 * \param[in,out] address Addresse IPv4 de l'hôte.
 * \retval 0 Pas d'erreur.
 * \retval -1 Erreur.
 * \deprecated Déprécié.
 *
 * protocol = 0 pour faire une recherche sans se préocupper du protocole.
 * Dans le cas de socket nécessitant une connection, la connection sera établie.
 */
int socket_host_v4(const char * hostname, int protocol, int socktype, int * sockfd, struct sockaddr * address);

/**
 * \brief Afficher une adresse IPv4.
 * \param address Adresse IPv4.
 */
void print_ipv4_address(u_int32_t address);

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
 * \brief Afficher un hôte.
 * \param host Addresse.
 */
void print_host_v4(struct in_addr host);

#endif /* __ADDRESS_H */
