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

u_int32_t get_ipv4(const char * hostname, int protocol)
{
    struct addrinfo hints;
    struct addrinfo * results;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = 0;
    hints.ai_protocol = protocol;
    hints.ai_flags = 0;

    getaddrinfo(hostname, NULL, &hints, &results);

    /* Première addresse IP. */
    struct sockaddr_in * s = (struct sockaddr_in *) results->ai_addr;
    u_int32_t address = s->sin_addr.s_addr;

    freeaddrinfo(results);

    return address;
}

u_int32_t get_source_ipv4(int protocol)
{
    /* Voir la section NOTES du man(2) de gethostname pour la taille
     * du buffer.
     */
    char buffer[HOST_NAME_MAX];
    gethostname(buffer, HOST_NAME_MAX);

    u_int32_t address = get_ipv4(buffer, protocol);

    return address;
}
