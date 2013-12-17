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

int receive_icmp_v4(int sockfd, int ttl, struct sockaddr_in * address)
{
    int gotten = -1;
    fd_set socket_set;
    struct timeval wait_time = { 1, 0 };
    socklen_t address_size = sizeof (struct sockaddr_in);

    FD_ZERO(&socket_set);
    FD_SET(sockfd, &socket_set);
    if (select(sockfd + 1, &socket_set, NULL, NULL, &wait_time) != -1)
    {
        if (FD_ISSET(sockfd, &socket_set))
        {
            icmp4_packet received;
            if (recvfrom(sockfd, &received, sizeof received, 0, (struct sockaddr *) address, &address_size) != -1)
            {
                gotten = received.icmp_header.type;
                struct in_addr in = { received.ip_header.saddr };
                struct sockaddr_in s = { AF_INET, 0, in, { 0 } };
                char buf[256];
                getnameinfo((struct sockaddr *)&s, sizeof s, buf, 256, NULL, 0, 0);
                printf("%d: %s %s\n", ttl, buf, inet_ntoa(in));
            }
        }
    }

    return gotten;
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

    for (int i = 1; stop != 0 && i < 60; i++)
    {
        icmp4_packet_set_ttl(&packet, i);
        sendto(sockfd, &packet, sizeof packet, 0, (struct sockaddr *) &address, address_size);
        int current = receive_icmp_v4(sockfd, i, &address);
        if (current == ICMP_ECHOREPLY)
            stop = 0;
    }

    return success;
}
