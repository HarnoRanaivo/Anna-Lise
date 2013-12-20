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
        if (results->ai_family == AF_INET6)
        {
            struct sockaddr_in6 * a = (struct sockaddr_in6 *) address;
            struct sockaddr_in6 * r = (struct sockaddr_in6 *) results->ai_addr;
            *a = *r;
        }
        freeaddrinfo(results);
    }

    return success;
}

int get_ipv4(const char * hostname, int protocol, struct sockaddr_in * address)
{
    return get_ip(hostname, AF_INET, SOCK_RAW, protocol, (struct sockaddr *) address);
}

int get_ipv6(const char * hostname, int protocol, struct sockaddr_in6 * address)
{
    return get_ip(hostname, AF_INET6, SOCK_RAW, protocol, (struct sockaddr *) address);
}

int get_source_ipv4(int protocol, struct sockaddr_in * address)
{
    /* Voir la section NOTES du man(2) de gethostname pour la taille
     * du buffer.
     */
    char buffer[HOST_NAME_MAX+1];
    gethostname(buffer, HOST_NAME_MAX+1);

    int success = get_ipv4(buffer, protocol, address);

    /* Workaround pour obtenir une adresse de la machine.
     *
     * Sur certaines machines getaddrinfo retourne pour unique adresse 127.0.0.1
     * lorsqu'on donne le hostname de la machine...
     * Sur d'autres elle retourne bien les adresses des interfaces
     * de la machine.
     *
     * De même avec les « vrais » ping et traceroute:
     * `ping localhost` et `ping <hostname de la machine>` vont tous deux se faire sur
     * 127.0.0.1, mais sur d'autres machines se feront sur deux adresses différentes.
     * Configuration des machines ? Versions des logiciels ? ...?
     *
     * Avec ça, ça fonctionne partout :
     */
    const in_addr_t REFUSED_IPV4 = inet_addr("127.0.0.1");
    if (address->sin_addr.s_addr == REFUSED_IPV4)
        success = get_interface_ipv4(address);

    return success;
}

int get_source_ipv6(int protocol, struct sockaddr_in6 * address)
{
    char buffer[HOST_NAME_MAX+1];
    gethostname(buffer, HOST_NAME_MAX+1);

    int success = get_ipv6(buffer, protocol, address);

    return success;
}

int get_interface_ipv4(struct sockaddr_in * address)
{
    struct ifaddrs * results;
    const in_addr_t REFUSED_IPV4 = inet_addr("127.0.0.1");

    int success = getifaddrs(&results);
    if (success == 0)
    {
        success = -1;
        for (const struct ifaddrs * r = results; success == -1 && r != NULL; r = r->ifa_next)
            if (r->ifa_addr != NULL && r->ifa_addr->sa_family == AF_INET)
            {
                struct sockaddr_in * s = (struct sockaddr_in *) r->ifa_addr;
                if (s->sin_addr.s_addr != REFUSED_IPV4)
                {
                    *address = *s;
                    success = 0;
                }
            }
        freeifaddrs(results);
    }

    return success;
}

static inline int compare_ipv6(struct in6_addr * address_1, struct in6_addr * address_2)
{
    int identical = 0;

    for (int i = 0; identical == 0 && i < 4; i++)
        if (address_1->__in6_u.__u6_addr32[i] != address_2->__in6_u.__u6_addr32[i])
            identical = -1;

    return identical;
}

int get_interface_ipv6(struct sockaddr_in6 * address)
{
    struct ifaddrs * results;
    struct in6_addr REFUSED_IPV6;
    inet_pton(AF_INET6, "::1", &REFUSED_IPV6);

    int success = getifaddrs(&results);
    if (success == 0)
    {
        success = -1;
        for (const struct ifaddrs * r = results; success == -1 && r != NULL; r = r->ifa_next)
            if (r->ifa_addr != NULL && r->ifa_addr->sa_family == AF_INET6)
            {
                struct sockaddr_in6 * s = (struct sockaddr_in6 *) r->ifa_addr;
                if (compare_ipv6(&s->sin6_addr, &REFUSED_IPV6) == -1)
                {
                    char buffer[INET6_ADDRSTRLEN];
                    if (inet_ntop(AF_INET6, &s->sin6_addr, buffer, INET6_ADDRSTRLEN) != NULL)
                        if (strncmp(buffer, "fe80::", 6) != 0)
                        {
                            *address = *s;
                            success = 0;
                        }
                }
            }
        freeifaddrs(results);
    }

    return success;
}
u_int32_t extract_ipv4(const struct sockaddr_in * address)
{
    u_int32_t result = 0;
    if (check_pointer(address) == 0)
        result = address->sin_addr.s_addr;

    return result;
}

void print_ip(int family, struct sockaddr * address)
{
    void * in;
    char buffer[INET6_ADDRSTRLEN];
    if (family == AF_INET)
    {
        struct sockaddr_in * a = (struct sockaddr_in *)address;
        in = &a->sin_addr;
    }
    else
    {
        struct sockaddr_in6 * a = (struct sockaddr_in6 *)address;
        in = &a->sin6_addr;
    }

    if (inet_ntop(family, in, buffer, INET6_ADDRSTRLEN) != NULL)
        printf("%s\n", buffer);
}

void print_ipv4_address(u_int32_t address)
{
    printf("%s\n", inet_ntoa((struct in_addr) { address }));
}

int reverse_dns_v4(char * buffer, size_t buffer_size, struct in_addr address)
{
    struct sockaddr_in source = { AF_INET, 0, address, { 0 } };
    return getnameinfo((struct sockaddr *)&source, sizeof source, buffer, buffer_size, NULL, 0, 0);
}

void print_host_v4(struct in_addr host)
{
    size_t buffer_size = 256;
    char buffer[buffer_size];
    reverse_dns_v4(buffer, buffer_size, host);
    printf("%s (%s)", buffer, inet_ntoa(host));
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
