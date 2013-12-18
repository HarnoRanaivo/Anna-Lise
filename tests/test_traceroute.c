#include "address.h"
#include "packet.h"
#include "traceroute.h"

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

    int success = traceroute_icmp_v4(argv[1], 64, 4);

    return success;
}
