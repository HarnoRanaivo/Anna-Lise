/**
 * \file ip_util.c
 * \brief Utilitaires IP (implémentation)
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

#include "ip_util.h"

static inline int check_ipv4_version(unsigned int version)
{
    int success = 0;
    if (version != IPVERSION)
    {
        success = -2;
        errno = EINVAL;
    }
    return success;
}

static inline int check_iphdr(iphdr * header)
{
    int success = check_pointer(header);
    if (success == 0 && header->version != 4)
    {
        success = -2;
        errno = EINVAL;
    }
    return success;
}

static inline int check_domain(unsigned int value, unsigned int min, unsigned int max)
{
    int success = 0;
    if (value < min || value > max)
    {
        success = -3;
        errno = EDOM;
    }
    return success;
}

int iphdr_set_version(iphdr * header)
{
    int success = check_pointer(header);

    if (success == 0)
        header->version = IPVERSION;

    return success;
}

int iphdr_set_header_length(iphdr * header, unsigned int length)
{
    int success = check_iphdr(header);

    if (success == 0)
        success = check_domain(length, 5, 15);

    if (success == 0)
        header->ihl = length;

    return success;
}

int iphdr_set_type_of_service(iphdr * header, u_int8_t service)
{
    int success = check_iphdr(header);

    if (success == 0)
        header->tos = service;

    return success;
}

int iphdr_set_total_length(iphdr * header, u_int16_t length)
{
    int success = check_iphdr(header);

    if (success == 0)
        success = check_domain(length, 20, IP_MAXPACKET);
    if (success == 0)
        header->tot_len = length;

    return success;
}

int iphdr_set_id(iphdr * header, u_int16_t id)
{
    int success = check_iphdr(header);

    if (success == 0)
        header->id = id;

    return success;
}

int iphdr_set_flags(iphdr * header, unsigned int flags)
{
    int success = check_iphdr(header);

    if (success == 0)
        header->frag_off = flags;

    return success;
}

int iphdr_set_fragment_offset(iphdr * header, unsigned int offset)
{
    int success = check_iphdr(header);

    if (success == 0)
        header->frag_off = offset;

    return success;
}

int iphdr_set_ttl(iphdr * header, u_int8_t ttl)
{
    int success = check_iphdr(header);

    if (success == 0)
        success = check_domain(ttl, 1, MAXTTL);
    if (success == 0)
        header->ttl = ttl;

    return success;
}

int iphdr_set_protocol(iphdr * header, u_int8_t protocol)
{
    int success = check_iphdr(header);

    if (success == 0)
        header->protocol = protocol;

    return success;
}

int iphdr_checksum(iphdr * header)
{
    int success = check_iphdr(header);

    if (success == 0)
    {
        u_int16_t old_sum = header->check;
        header->check = 0;
        header->check = checksum(header, (sizeof *header) / 2);
        u_int16_t check = checksum(header, (sizeof *header) / 2);
        if (check != 0)
        {
            header->check = old_sum;
            errno = ECANCELED;
            success = -3;
        }
    }

    return success;
}

int iphdr_set_source_address(iphdr * header, u_int32_t address)
{
    int success = check_iphdr(header);

    if (success == 0)
        header->saddr = address;

    return success;
}

int iphdr_set_dest_address(iphdr * header, u_int32_t address)
{
    int success = check_iphdr(header);

    if (success == 0)
        header->daddr = address;

    return success;
}

void iphdr_print(const iphdr * header)
{
    int ok = check_pointer(header);

    if (ok == 0)
    {
        printf("IP ihl: %d\n", header->ihl);
        printf("IP version: %d\n", header->version);
        printf("IP tos: %d\n", header->tos);
        printf("IP total length: %d\n", header->tot_len);
        printf("IP id: %d\n", header->id);
        printf("IP fragment_offset: %d\n", header->frag_off);
        printf("IP ttl: %d\n", header->ttl);
        printf("IP protocol: %d\n", header->protocol);
        printf("IP checksum: %d\n", header->check);
        printf("IP source: ");
        print_ipv4_address(header->saddr);
        printf("IP dest: ");
        print_ipv4_address(header->daddr);
    }
}
