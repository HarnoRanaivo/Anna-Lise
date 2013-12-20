#include "address.h"
#include "packet.h"
#include "traceroute.h"

int main(int argc, char ** argv)
{
    if (argc !=2)
        return 64;

    struct timeval wait_time = { 1, 0 };
    int success = traceroute_icmp_v4(argv[1], 64, 3, 64, &wait_time);

    return success;
}
