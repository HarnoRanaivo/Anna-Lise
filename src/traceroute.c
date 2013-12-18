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

int receive_icmp_v4(int sockfd, struct sockaddr_in * address, icmp4_packet * packet)
{
    int success = -1;
    fd_set socket_set;
    struct timeval wait_time = { 1, 0 };
    socklen_t address_size = sizeof (struct sockaddr_in);

    FD_ZERO(&socket_set);
    FD_SET(sockfd, &socket_set);
    if (select(sockfd + 1, &socket_set, NULL, NULL, &wait_time) != -1)
        if (FD_ISSET(sockfd, &socket_set))
            if (recvfrom(sockfd, packet, sizeof *packet, 0, (struct sockaddr *) address, &address_size) != -1)
                success = 0;

    return success;
}

int traceroute_receive_icmp_v4(int sockfd, struct sockaddr_in * address, struct sockaddr_in * source, struct timeval * time)
{
    int answer_type = -1;
    icmp4_packet received;
    struct timeval start;
    struct timeval end;

    gettimeofday(&start, NULL);
    if (receive_icmp_v4(sockfd, address, &received) == 0)
    {
        answer_type = received.icmp_header.type;
        *source = (struct sockaddr_in) { AF_INET, 0, { received.ip_header.saddr }, { 0 } };
    }
    else
        printf(" *");

    gettimeofday(&end, NULL);
    *time = diff_timeval(start, end);

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

int traceroute_icmp_v4(const char * hostname, int hops_max, int attempts_number)
{
    int sockfd;
    int success;
    int current_type = -1;
    icmp4_packet packet;
    struct sockaddr_in address;
    socklen_t address_size = sizeof (struct sockaddr_in);

    success = create_raw_socket(AF_INET, SOCK_RAW, IPPROTO_ICMP, &sockfd);
    if (success == 0)
        success = get_ipv4(hostname, IPPROTO_ICMP, &address);
    if (success == 0)
        success = icmp4_packet_init(&packet, extract_ipv4(&address));
    printf("traceroute to ");
    print_host_v4(address.sin_addr);
    printf(", %d hops max\n", hops_max);

    if (success == 0)
        for (int ttl = 1; current_type != ICMP_ECHOREPLY && ttl <= hops_max; ttl++)
        {
            int printed = 1;
            struct timeval times[attempts_number];
            memset(times, 0, attempts_number * sizeof (struct timeval));

            printf("%d", ttl);
            icmp4_packet_set_ttl(&packet, ttl);
            for (int attempt = 0; attempt < attempts_number; attempt++)
                if (sendto(sockfd, &packet, sizeof packet, 0, (struct sockaddr *) &address, address_size) == sizeof packet)
                {
                    struct sockaddr_in source;
                    current_type = traceroute_receive_icmp_v4(sockfd, &address, &source, &times[attempt]);
                    if (current_type != -1 && printed == 1)
                    {
                        printf(" ");
                        print_host_v4(source.sin_addr);
                        printed = 0;
                    }
                }
            print_times(times, attempts_number);
        }

    return success;
}
