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

/* IPv4 */
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

/* IPv6 */
static inline int check_ipv6_version(unsigned int version)
{
    int success = 0;
    if (version != 6)
    {
        success = -2;
        errno = EINVAL;
    }
    return success;
}

static inline int check_ip6_hdr(ip6_hdr * header)
{
    ip6_hdr_first_part * beginning = (ip6_hdr_first_part *) header;
    int success = check_pointer(header);
    if (success == 0 && beginning->version != 6)
    {
        success = -2;
        errno = EINVAL;
    }
    return success;
}

int ip6_hdr_set_version(ip6_hdr * header)
{
    int success = check_pointer(header);

    if (success == 0)
    {
        ip6_hdr_first_part * beginning = (ip6_hdr_first_part *) header;
        beginning->version = 6;
    }

    return success;
}

int ip6_hdr_set_traffic_class(ip6_hdr * header, u_int8_t traffic_class)
{
    int success = check_ip6_hdr(header);

    if (success == 0)
    {
        ip6_hdr_first_part * beginning = (ip6_hdr_first_part *) header;
        beginning->traffic_class = traffic_class;
    }

    return success;
}

int ip6_hdr_set_flow_label(ip6_hdr * header, unsigned int label)
{
    int success = check_ip6_hdr(header);

    if (success == 0)
    {
        ip6_hdr_first_part * beginning = (ip6_hdr_first_part *) header;
        beginning->flow_label = label;
    }

    return success;
}

int ip6_hdr_set_payload_length(ip6_hdr * header, uint16_t length)
{
    int success = check_ip6_hdr(header);

    if (success == 0)
        header->ip6_ctlun.ip6_un1.ip6_un1_plen = length;

    return success;
}

int ip6_hdr_set_next_header(ip6_hdr * header, uint8_t next_header)
{
    int success = check_ip6_hdr(header);

    if (success == 0)
        header->ip6_ctlun.ip6_un1.ip6_un1_nxt = next_header;

    return success;
}

int ip6_hdr_set_hop_limit(ip6_hdr * header, uint8_t limit)
{
    int success = check_ip6_hdr(header);

    if (success == 0)
        header->ip6_ctlun.ip6_un1.ip6_un1_hlim = limit;

    return success;
}

static inline void copy_in6_addr(struct in6_addr * copy, struct in6_addr * original)
{
    for (int i = 0; i < 4; i++)
        copy->__in6_u.__u6_addr32[i] = original->__in6_u.__u6_addr32[i];
}

int ip6_hdr_set_source(ip6_hdr * header, sockaddr_in6 * address)
{
    int success = check_ip6_hdr(header);

    if (success == 0)
        success = check_pointer(address);
    if (success == 0)
        copy_in6_addr(&header->ip6_src, &address->sin6_addr);

    return success;
}

int ip6_hdr_set_destination(ip6_hdr * header, sockaddr_in6 * address)
{
    int success = check_ip6_hdr(header);

    if (success == 0)
        success = check_pointer(address);
    if (success == 0)
        copy_in6_addr(&header->ip6_dst, &address->sin6_addr);

    return success;
}

int fake_ip6_hdr_set_source(fake_ip6_hdr * header, struct in6_addr * address)
{
    int success = check_pointer(header);

    if (success == 0)
        success = check_pointer(address);
    if (success == 0)
        header->source = *address;

    return success;
}

int fake_ip6_hdr_set_destination(fake_ip6_hdr * header, struct in6_addr * address)
{
    int success = check_pointer(header);

    if (success == 0)
        success = check_pointer(address);
    if (success == 0)
        header->destination = *address;

    return success;
}

int fake_ip6_hdr_set_length(fake_ip6_hdr * header, uint32_t length)
{
    int success = check_pointer(header);

    if (success == 0)
        header->length = length;

    return success;
}

int fake_ip6_hdr_set_zeros(fake_ip6_hdr * header)
{
    int success = check_pointer(header);

    if (success == 0)
        for (int i = 0; i < 3; i++)
            header->zeros[i] = 0;

    return success;
}

int fake_ip6_hdr_set_next_header(fake_ip6_hdr * header, uint8_t next_header)
{
    int success = check_pointer(header);

    if (success == 0)
        header->next_header = next_header;

    return success;
}

int fake_ip6_hdr_init(fake_ip6_hdr * fake, ip6_hdr * header)
{
    int success = check_pointer(fake);

    succeed_or_die(success, 0, check_pointer(header));
    succeed_or_die(success, 0, fake_ip6_hdr_set_source(fake, &header->ip6_src));
    succeed_or_die(success, 0, fake_ip6_hdr_set_destination(fake, &header->ip6_dst));
    succeed_or_die(success, 0, fake_ip6_hdr_set_length(fake, header->ip6_ctlun.ip6_un1.ip6_un1_plen));
    succeed_or_die(success, 0, fake_ip6_hdr_set_zeros(fake));
    succeed_or_die(success, 0, fake_ip6_hdr_set_next_header(fake, header->ip6_ctlun.ip6_un1.ip6_un1_nxt));

    return success;
}

void ip6_hdr_print(const ip6_hdr * header)
{
    int ok = check_pointer(header);

    if (ok == 0)
    {
        const ip6_hdr_first_part * beginning = (const ip6_hdr_first_part *) header;
        printf("IP version: %d\n", beginning->version);
        printf("IP traffic class: %d\n", beginning->traffic_class);
        printf("IP flow label: %d\n", beginning->flow_label);
        printf("IP payload length: %d\n", header->ip6_ctlun.ip6_un1.ip6_un1_plen);
        printf("IP next header: %d\n", header->ip6_ctlun.ip6_un1.ip6_un1_nxt);
        printf("IP hop limit: %d\n", header->ip6_ctlun.ip6_un1.ip6_un1_hlim);

        char buffer[INET6_ADDRSTRLEN];
        if (inet_ntop(AF_INET6, &header->ip6_src, buffer, INET6_ADDRSTRLEN) != NULL)
            printf("IP source: %s\n", buffer);
        if (inet_ntop(AF_INET6, &header->ip6_dst, buffer, INET6_ADDRSTRLEN) != NULL)
            printf("IP dest: %s\n", buffer);
    }
}

void fake_ip6_hdr_print(const fake_ip6_hdr * header)
{
    int ok = check_pointer(header);

    if (ok == 0)
    {
        char buffer[INET6_ADDRSTRLEN];
        if (inet_ntop(AF_INET6, &header->source, buffer, INET6_ADDRSTRLEN) != NULL)
            printf("IP source: %s\n", buffer);
        if (inet_ntop(AF_INET6, &header->destination, buffer, INET6_ADDRSTRLEN) != NULL)
            printf("IP destination: %s\n", buffer);
        printf("IP length: %d\n", header->length);
        printf("IP next header: %d\n", header->next_header);
    }

}
