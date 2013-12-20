/**
 * \file traceroute.c
 * \brief Traceroute (implémentation)
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

#include "traceroute.h"

int traceroute_receive_icmp_v4(int sockfd, struct sockaddr_in * address, struct sockaddr_in * source, const struct timeval * wait_time)
{
    int answer_type = -1;
    icmp4_packet received;

    struct timeval wait = *wait_time;
    if (receive_icmp_v4(sockfd, address, &wait, &received) == 0)
    {
        answer_type = received.icmp_header.type;
        *source = (struct sockaddr_in) { AF_INET, 0, { received.ip_header.saddr }, { 0 } };
    }
    else
        printf(" *");

    return answer_type;
}

static inline void print_times(struct timeval times[], size_t array_size)
{
    for (unsigned int i = 0; i < array_size; i++)
    {
        printf(" ");
        print_timeval(times[i]);
    }
    printf("\n");
}

static inline int traceroute_icmp_v4_init(const char* hostname, int * sockfd, struct sockaddr_in * address, icmp4_packet * packet, int packet_size)
{
    int success = get_ipv4(hostname, IPPROTO_ICMP, address);

    succeed_or_die(success, 0, create_raw_socket(AF_INET, SOCK_RAW, IPPROTO_ICMP, sockfd));
    succeed_or_die(success, 0, icmp4_packet_init(packet, extract_ipv4(address)));
    succeed_or_die(success, 0, icmp4_packet_set_length(packet, packet_size));

    return success;
}

static inline void print_traceroute_greeting(int family, struct sockaddr * address, int hops_max, int packet_size)
{
    printf("traceroute to ");
    if (family == AF_INET6)
    {
        struct sockaddr_in6 * in = (struct sockaddr_in6 *) address;
        print_host_v6(in);
    }
    else
    {
        struct sockaddr_in * in = (struct sockaddr_in *) address;
        print_host_v4(in);
    }
    printf(", %d hops max, %d byte packets\n", hops_max, packet_size);
}

static int icmp_v4_exchange(int sockfd, icmp4_packet * packet, int packet_size, struct sockaddr_in * address,
        const struct timeval * wait_time, int * host_printed, struct timeval * diff)
{
    int current_type = -1;
    struct timeval start;
    struct timeval end;
    gettimeofday(&start, NULL);
    static const socklen_t address_size = sizeof (struct sockaddr_in);

    if (sendto(sockfd, packet, packet_size, 0, (struct sockaddr *) address, address_size) == packet_size)
    {
        struct sockaddr_in source;
        current_type = traceroute_receive_icmp_v4(sockfd, address, &source, wait_time);
        if (current_type != -1 && *host_printed == 1)
        {
            printf(" ");
            print_host_v4(&source);
            *host_printed = 0;
        }
        gettimeofday(&end, NULL);
        *diff = diff_timeval(start, end);
    }

    return current_type;
}

int traceroute_icmp_v4(const char * hostname, int hops_max, int attempts_number, int packet_size, const struct timeval * wait_time)
{
    int sockfd;
    struct sockaddr_in address;
    char buffer[packet_size];
    for (int i = 0; i < packet_size; i++)
        buffer[i] = 0;
    icmp4_packet * packet = (icmp4_packet *) buffer;
    int success = traceroute_icmp_v4_init(hostname, &sockfd, &address, packet, packet_size);

    if (success != 0)
        return success;

    print_traceroute_greeting(AF_INET, (struct sockaddr *)  &address, hops_max, packet_size);

    int current_type = -1;
    for (int ttl = 1; current_type != ICMP_ECHOREPLY && ttl <= hops_max; ttl++)
    {
        int printed = 1;
        struct timeval times[attempts_number];
        memset(times, 0, attempts_number * sizeof (struct timeval));

        printf("%d", ttl);
        icmp4_packet_set_ttl(packet, ttl);
        for (int attempt = 0; attempt < attempts_number; attempt++)
            current_type = icmp_v4_exchange(sockfd, packet, packet_size, &address, wait_time, &printed, &times[attempt]);
        print_times(times, attempts_number);
    }

    return success;
}

int traceroute_receive_icmp_v6(int sockfd, struct sockaddr_in6 * address, struct sockaddr_in6 * source, const struct timeval * wait_time)
{
    int answer_type = -1;
    icmp6_packet received;
    memset(&received, 0, sizeof received);

    struct timeval wait = *wait_time;
    if (receive_icmp_v6(sockfd, address, &wait, &received) == 0)
    {
        answer_type = received.icmp_header.icmp6_type;
        *source = (struct sockaddr_in6) { AF_INET6, 0, 0, received.ip_header.ip6_src, 0 };
        u_int32_t * a = (u_int32_t *) &received.ip_header.ip6_src;
        for (int i = 0; i < 4; i++)
            source->sin6_addr.__in6_u.__u6_addr32[0] = a[i];
    }
    else
        printf(" *");

    return answer_type;
}

static int icmp_v6_exchange(int sockfd, icmp6_packet * packet, int packet_size, struct sockaddr_in6 * address,
        const struct timeval * wait_time, int * host_printed, struct timeval * diff)
{
    int current_type = -1;
    struct timeval start;
    struct timeval end;
    gettimeofday(&start, NULL);
    static const socklen_t address_size = sizeof (struct sockaddr_in6);

    if (sendto(sockfd, packet, packet_size, 0, (struct sockaddr *) address, address_size) == packet_size)
    {
        struct sockaddr_in6 source;
        current_type = traceroute_receive_icmp_v6(sockfd, address, &source, wait_time);
        if (current_type != -1 && *host_printed == 1)
        {
            printf(" ");
            print_host_v6(&source);
            *host_printed = 0;
        }
        gettimeofday(&end, NULL);
        *diff = diff_timeval(start, end);
    }

    return current_type;
}

int traceroute_icmp_v6(const char * hostname, int hops_max, int attempts_number)
{
    int sockfd;
    struct sockaddr_in6 address;
    icmp6_packet packet;
    int success = -1;
    int packet_size = sizeof packet;
    struct timeval wait_time = { 1, 0 };

    succeed_or_die(success, 0, get_ipv6(hostname, IPPROTO_ICMPV6, &address));
    succeed_or_die(success, 0, create_raw_socket_v6(AF_INET6, SOCK_RAW, IPPROTO_ICMPV6, &sockfd));
    succeed_or_die(success, 0, icmp6_packet_init(&packet, &address));

    print_traceroute_greeting(AF_INET6, (struct sockaddr *) &address, hops_max, sizeof packet);
    int current_type = -1;
    for (int ttl = 1; current_type != ICMP6_ECHO_REPLY && ttl <= hops_max; ttl++)
    {
        int printed = 1;
        struct timeval times[attempts_number];
        memset(times, 0, attempts_number * sizeof (struct timeval));

        printf("%d", ttl);
        icmp6_packet_set_ttl(&packet, ttl);
        for (int attempt = 0; attempt < attempts_number; attempt++)
            current_type = icmp_v6_exchange(sockfd, &packet, packet_size, &address, &wait_time, &printed, &times[attempt]);
        print_times(times, attempts_number);
    }

    return success;
}

static inline int traceroute_udp_v4_init(const char * hostname, int * sendfd, int * listenfd, struct sockaddr_in * address, udp4_packet * packet)
{
    int success = get_ipv4(hostname, IPPROTO_UDP, address);

    if (success != 0)
        return success;

    succeed_or_die(success, 0, create_raw_socket(AF_INET, SOCK_RAW, IPPROTO_ICMP, listenfd));
    succeed_or_die(success, 0, create_raw_socket(AF_INET, SOCK_RAW, IPPROTO_UDP, sendfd));
    succeed_or_die(success, 0, udp4_packet_init(packet, address));

    return success;
}

static int udp_v4_exchange(int sendfd, int listenfd, udp4_packet * packet, int packet_size, struct sockaddr_in * address,
        const struct timeval * wait_time, int * host_printed, struct timeval * diff)
{
    int current_type = -1;
    struct timeval start;
    struct timeval end;
    gettimeofday(&start, NULL);
    static const socklen_t address_size = sizeof (struct sockaddr_in);

    if (sendto(sendfd, packet, packet_size, 0, (struct sockaddr *) address, address_size) == packet_size)
    {
        struct sockaddr_in source;
        current_type = traceroute_receive_icmp_v4(listenfd, address, &source, wait_time);
        if (current_type != -1 && *host_printed == 1)
        {
            printf(" ");
            print_host_v4(&source);
            *host_printed = 0;
        }
        gettimeofday(&end, NULL);
        *diff = diff_timeval(start, end);
    }

    return current_type;
}

int traceroute_udp_v4(const char * hostname, int hops_max, int attempts_number)
{
    int success = -1;
    int send_sockfd;
    int listen_sockfd;
    struct sockaddr_in address;
    udp4_packet packet;
    struct timeval wait_time = { 1, 0 };

    succeed_or_die(success, 0 , traceroute_udp_v4_init(hostname, &send_sockfd, &listen_sockfd, &address, &packet));

    print_traceroute_greeting(AF_INET, (struct sockaddr *) &address, hops_max, sizeof packet);
    int current_type = -1;
    for (int ttl = 1; current_type != ICMP6_ECHO_REPLY && ttl <= hops_max; ttl++)
    {
        int printed = 1;
        struct timeval times[attempts_number];
        memset(times, 0, attempts_number * sizeof (struct timeval));

        printf("%d", ttl);
        udp4_packet_set_ttl(&packet, ttl);
        for (int attempt = 0; attempt < attempts_number; attempt++)
            current_type = udp_v4_exchange(send_sockfd, listen_sockfd, &packet, sizeof packet, &address, &wait_time, &printed, &times[attempt]);
        print_times(times, attempts_number);
    }

    return success;
}
