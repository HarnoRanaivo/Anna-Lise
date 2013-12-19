#include "address.h"
#include "packet.h"
#include "traceroute.h"

int main(int argc, char ** argv)
{
    if (argc !=2)
        return 64;

    int success = traceroute_icmp_v4(argv[1], 64, 3);

    return success;
}
