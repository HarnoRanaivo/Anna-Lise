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

int traceroute_receive_icmp_v4(int sockfd, struct sockaddr_in * address, struct sockaddr_in * source, struct timeval * wait_time)
{
    int answer_type = -1;
    icmp4_packet received;

    if (receive_icmp_v4(sockfd, address, wait_time, &received) == 0)
    {
        answer_type = received.icmp_header.type;
        *source = (struct sockaddr_in) { AF_INET, 0, { received.ip_header.saddr }, { 0 } };
    }
    else
        printf(" *");

    return answer_type;
}

static inline int icmp_v4_init(const char * hostname, int * sockfd, struct sockaddr_in * address, icmp4_packet * packet)
{
    int success = create_raw_socket(AF_INET, SOCK_RAW, IPPROTO_ICMP, sockfd);
    if (success == 0)
        success = get_ipv4(hostname, IPPROTO_ICMP, address);
    if (success == 0)
        success = icmp4_packet_init(packet, extract_ipv4(address));
    return success;
}

/* Afficher un tableau de struct timeval. */
static inline void print_times(struct timeval times[], size_t array_size)
{
    for (unsigned int i = 0; i < array_size; i++)
    {
        printf(" ");
        print_timeval(times[i]);
    }
    printf("\n");
}

static inline int icmp_v4_exchange(int sockfd, struct sockaddr_in * address, void * packet,
    int packet_size, struct timeval * time, struct timeval * wait_time, int * host_printed)
{
    static const socklen_t address_size = sizeof (struct sockaddr_in);
    int current_type = -1;
    struct timeval start;
    struct timeval end;

    gettimeofday(&start, NULL);
    if (sendto(sockfd, packet, packet_size, 0, (struct sockaddr *) address, address_size) == packet_size)
    {
        struct sockaddr_in source;
        current_type = traceroute_receive_icmp_v4(sockfd, address, &source, wait_time);
        gettimeofday(&end, NULL);
        *time = diff_timeval(start, end);
        if (current_type != -1 && *host_printed == 1)
        {
            printf(" ");
            print_host_v4(source.sin_addr);
            *host_printed = 0;
        }
    }
    return current_type;
}

int traceroute_icmp_v4(const char * hostname, int hops_max, int attempts_number, int packet_size, struct timeval * wait_time)
{
    int sockfd;
    char buffer[packet_size];
    icmp4_packet * packet = (icmp4_packet *) buffer;
    struct sockaddr_in address;
    int success = icmp_v4_init(hostname, &sockfd, &address, packet);

    if (success != 0)
        return success;

    printf("traceroute to ");
    print_host_v4(address.sin_addr);
    printf(", %d hops max, %d byte packets\n", hops_max, packet_size);

    int current_type = -1;
    for (int ttl = 1; current_type != ICMP_ECHOREPLY && ttl <= hops_max; ttl++)
    {
        printf("%d", ttl);
        icmp4_packet_set_ttl(packet, ttl);
        struct timeval times[attempts_number];
        memset(times, 0, attempts_number * sizeof (struct timeval));

        int host_printed = 1;
        for (int attempt = 0; attempt < attempts_number; attempt++)
            current_type = icmp_v4_exchange(sockfd, &address, packet, packet_size, &times[attempt], wait_time, &host_printed);
        print_times(times, attempts_number);
    }

    return success;
}
