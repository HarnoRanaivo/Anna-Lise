/**
 * \file packet.c
 * \brief Utilitaires pour créer des paquets (implémentation)
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

#include "packet.h"

#define succeed_or_die(var, instr) \
    (var) = (instr); \
    if ((var) != 0) \
        return (var)

int icmp4_packet_init(icmp4_packet * packet, u_int32_t dest_address)
{
    int success = check_pointer(packet);

    if (success != 0)
        return success;

    memset(packet, 0, sizeof (*packet));
    iphdr * ip_header = &packet->ip_header;
    icmphdr * icmp_header = &packet->icmp_header;

    succeed_or_die(success, iphdr_set_version(ip_header));
    succeed_or_die(success, iphdr_set_header_length(ip_header, 5));
    succeed_or_die(success, iphdr_set_type_of_service(ip_header, 0));
    succeed_or_die(success, iphdr_set_total_length(ip_header, sizeof (icmp4_packet)));
    succeed_or_die(success, iphdr_set_id(ip_header, 0));
    succeed_or_die(success, iphdr_set_fragment_offset(ip_header, 0));
    succeed_or_die(success, iphdr_set_ttl(ip_header, IPDEFTTL));
    succeed_or_die(success, iphdr_set_protocol(ip_header, IPPROTO_ICMP));

    struct sockaddr_in address;
    succeed_or_die(success, get_source_ipv4(IPPROTO_ICMP, &address));
    succeed_or_die(success, iphdr_set_source_address(ip_header, extract_ipv4(&address)));

    succeed_or_die(success, iphdr_set_dest_address(ip_header, dest_address));
    /* À faire en dernier. */
    succeed_or_die(success, iphdr_checksum(ip_header));

    succeed_or_die(success, icmp_set_type(icmp_header, ICMP_ECHO));
    succeed_or_die(success, icmp_set_code(icmp_header, 0));
    succeed_or_die(success, icmp_set_echo(icmp_header, getpid(), 0));
    /* À faire en dernier. */
    succeed_or_die(success, icmp_checksum(icmp_header));

    return success;
}

int icmp4_packet_set_ttl(icmp4_packet * packet, u_int8_t ttl)
{
    int success = check_pointer(packet);

    if (success != 0)
        return success;

    iphdr * ip_header = &packet->ip_header;
    succeed_or_die(success, iphdr_set_ttl(ip_header, ttl));
    succeed_or_die(success, iphdr_checksum(ip_header));

    return success;
}

int icmp4_packet_set_echo_seq(icmp4_packet * packet, u_int16_t sequence)
{
    int success = check_pointer(packet);

    if (success != 0)
        return success;

    icmphdr * icmp_header = &packet->icmp_header;
    succeed_or_die(success, icmp_set_echo(icmp_header, icmp_header->un.echo.id, sequence));
    succeed_or_die(success, icmp_checksum(icmp_header));

    return success;
}

void icmp4_packet_print(const icmp4_packet * packet)
{
    iphdr_print(&packet->ip_header);
    icmp_print(&packet->icmp_header);
}

#undef succeed_or_die
