#include <stdio.h>
#include <stdlib.h>

#include "manual_tests.h"
#include "address.h"

static const char * HOSTNAMES[] =
{
    "localhost",
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
    MT_title("Test address.[ch]");
    MT_section("IPv4");

    struct sockaddr_in address_buffer_4;
    /* get_source_ipv4(0, &address_buffer_4); */
    /* printf("\tlocalhost: %s\n", address_to_string(extract_ipv4(&address_buffer_4))); */
    for (int i = 0; HOSTNAMES[i] != NULL; i++)
    {
        const char * name = HOSTNAMES[i];

        get_ipv4(name, 0, &address_buffer_4);
        u_int32_t address = extract_ipv4(&address_buffer_4);
        printf("\t%s: %s\n", name, address_to_string(address));
    }
    if (argc != 1)
        for (int i = 1; i < argc; i++)
        {
            const char * name = argv[i];
            get_ipv4(name, 0, &address_buffer_4);
            u_int32_t address = extract_ipv4(&address_buffer_4);
            printf("\t%s: %s\n", name, address_to_string(address));
        }

    get_interface_ipv4(&address_buffer_4);
    printf("\tfirst valid interface: %s\n", address_to_string(extract_ipv4(&address_buffer_4)));
    get_source_ipv4(0, &address_buffer_4);
    printf("\tsource: ");
    print_ip(AF_INET, (struct sockaddr *) &address_buffer_4);
    printf("\tsource bis: %s\n", address_to_string(extract_ipv4(&address_buffer_4)));

    MT_section("IPv6");
    struct sockaddr_in6 address_buffer_6;
    for (int i = 0; HOSTNAMES[i] != NULL; i++)
    {
        const char * name = HOSTNAMES[i];
        get_ipv6(name, 9, &address_buffer_6);
        printf("\t%s: ", name);
        print_ip(AF_INET6, (struct sockaddr *) &address_buffer_6);
    }
    printf("\tsource: ");
    get_source_ipv6(0, &address_buffer_6);
    print_ip(AF_INET6, (struct sockaddr *) &address_buffer_6);

    return 0;
}
