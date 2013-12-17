#include "address.h"
#include "packet.h"

static inline void print_packet_addresses(const icmp4_packet * packet)
{
    struct in_addr saddr = { packet->ip_header.saddr };
    struct in_addr daddr = { packet->ip_header.daddr };
    printf("packet source: %s\n", inet_ntoa(saddr));
    printf("packet dest: %s\n", inet_ntoa(daddr));
}

int main(int argc, char ** argv)
{
    if (argc !=2)
        return 64;

    int sockfd;
    struct sockaddr address;
    socklen_t address_size = sizeof (struct sockaddr_in);
    icmp4_packet packet;

    int success = socket_host_v4(argv[1], IPPROTO_ICMP, SOCK_RAW, &sockfd, &address);
    if (success == 0)
    {
        printf("socket_host ok\n");
        struct sockaddr_in * dest = (struct sockaddr_in *) &address;

        success = icmp4_packet_init(&packet, dest->sin_addr.s_addr);
    }

    int optval;
    success = setsockopt(sockfd, IPPROTO_IP, IP_HDRINCL, &optval, sizeof optval);
    if (success == 0)
    {
        printf("init ok\n");
        print_packet_addresses(&packet);
        if (sendto(sockfd, &packet, sizeof packet, 0, &address, address_size) < 0)
            success = -1;
    }

    if (success == 0)
    {
        printf("sendto ok\n");
        fd_set socket_set;
        struct timeval wait_time = { 1, 0 };

        FD_ZERO(&socket_set);
        FD_SET(sockfd, &socket_set);
        if (select(sockfd + 1, &socket_set, NULL, NULL, &wait_time) != -1)
        {
            printf("select ok\n");
            if (FD_ISSET(sockfd, &socket_set))
            {
                icmp4_packet received;
                if (recvfrom(sockfd, &received, sizeof received, 0, &address, &address_size) == -1)
                    success = -1;
                if (success == 0 && received.ip_header.ihl == 5)
                {
                    printf("recvfrom ok\n");
                    printf("ICMP type: %d, ICMP code: %d\n", received.icmp_header.type, received.icmp_header.code);
                }
            }
        }
        else
            success = -1;
    }

    return success;
}
