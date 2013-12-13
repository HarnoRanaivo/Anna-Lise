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

int icmp4_packet_set(icmp4_packet * packet, u_int32_t dest_address)
{
    int success = check_pointer(packet);

    if (success != 0)
        return success;

    iphdr * ip_header = &packet->ip_header;
    icmphdr * icmp_header = &packet->icmp_header;

    success += iphdr_set_version(ip_header);
    success += iphdr_set_header_length(ip_header, 5);
    success += iphdr_set_type_of_service(ip_header, 0);
    success += iphdr_set_total_length(ip_header, sizeof (icmp4_packet));
    success += iphdr_set_id(ip_header, 0);
    success += iphdr_set_fragment_offset(ip_header, 0);
    success += iphdr_set_ttl(ip_header, IPDEFTTL);
    success += iphdr_set_protocol(ip_header, 1);
    success += iphdr_set_source_address(ip_header, get_source_ipv4(IPPROTO_ICMP));
    success += iphdr_set_dest_address(ip_header, dest_address);
    /* À faire en dernier. */
    success += iphdr_checksum(ip_header);

    success += icmp_set_type(icmp_header, ICMP_ECHO);
    success += icmp_set_code(icmp_header, 0);
    success += icmp_set_echo(icmp_header, 0, 0);
    /* À faire en dernier. */
    success += icmp_checksum(icmp_header);

    return success;
}
