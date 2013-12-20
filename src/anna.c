#include "anna.h"

int fin_des_temps = 1;

static void handler_int (int signum)
{
    if (signum == SIGINT)
    {
        fin_des_temps = 0;
        printf("\n");
    }
}

static inline void set_handler(void)
{
    struct sigaction sa;
    sa.sa_handler = handler_int;
    sigfillset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT,&sa,NULL);
}

static inline void print_ping_statistics(int sent, int gotten, long double min, long double max, long double sum, struct timeval total, struct sockaddr_in * address)
{
    printf("--- ");
    print_host_v4(address);
    printf(" ping statistics ---\n");
    printf("%d packets transmitted, %d received, %.0f%% paquet loss, time %.0Lfms\n", sent, gotten, ((float) (sent - gotten) / sent) * 100, extract_time(total));
    printf("rtt min/avg/max = %.3Lf/%.3Lf/%.3Lf\n", min, sum / gotten, max);


}

static inline void update_statistics(long double * min, long double * max, long double * sum, long double rtt, int gotten, int before)
{
    if (gotten == 1 && before != gotten)
    {
        *min = rtt;
        *max = rtt;
    }
    if (rtt < *min)
        *min = rtt;
    if (rtt > *max)
        *max = rtt;
    *sum += rtt;
}

static inline void print_received(icmp4_packet * received, struct sockaddr_in * address, long double rtt)
{
    printf("%lu bytes from ", sizeof *received);
    print_host_v4(address);
    printf(": icmp_seq=%d ttl=%d time=%.2Lf ms\n",
        received->icmp_header.un.echo.sequence, received->ip_header.ttl, rtt);
}

static inline int ping_v4(const char * hostname)
{
    int sockfd;
    struct sockaddr_in address;
    icmp4_packet packet;

    int success = get_ipv4(hostname, IPPROTO_ICMP, &address);
    printf("ping ");
    print_host_v4(&address);
    printf("\n");
    succeed_or_die(success, 0, create_raw_socket(AF_INET, SOCK_RAW, IPPROTO_ICMP, &sockfd));
    succeed_or_die(success, 0, icmp4_packet_init(&packet, extract_ipv4(&address)));
    succeed_or_die(success, 0, icmp4_packet_set_length(&packet, sizeof packet));

    int sent = 0;
    int i = 0;
    int gotten = 0;
    struct timeval wait_time = { 1, 0 };
    long double min = 0.;
    long double max = 0.;
    long double sum = .0;
    struct timeval ping_start = { 0, 0 };
    struct timeval ping_end = { 0, 0 };
    gettimeofday(&ping_start, NULL);
    while (success == 0 && fin_des_temps == 1)
    {
        struct timeval start = { 0, 0 };
        struct timeval end = { 0, 0 };

        succeed_or_die(success, 0, icmp4_packet_set_echo_seq(&packet, i));
        gettimeofday(&start, NULL);
        if (sendto(sockfd, &packet, sizeof packet, 0, (struct sockaddr *) &address, sizeof address) == sizeof packet)
        {
            sent++;
            icmp4_packet received;
            memset(&received, 0, sizeof received);
            int before = gotten;
            if (receive_icmp_v4(sockfd, &address, &wait_time, &received) == 0)
            {
                if (received.icmp_header.type == ICMP_ECHOREPLY
                    && received.icmp_header.un.echo.sequence == i
                    && received.icmp_header.un.echo.id == packet.icmp_header.un.echo.id
                    )
                {
                    gotten++;
                    gettimeofday(&end, NULL);
                    struct timeval diff = diff_timeval(start, end);
                    long double rtt = extract_time(diff);
                    update_statistics(&min, &max, &sum, rtt, gotten, before);
                    print_received(&received, &address, rtt);

                    if (rtt > sum / gotten * 2 || rtt < sum / gotten / 2)
                        success = -1;
                }
            }
            if ((float) gotten / sent < 0.7)
                success = -1;
        }
        i++;
        sleep(1);
    }
    gettimeofday(&ping_end, NULL);
    struct timeval total = diff_timeval(ping_start, ping_end);
    print_ping_statistics(sent, gotten, min, max, sum, total, &address);

    return success;

}

int anna(const char * hostname)
{
    int success;
    struct sockaddr_in address;
    struct timeval wait_time = { 1, 0 };

    succeed_or_die(success, 0, get_ipv4(hostname, IPPROTO_ICMP, &address));

    int sockfd;
    succeed_or_die(success, 0, create_raw_socket(AF_INET, SOCK_RAW, IPPROTO_ICMP, &sockfd));

    set_handler();

    int i;
    for (i = 0; fin_des_temps == 1; i++)
    {
        printf("Discovering new route:\n");
        printf("----------------------\n");
        succeed_or_die(success, 0, traceroute_icmp_v4(hostname, 64, 3, 64, &wait_time));
        printf("\n");
        printf("Pinging:\n");
        printf("--------\n");
        ping_v4(hostname);
        printf("\n");
    }
    printf("traceroute and pinging done %d time(s).\n", i);

    close(sockfd);

    return success;
}
