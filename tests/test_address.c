#include <stdio.h>
#include <stdlib.h>

#include "address.h"

static const char * HOSTNAMES[] =
{
    "google.com",
    "duckduckgo.com",
    NULL,
};

static inline char * address_to_string(u_int32_t address)
{
    struct in_addr in;
    in.s_addr = address;

    return inet_ntoa(in);
}

int main(int argc, char ** argv)
{
    printf("Test address.[ch]\n");
    printf("=================\n");
    printf("IPv4:\n");
    printf("-----\n");
    printf("\tlocalhost: %s\n", address_to_string(get_source_ipv4(0)));

    for (int i = 0; HOSTNAMES[i] != NULL; i++)
    {
        const char * name = HOSTNAMES[i];
        u_int32_t address = get_ipv4(name, 0);
        printf("\t%s: %s\n", name, address_to_string(address));
    }

    if (argc != 1)
        for (int i = 1; i < argc; i++)
        {
            const char * name = argv[i];
            u_int32_t address = get_ipv4(name, 0);
            printf("\t%s: %s\n", name, address_to_string(address));
        }

    printf("\n");
    printf("IPv6:\n");
    printf("-----\n");
    printf("TODO\n");

    return 0;
}
