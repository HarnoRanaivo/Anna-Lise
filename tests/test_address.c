#include <stdio.h>
#include <stdlib.h>

#include "manual_tests.h"
#include "address.h"

static const char * HOSTNAMES[] =
{
    "localhost",
    "google.com",
    "duckduckgo.com",
    "facebook.com",
    NULL,
};

static inline char * address_to_string(u_int32_t address)
{
    struct in_addr in;
    in.s_addr = address;

    return inet_ntoa(in);
}

static inline void print_ip4(const char * name)
{
    struct sockaddr_in address_buffer;
    printf("\t%s: ", name);
    if (get_ipv4(name, 0, &address_buffer) == 0)
        print_ip(AF_INET, (struct sockaddr *) &address_buffer);
    else
        printf("None.\n");
}

static inline void print_ip6(const char * name)
{
    struct sockaddr_in6 address_buffer;
    printf("\t%s: ", name);
    if (get_ipv6(name, 0, &address_buffer) == 0)
        print_ip(AF_INET6, (struct sockaddr *) &address_buffer);
    else
        printf("None.\n");
}

int main(int argc, char ** argv)
{
    MT_title("Test address.[ch]");
    MT_section("IPv4");

    for (int i = 0; HOSTNAMES[i] != NULL; i++)
        print_ip4(HOSTNAMES[i]);
    if (argc != 1)
        for (int i = 1; i < argc; i++)
        {
            const char * name = argv[i];
            print_ip4(name);
        }

    struct sockaddr_in if_address_buffer;
    get_interface_ipv4(&if_address_buffer);
    printf("\tfirst valid interface: %s\n", address_to_string(extract_ipv4(&if_address_buffer)));
    struct sockaddr_in src_address_buffer;
    get_source_ipv4(0, &src_address_buffer);
    printf("\tsource: ");
    print_ip(AF_INET, (struct sockaddr *) &src_address_buffer);
    printf("\tsource bis: %s\n", address_to_string(extract_ipv4(&src_address_buffer)));

    MT_section("IPv6");
    for (int i = 0; HOSTNAMES[i] != NULL; i++)
    {
        const char * name = HOSTNAMES[i];
        print_ip6(name);
    }
    printf("\tsource: ");
    struct sockaddr_in6 src_address_buffer_6;
    get_source_ipv6(0, &src_address_buffer_6);
    print_ip(AF_INET6, (struct sockaddr *) &src_address_buffer_6);

    return 0;
}
