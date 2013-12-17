#include "test_packet.h"

void test_icmp4_packet_init(void)
{
    icmp4_packet packet;

    CU_ASSERT_EQUAL(icmp4_packet_init(&packet, 0), 0);
    CU_ASSERT_NOT_EQUAL(icmp4_packet_init(NULL, 0), 0);

    CU_ASSERT_EQUAL(packet.ip_header.version, IPVERSION);
    CU_ASSERT_EQUAL(packet.ip_header.ihl, 5);
    CU_ASSERT_EQUAL(packet.ip_header.tos, 0);
    CU_ASSERT_EQUAL(packet.ip_header.tot_len, sizeof (icmp4_packet));
    CU_ASSERT_EQUAL(packet.ip_header.id, 0);
    CU_ASSERT_EQUAL(packet.ip_header.frag_off, 0);
    CU_ASSERT_EQUAL(packet.ip_header.ttl, IPDEFTTL);
    CU_ASSERT_EQUAL(packet.ip_header.protocol, 1);
    CU_ASSERT_EQUAL(packet.ip_header.saddr, get_source_ipv4(IPPROTO_ICMP));
    CU_ASSERT_EQUAL(packet.ip_header.daddr, 0);

    CU_ASSERT_EQUAL(packet.icmp_header.type, ICMP_ECHO);
    CU_ASSERT_EQUAL(packet.icmp_header.code, 0);
    CU_ASSERT_EQUAL(packet.icmp_header.un.echo.id, getpid());
    CU_ASSERT_EQUAL(packet.icmp_header.un.echo.sequence, 0);
}

void test_icmp4_packet_set_ttl(void)
{
    icmp4_packet packet_1;
    icmp4_packet packet_2;
    icmp4_packet packet_3;
    icmp4_packet packet_4;
    icmp4_packet_init(&packet_1, 0);
    icmp4_packet_init(&packet_2, 0);
    icmp4_packet_init(&packet_3, 0);
    icmp4_packet_init(&packet_4, 0);

    CU_ASSERT_NOT_EQUAL(icmp4_packet_set_ttl(NULL, 0), 0);
    CU_ASSERT_NOT_EQUAL(icmp4_packet_set_ttl(NULL, 1), 0);
    CU_ASSERT_NOT_EQUAL(icmp4_packet_set_ttl(NULL, IPDEFTTL), 0);
    CU_ASSERT_NOT_EQUAL(icmp4_packet_set_ttl(NULL, MAXTTL), 0);
    CU_ASSERT_NOT_EQUAL(icmp4_packet_set_ttl(&packet_1, 0), 0);
    CU_ASSERT_EQUAL(packet_1.ip_header.ttl, IPDEFTTL);
    CU_ASSERT_NOT_EQUAL(icmp4_packet_set_ttl(&packet_2, 0), 0);
    CU_ASSERT_EQUAL(packet_2.ip_header.ttl, IPDEFTTL);

    CU_ASSERT_EQUAL(icmp4_packet_set_ttl(&packet_3, 1), 0);
    CU_ASSERT_EQUAL(packet_3.ip_header.ttl, 1);

    CU_ASSERT_EQUAL(icmp4_packet_set_ttl(&packet_4, MAXTTL), 0);
    CU_ASSERT_EQUAL(packet_4.ip_header.ttl, MAXTTL);
}

void test_icmp4_packet_set_echo_seq(void)
{
    icmp4_packet packet;

    icmp4_packet_init(&packet, 0);
    CU_ASSERT_NOT_EQUAL(icmp4_packet_set_echo_seq(NULL, 0), 0);
    CU_ASSERT_EQUAL(icmp4_packet_set_echo_seq(&packet, 2), 0);
    CU_ASSERT_EQUAL(packet.icmp_header.un.echo.sequence, 2);
}
