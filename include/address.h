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
#include <ifaddrs.h>

#include "base.h"

typedef struct sockaddr sockaddr;
typedef struct sockaddr_in sockaddr_in;
typedef struct sockaddr_in6 sockaddr_in6;

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
 * \brief Afficher une addresse IP.
 * \param family Type d'adresse.
 * \param address Adresse.
 */
void print_ip(int family, struct sockaddr * address);

/**
 * \brief Obtenir une adresse IPv4.
 * \param hostname Nom d'hôte.
 * \param protocol Protocole.
 * \return Adresse IPv4.
 */
int get_ipv4(const char * hostname, int protocol, struct sockaddr_in * address);

/**
 * \brief Obtenir une adresse IPv6.
 * \param hostname Nom d'hôte.
 * \param protocol Protocole.
 * \return Adresse IPv6.
 */
int get_ipv6(const char * hostname, int protocol, struct sockaddr_in6 * address);
/**
 * \brief Obtenir l'adresse IPv4 de la machine.
 * \param protocol Protocole.
 * \return Adresse IPv4.
 */
int get_source_ipv4(int protocol, struct sockaddr_in * address);

/**
 * \brief Obtenir l'adresse IPv6 de la machine.
 * \param protocol Protocole.
 * \return Adresse Ipv6.
 */
int get_source_ipv6(int protocol, struct sockaddr_in6 * address);

/**
 * \brief Rechercher une adresse IPv4 parmi celles des interfaces de la machine.
 * \param[in,out] address Adresse.
 * \retval 0 Pas d'erreur.
 * \retval -1 Erreur.
 */
int get_interface_ipv4(struct sockaddr_in * address);

/**
 * \brief Rechercher une addresse IPv6 parmi celles des interfaces de la machine.
 * \param[în,out] address Adresse.
 * \retval 0 Pas d'erreur.
 * \retval -1 Erreur.
 */
int get_interface_ipv6(struct sockaddr_in6 * address);

/**
 * \brief Extraire une IPv4.
 * \param address sockaddr_in.
 * \return Addresse IPv4.
 */
u_int32_t extract_ipv4(const struct sockaddr_in * address);

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
int reverse_dns_v4(char * buffer, size_t buffer_size, struct sockaddr_in * address);

/**
 * \brief Afficher un hôte.
 * \param host Addresse.
 *
 * Affichage sous la forme "nom d'hôte (addresse)".
 */
void print_host_v4(struct sockaddr_in * address);

void print_host_v6(struct sockaddr_in6 * address);
int reverse_dns_v6(char * buffer, size_t buffer_size, struct sockaddr_in6 * address);
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

#endif /* __ADDRESS_H */
