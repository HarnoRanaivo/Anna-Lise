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

int reverse_dns_v4(char * buffer, size_t buffer_size, struct in_addr address)
{
    struct sockaddr_in source = { AF_INET, 0, address, { 0 } };
    return getnameinfo((struct sockaddr *)&source, sizeof source, buffer, buffer_size, NULL, 0, 0);
}

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
        print_timeval(times[i]);
}

int traceroute_icmp_v4(const char * hostname)
{
    int sockfd;
    int success;
    int stop = 1;
    icmp4_packet packet;
    struct sockaddr_in address;
    socklen_t address_size = sizeof (struct sockaddr_in);

    success = create_raw_socket(AF_INET, SOCK_RAW, IPPROTO_ICMP, &sockfd);
    if (success == 0)
        success = get_ipv4(hostname, IPPROTO_ICMP, &address);
    if (success == 0)
        success = icmp4_packet_init(&packet, extract_ipv4(&address));

    for (int ttl = 1; stop != 0 && ttl <= 60; ttl++)
    {
        printf("%d", ttl);
        icmp4_packet_set_ttl(&packet, ttl);
        int printed = 1;

        int attempt_number = 3;
        struct timeval times[attempt_number];
        for (int attempt = 0; attempt < attempt_number; attempt++)
        {
            sendto(sockfd, &packet, sizeof packet, 0, (struct sockaddr *) &address, address_size);
            struct sockaddr_in source;
            int current = traceroute_receive_icmp_v4(sockfd, &address, &source, &times[attempt]);
            if (current != -1 && printed == 1)
            {
                size_t buffer_size = 256;
                char buffer[buffer_size];
                struct in_addr source_address = source.sin_addr;
                reverse_dns_v4(buffer, buffer_size, source_address);
                printf(" %s (%s)", buffer, inet_ntoa(source_address));
                printed = 0;
            }
            if (current == ICMP_ECHOREPLY)
                stop = 0;
        }
        print_times(times, attempt_number);
        printf("\n");
    }

    return success;
}
