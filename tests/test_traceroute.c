#include "address.h"
#include "packet.h"
#include "traceroute.h"

int main(int argc, char ** argv)
{
    if (argc !=2)
        return 64;

    int success = -1;
    struct sockaddr address;
    if (get_ipv6(argv[1], IPPROTO_ICMP, (struct sockaddr_in6 *) &address) == 0)
    {
        success = traceroute_icmp_v6(argv[1], 64, 3);
    }
    else
    {
        struct timeval wait_time = { 1, 0 };
        success = traceroute_icmp_v4(argv[1], 64, 3, 64, &wait_time);
    }

    return success;
}
