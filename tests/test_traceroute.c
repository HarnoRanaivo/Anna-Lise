#include <stdlib.h>
#include <stdio.h>
#include <sysexits.h>

#include "address.h"
#include "packet.h"
#include "traceroute.h"

int main(int argc, char ** argv)
{
    if (argc !=2)
    {
        fprintf(stderr, "Usage: %s <hostname | address>\n", argv[0]);
        exit(EX_USAGE);
    }

    if (getuid() != 0)
    {
        fprintf(stderr, "You need root rights.\n");
        exit(EX_NOPERM);
    }

    int success = -1;
    int enable_ipv6 = 1;
    int enable_udp = 0;

    struct sockaddr address;
    if (enable_udp == 0)
    {
        printf("traceroute IPv4 + UDP.\n");
        success = traceroute_udp_v4(argv[1], 64, 3);
    }
    else if (enable_ipv6 == 0 && get_ipv6(argv[1], IPPROTO_ICMPV6, (struct sockaddr_in6 *) &address) == 0)
    {
        printf("traceroute IPv6 + ICMP.\n");
        success = traceroute_icmp_v6(argv[1], 64, 3);
    }
    else
    {
        printf("traceroute IPv4 + ICMP.\n");
        struct timeval wait_time = { 1, 0 };
        success = traceroute_icmp_v4(argv[1], 64, 3, 64, &wait_time);
    }

    return success;
}
