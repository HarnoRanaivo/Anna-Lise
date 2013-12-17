/**
 * \file address.c
 * \brief Utilitaires pour obtenir des addresses. (implémentation)
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

#include "address.h"

static inline void addrinfo_hints(struct addrinfo * hints, int family, int socktype, int protocol, int flags)
{
    memset(hints, 0, sizeof *hints);
    hints->ai_family = family;
    hints->ai_socktype = socktype;
    hints->ai_protocol = protocol;
    hints->ai_flags = flags;
}

int get_ip(const char * hostname, int family, int socktype, int protocol, struct sockaddr * address)
{
    int success = -1;
    struct addrinfo hints;
    struct addrinfo * results;

    addrinfo_hints(&hints, family, socktype, protocol, 0);
    success = getaddrinfo(hostname, NULL, &hints, &results);
    if (success == 0)
    {
        *address = *results->ai_addr;
        freeaddrinfo(results);
    }

    return success;
}

int get_ipv4(const char * hostname, int protocol, struct sockaddr_in * address)
{
    return get_ip(hostname, AF_INET, SOCK_RAW, protocol, (struct sockaddr *) address);
}

int get_source_ipv4(int protocol, struct sockaddr_in * address)
{
    /* Voir la section NOTES du man(2) de gethostname pour la taille
     * du buffer.
     */
    char buffer[HOST_NAME_MAX+1];
    gethostname(buffer, HOST_NAME_MAX+1);

    return get_ipv4(buffer, protocol, address);
}

u_int32_t extract_ipv4(struct sockaddr_in * address)
{
    u_int32_t result = 0;
    if (check_pointer(address) == 0)
        result = address->sin_addr.s_addr;

    return result;
}

int create_raw_socket(int family, int socktype, int protocol, int * sockfd)
{
    int success = -1;
    int optval;

    *sockfd = socket(family, socktype, protocol);
    if (*sockfd != -1)
        success = setsockopt(*sockfd, IPPROTO_IP, IP_HDRINCL, &optval, sizeof optval);

    return success;
}

int socket_host_v4(const char * hostname, int protocol, int socktype, int * sockfd, struct sockaddr * address)
{
    int success = -1;
    struct addrinfo hints;
    struct addrinfo * results;

    /* AF_INET : forcer IPv4. */
    addrinfo_hints(&hints, AF_INET, socktype, protocol, 0);
    getaddrinfo(hostname, NULL, &hints, &results);
    int go_on = 1;
    printf("%s\n", hostname);
    for (const struct addrinfo * r = results; go_on == 1 && r != NULL; r = r->ai_next)
    {
        *sockfd = socket(AF_INET, socktype, protocol);
        if (*sockfd != -1)
        {
            printf("socket\n");
            /* Si la socket nécessite une connection...
             * Mais on n'utilisera que des SOCK_RAW...on laisse pour l'instant.
             */
            int connected = -1;
            if (socktype == SOCK_STREAM)
            {
                connected = connect(*sockfd, r->ai_addr, r->ai_addrlen);
                if (connected == -1)
                    close(*sockfd);
            }

            /* Si la socket ne nécessite pas de connection, c'est bon.
             * Si la socket en nécessite une, elle doit être connectée.
             */
            if (socktype != SOCK_STREAM || connected == 0)
            {
                *address = *results->ai_addr;
                go_on = 0;
                success = 0;
            }
        }
    }

    freeaddrinfo(results);

    return success;
}

void print_ipv4_address(u_int32_t address)
{
    struct in_addr in = { address };
    printf("%s\n", inet_ntoa(in));
}
