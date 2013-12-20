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

int icmp4_packet_init(icmp4_packet * packet, u_int32_t dest_address)
{
    int success = check_pointer(packet);

    if (success != 0)
        return success;

    memset(packet, 0, sizeof (*packet));
    iphdr * ip_header = &packet->ip_header;
    icmphdr * icmp_header = &packet->icmp_header;

    succeed_or_die(success, 0, iphdr_set_version(ip_header));
    succeed_or_die(success, 0, iphdr_set_header_length(ip_header, 5));
    succeed_or_die(success, 0, iphdr_set_type_of_service(ip_header, 0));
    succeed_or_die(success, 0, iphdr_set_total_length(ip_header, sizeof (icmp4_packet)));
    succeed_or_die(success, 0, iphdr_set_id(ip_header, 0));
    succeed_or_die(success, 0, iphdr_set_fragment_offset(ip_header, 0));
    succeed_or_die(success, 0, iphdr_set_ttl(ip_header, IPDEFTTL));
    succeed_or_die(success, 0, iphdr_set_protocol(ip_header, IPPROTO_ICMP));

    struct sockaddr_in address;
    succeed_or_die(success, 0, get_source_ipv4(IPPROTO_ICMP, &address));
    succeed_or_die(success, 0, iphdr_set_source_address(ip_header, extract_ipv4(&address)));

    succeed_or_die(success, 0, iphdr_set_dest_address(ip_header, dest_address));
    /* À faire en dernier. */
    succeed_or_die(success, 0, iphdr_checksum(ip_header));

    succeed_or_die(success, 0, icmp_set_type(icmp_header, ICMP_ECHO));
    succeed_or_die(success, 0, icmp_set_code(icmp_header, 0));
    succeed_or_die(success, 0, icmp_set_echo(icmp_header, getpid(), 0));
    /* À faire en dernier. */
    succeed_or_die(success, 0, icmp_checksum(icmp_header));

    return success;
}

int icmp4_packet_set_length(icmp4_packet * packet, u_int16_t length)
{
    int success = check_pointer(packet);

    if (success != 0)
        return success;

    iphdr * ip_header = &packet->ip_header;
    succeed_or_die(success, 0, iphdr_set_total_length(ip_header, length));

    return success;
}

int icmp4_packet_set_ttl(icmp4_packet * packet, u_int8_t ttl)
{
    int success = check_pointer(packet);

    if (success != 0)
        return success;

    iphdr * ip_header = &packet->ip_header;
    succeed_or_die(success, 0, iphdr_set_ttl(ip_header, ttl));
    succeed_or_die(success, 0, iphdr_checksum(ip_header));

    return success;
}

int icmp4_packet_set_echo_seq(icmp4_packet * packet, u_int16_t sequence)
{
    int success = check_pointer(packet);

    if (success != 0)
        return success;

    icmphdr * icmp_header = &packet->icmp_header;
    succeed_or_die(success, 0, icmp_set_echo(icmp_header, icmp_header->un.echo.id, sequence));
    succeed_or_die(success, 0, icmp_checksum(icmp_header));

    return success;
}

void icmp4_packet_print(const icmp4_packet * packet)
{
    iphdr_print(&packet->ip_header);
    icmp_print(&packet->icmp_header);
}

int receive_icmp_v4(int sockfd, struct sockaddr_in * address, struct timeval * wait_time, icmp4_packet * packet)
{
    int success = -1;
    fd_set socket_set;
    socklen_t address_size = sizeof (struct sockaddr_in);

    FD_ZERO(&socket_set);
    FD_SET(sockfd, &socket_set);
    if (select(sockfd + 1, &socket_set, NULL, NULL, wait_time) != -1)
        if (FD_ISSET(sockfd, &socket_set))
            if (recvfrom(sockfd, packet, sizeof *packet, 0, (struct sockaddr *) address, &address_size) != -1)
                success = 0;

    return success;
}

int icmp6_packet_init(icmp6_packet * packet, struct sockaddr_in6 * address)
{
    int success = check_pointer(packet);

    if (success != 0)
        return success;

    memset(packet, 0, sizeof (*packet));
    ip6_hdr * ip_header = &packet->ip_header;
    icmp6_hdr * icmp_header = &packet->icmp_header;

    succeed_or_die(success, 0, ip6_hdr_set_version(ip_header));
    /* printf("version\n"); */
    succeed_or_die(success, 0, ip6_hdr_set_traffic_class(ip_header, 0));
    /* printf("traffic class\n"); */
    succeed_or_die(success, 0, ip6_hdr_set_flow_label(ip_header, 0));
    /* printf("flow\n"); */
    succeed_or_die(success, 0, ip6_hdr_set_payload_length(ip_header, sizeof *packet));
    /* printf("length\n"); */
    succeed_or_die(success, 0, ip6_hdr_set_next_header(ip_header, 58));
    /* printf("next\n"); */
    succeed_or_die(success, 0, ip6_hdr_set_hop_limit(ip_header, 64));
    /* printf("hop\n"); */
    struct sockaddr_in6 source;
    succeed_or_die(success, 0, get_source_ipv6(IPPROTO_ICMPV6, &source));
    /* printf("source get\n"); */
    succeed_or_die(success, 0, ip6_hdr_set_source(ip_header, &source));
    /* printf("source set\n"); */
    succeed_or_die(success, 0, ip6_hdr_set_destination(ip_header, address));
    /* printf("destination\n"); */

    succeed_or_die(success, 0, icmp6_set_type(icmp_header, ICMP6_ECHO_REQUEST));
    /* printf("type\n"); */
    succeed_or_die(success, 0, icmp6_set_code(icmp_header, 0));
    /* printf("code\n"); */
    succeed_or_die(success, 0, icmp6_set_echo(icmp_header, getpid(), 0));
    /* printf("echo\n"); */

    /* À faire en dernier. */
    succeed_or_die(success, 0, icmp6_packet_checksum(packet));
    /* printf("check\n"); */

    return 0;
}

static inline void copy_icmp6(icmp6_hdr * copy, icmp6_hdr * original)
{
    copy->icmp6_type = original->icmp6_type;
    copy->icmp6_code = original->icmp6_code;
    copy->icmp6_cksum = original->icmp6_cksum;
    copy->icmp6_dataun.icmp6_un_data32[0] = original->icmp6_dataun.icmp6_un_data32[0];
}

int icmp6_packet_checksum(icmp6_packet * packet)
{
    int success = check_pointer(packet);

    if (success == 0)
    {
        icmp6_checksum_packet temporary_packet;
        memset(&temporary_packet, 0, sizeof temporary_packet);
        fake_ip6_hdr_init(&temporary_packet.ip_header, &packet->ip_header);
        copy_icmp6(&temporary_packet.icmp_header, &packet->icmp_header);

        icmp6_hdr * icmp_header = &temporary_packet.icmp_header;
        icmp_header->icmp6_cksum = 0;
        /* printf("\n"); */
        /* icmp6_checksum_packet_print(&temporary_packet); */
        temporary_packet.icmp_header.icmp6_cksum = checksum(&temporary_packet, (sizeof temporary_packet) / 2);
        u_int16_t check = checksum(&temporary_packet, (sizeof temporary_packet) / 2);
        if (check != 0)
        {
            errno = ECANCELED;
            success = -2;
        }
        else
            packet->icmp_header.icmp6_cksum = temporary_packet.icmp_header.icmp6_cksum;
    }

    return success;
}

int icmp6_packet_set_length(icmp6_packet * packet, u_int16_t length)
{
    int success = check_pointer(packet);

    if (success != 0)
        return success;

    ip6_hdr * ip_header = &packet->ip_header;
    succeed_or_die(success, 0, ip6_hdr_set_payload_length(ip_header, length));
    succeed_or_die(success, 0, icmp6_packet_checksum(packet));

    return success;
}

int icmp6_packet_set_ttl(icmp6_packet * packet, u_int8_t ttl)
{
    int success = check_pointer(packet);

    if (success != 0)
        return success;

    ip6_hdr * ip_header = &packet->ip_header;
    succeed_or_die(success, 0, ip6_hdr_set_hop_limit(ip_header, ttl));
    succeed_or_die(success, 0, icmp6_packet_checksum(packet));

    return success;
}

int icmp6_packet_set_echo_seq(icmp6_packet * packet, u_int16_t sequence)
{
    int success = check_pointer(packet);

    if (success != 0)
        return success;

    icmp6_hdr * icmp_header = &packet->icmp_header;
    succeed_or_die(success, 0, icmp6_set_echo(icmp_header, icmp_header->icmp6_dataun.icmp6_un_data16[0], sequence));
    succeed_or_die(success, 0, icmp6_packet_checksum(packet));
    return success;
}

void icmp6_packet_print(const icmp6_packet * packet)
{
    const ip6_hdr * ip_header = &packet->ip_header;
    const icmphdr * icmp_header = (const icmphdr *) &packet->icmp_header;
    ip6_hdr_print(ip_header);
    icmp_print(icmp_header);
}

int receive_icmp_v6(int sockfd, struct sockaddr_in6 * address, struct timeval * wait_time, icmp6_packet * packet)
{
    int success = -1;
    fd_set socket_set;
    socklen_t address_size = sizeof (struct sockaddr_in6);

    FD_ZERO(&socket_set);
    FD_SET(sockfd, &socket_set);
    if (select(sockfd + 1, &socket_set, NULL, NULL, wait_time) != -1)
        if (FD_ISSET(sockfd, &socket_set))
            if (recvfrom(sockfd, packet, sizeof *packet, 0, (struct sockaddr *) address, &address_size) == sizeof *packet)
                success = 0;

    return success;
}

void icmp6_checksum_packet_print(icmp6_checksum_packet * packet)
{
    fake_ip6_hdr * ip_header = &packet->ip_header;
    icmp6_hdr * icmp_header = &packet->icmp_header;

    printf("fake:\n");
    fake_ip6_hdr_print(ip_header);
    icmp_print((icmphdr *) icmp_header);
}
