#include "address.h"
#include "packet.h"

int main(int argc, char ** argv)
{
    if (argc !=2)
        return 64;

    int sockfd;
    struct sockaddr address;
    icmp4_packet packet;

    int success = socket_host_v4(argv[1], IPPROTO_ICMP, SOCK_RAW, &sockfd, &address);

    if (success == 0)
    {
        printf("socket_host ok\n");
        struct sockaddr_in * dest = (struct sockaddr_in *) &address;
        success = icmp4_packet_init(&packet, dest->sin_addr.s_addr);
        printf("%d, %s\n", dest->sin_port, inet_ntoa(dest->sin_addr));
        struct in_addr addr;
        addr.s_addr = packet.ip_header.saddr;
        printf("%s\n", inet_ntoa(addr));
        addr.s_addr = packet.ip_header.daddr;
        printf("%s\n", inet_ntoa(addr));
    }

    success = setsockopt(sockfd, IPPROTO_IP, IP_HDRINCL, NULL, 0);
    socklen_t address_size = sizeof (struct sockaddr_in);
    if (success == 0)
    {
        printf("init ok\n");
        if (sendto(sockfd, &packet, sizeof packet, 0, &address, address_size) < 0)
            success = -1;
    }

    if (success == 0)
    {
        printf("sendto ok\n");
        fd_set socket_set;
        FD_ZERO(&socket_set);
        FD_SET(sockfd, &socket_set);
        if (select(sockfd + 1, &socket_set, NULL, NULL, NULL) != -1)
        {
            if (FD_ISSET(sockfd, &socket_set))
            {
                icmp4_packet received;
                if (recvfrom(sockfd, &received, sizeof received, 0, &address, &address_size) == -1)
                    success = -1;
                if (success == 0 && received.ip_header.ihl == 5)
                {
                    printf("%d %d\n", received.icmp_header.type, received.icmp_header.code);
                }
            }
        }
        else
            success = -1;
    }

    return success;
}
