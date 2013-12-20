#include "test_ip_util.h"

void test_iphdr_set_version(void)
{
    struct iphdr header;

    CU_ASSERT_EQUAL(iphdr_set_version(NULL), -1);
    CU_ASSERT_EQUAL(iphdr_set_version(&header), 0);
}

void test_iphdr_set_header_length(void)
{
    struct iphdr header_1;
    struct iphdr header_2;
    struct iphdr header_3;
    struct iphdr header_4;

    header_1.version = 0;
    iphdr_set_version(&header_2);
    iphdr_set_version(&header_3);
    iphdr_set_version(&header_4);

    CU_ASSERT_EQUAL(iphdr_set_header_length(NULL, 2), -1);
    CU_ASSERT_EQUAL(iphdr_set_header_length(NULL, 5), -1);
    CU_ASSERT_EQUAL(iphdr_set_header_length(NULL, 8), -1);
    CU_ASSERT_EQUAL(iphdr_set_header_length(NULL, 15), -1);
    CU_ASSERT_EQUAL(iphdr_set_header_length(NULL, 16), -1);

    CU_ASSERT_EQUAL(iphdr_set_header_length(&header_1, 2), -2);
    CU_ASSERT_EQUAL(iphdr_set_header_length(&header_1, 5), -2);
    CU_ASSERT_EQUAL(iphdr_set_header_length(&header_1, 8), -2);
    CU_ASSERT_EQUAL(iphdr_set_header_length(&header_1, 15), -2);
    CU_ASSERT_EQUAL(iphdr_set_header_length(&header_1, 16), -2);

    CU_ASSERT_EQUAL(iphdr_set_header_length(&header_2, 4), -3);
    CU_ASSERT_EQUAL(iphdr_set_header_length(&header_3, 16), -3);

    CU_ASSERT_EQUAL(iphdr_set_header_length(&header_4, 5), 0);
    CU_ASSERT_EQUAL(iphdr_set_header_length(&header_4, 15), 0);
}

void test_iphdr_set_type_of_service(void)
{
    struct iphdr header_1;
    struct iphdr header_2;

    header_1.version = 0;
    iphdr_set_version(&header_2);

    CU_ASSERT_EQUAL(iphdr_set_type_of_service(NULL, 1), -1);
    CU_ASSERT_EQUAL(iphdr_set_type_of_service(&header_1, 1), -2);
    CU_ASSERT_EQUAL(iphdr_set_type_of_service(&header_2, 1), 0);
}

void test_iphdr_set_total_length(void)
{
    struct iphdr header_1;
    struct iphdr header_2;

    header_1.version = 0;
    iphdr_set_version(&header_2);

    CU_ASSERT_EQUAL(iphdr_set_total_length(NULL, 2), -1);
    CU_ASSERT_EQUAL(iphdr_set_total_length(NULL, 5), -1);
    CU_ASSERT_EQUAL(iphdr_set_total_length(NULL, 8), -1);
    CU_ASSERT_EQUAL(iphdr_set_total_length(NULL, 15), -1);
    CU_ASSERT_EQUAL(iphdr_set_total_length(NULL, 16), -1);
    CU_ASSERT_EQUAL(iphdr_set_total_length(&header_1, 2), -2);
    CU_ASSERT_EQUAL(iphdr_set_total_length(&header_1, 5), -2);
    CU_ASSERT_EQUAL(iphdr_set_total_length(&header_1, 8), -2);
    CU_ASSERT_EQUAL(iphdr_set_total_length(&header_1, 15), -2);
    CU_ASSERT_EQUAL(iphdr_set_total_length(&header_1, 16), -2);

    CU_ASSERT_EQUAL(iphdr_set_total_length(&header_2, 19), -3);
    CU_ASSERT_EQUAL(iphdr_set_total_length(&header_2, 20), 0);
    CU_ASSERT_EQUAL(iphdr_set_total_length(&header_2, IP_MAXPACKET), 0);
}

void test_iphdr_set_id(void)
{
    struct iphdr header_1;
    struct iphdr header_2;

    header_1.version = 0;
    iphdr_set_version(&header_2);

    CU_ASSERT_EQUAL(iphdr_set_id(NULL, 1), -1);
    CU_ASSERT_EQUAL(iphdr_set_id(&header_1, 1), -2);
    CU_ASSERT_EQUAL(iphdr_set_id(&header_2, 1), 0);
}

void test_iphdr_set_flags(void)
{
    struct iphdr header_1;
    struct iphdr header_2;

    header_1.version = 0;
    iphdr_set_version(&header_2);

    CU_ASSERT_EQUAL(iphdr_set_flags(NULL, 0), -1);
    CU_ASSERT_EQUAL(iphdr_set_flags(&header_1, 0), -2);
    CU_ASSERT_EQUAL(iphdr_set_flags(&header_2, 0), 0);
}

void test_iphdr_set_fragment_offset(void)
{
    struct iphdr header_1;
    struct iphdr header_2;

    header_1.version = 0;
    iphdr_set_version(&header_2);

    CU_ASSERT_EQUAL(iphdr_set_fragment_offset(NULL, 0), -1);
    CU_ASSERT_EQUAL(iphdr_set_fragment_offset(&header_1, 0), -2);
    CU_ASSERT_EQUAL(iphdr_set_fragment_offset(&header_2, 0), 0);
}

void test_iphdr_set_ttl(void)
{
    struct iphdr header_1;
    struct iphdr header_2;

    header_1.version = 0;
    iphdr_set_version(&header_2);

    CU_ASSERT_EQUAL(iphdr_set_ttl(NULL, 2), -1);
    CU_ASSERT_EQUAL(iphdr_set_ttl(NULL, 5), -1);
    CU_ASSERT_EQUAL(iphdr_set_ttl(NULL, 8), -1);
    CU_ASSERT_EQUAL(iphdr_set_ttl(NULL, 15), -1);
    CU_ASSERT_EQUAL(iphdr_set_ttl(NULL, 16), -1);
    CU_ASSERT_EQUAL(iphdr_set_ttl(&header_1, 2), -2);
    CU_ASSERT_EQUAL(iphdr_set_ttl(&header_1, 5), -2);
    CU_ASSERT_EQUAL(iphdr_set_ttl(&header_1, 8), -2);
    CU_ASSERT_EQUAL(iphdr_set_ttl(&header_1, 15), -2);
    CU_ASSERT_EQUAL(iphdr_set_ttl(&header_1, 16), -2);

    CU_ASSERT_EQUAL(iphdr_set_ttl(&header_2, 0), -3);
    CU_ASSERT_EQUAL(iphdr_set_ttl(&header_2, 20), 0);
    CU_ASSERT_EQUAL(iphdr_set_ttl(&header_2, MAXTTL), 0);
}

void test_iphdr_set_protocol(void)
{
    struct iphdr header_1;
    struct iphdr header_2;

    header_1.version = 0;
    iphdr_set_version(&header_2);

    CU_ASSERT_EQUAL(iphdr_set_protocol(NULL, 0), -1);
    CU_ASSERT_EQUAL(iphdr_set_protocol(&header_1, 0), -2);
    CU_ASSERT_EQUAL(iphdr_set_protocol(&header_2, 0), 0);
}

void test_iphdr_checksum(void)
{
    struct iphdr header_1;
    struct iphdr header_2;

    header_1.version = 0;
    iphdr_set_version(&header_2);

    CU_ASSERT_EQUAL(iphdr_checksum(NULL), -1);
    CU_ASSERT_EQUAL(iphdr_checksum(&header_1), -2);
    CU_ASSERT_EQUAL(iphdr_checksum(&header_2), 0);
}

void test_iphdr_set_source_address(void)
{
    struct iphdr header_1;
    struct iphdr header_2;

    header_1.version = 0;
    iphdr_set_version(&header_2);

    CU_ASSERT_EQUAL(iphdr_set_source_address(NULL, 0), -1);
    CU_ASSERT_EQUAL(iphdr_set_source_address(&header_1, 0), -2);
    CU_ASSERT_EQUAL(iphdr_set_source_address(&header_2, 0), 0);
}

void test_iphdr_set_dest_address(void)
{
    struct iphdr header_1;
    struct iphdr header_2;

    header_1.version = 0;
    iphdr_set_version(&header_2);

    CU_ASSERT_EQUAL(iphdr_set_dest_address(NULL, 0), -1);
    CU_ASSERT_EQUAL(iphdr_set_dest_address(&header_1, 0), -2);
    CU_ASSERT_EQUAL(iphdr_set_dest_address(&header_2, 0), 0);
}

void test_ip6_hdr_set_version(void)
{
    ip6_hdr header;
    header.ip6_ctlun.ip6_un1.ip6_un1_flow = 0;

    CU_ASSERT_EQUAL(ip6_hdr_set_version(NULL), -1);
    CU_ASSERT_EQUAL(ip6_hdr_set_version(&header), 0);
}

void test_ip6_hdr_set_traffic_class(void)
{
    ip6_hdr header_1;
    ip6_hdr header_2;
    header_1.ip6_ctlun.ip6_un1.ip6_un1_flow = 0;
    ip6_hdr_set_version(&header_2);

    CU_ASSERT_EQUAL(ip6_hdr_set_traffic_class(NULL, 0), -1);
    CU_ASSERT_EQUAL(ip6_hdr_set_traffic_class(&header_1, 0), -2);
    CU_ASSERT_EQUAL(ip6_hdr_set_traffic_class(&header_2, 0), 0);
}

void test_ip6_hdr_set_flow_label(void)
{
    ip6_hdr header_1;
    ip6_hdr header_2;
    header_1.ip6_ctlun.ip6_un1.ip6_un1_flow = 0;
    ip6_hdr_set_version(&header_2);

    CU_ASSERT_EQUAL(ip6_hdr_set_flow_label(NULL, 0), -1);
    CU_ASSERT_EQUAL(ip6_hdr_set_flow_label(&header_1, 0), -2);
    CU_ASSERT_EQUAL(ip6_hdr_set_flow_label(&header_2, 0), 0);
}

void test_ip6_hdr_set_payload_length(void)
{
    ip6_hdr header_1;
    ip6_hdr header_2;
    header_1.ip6_ctlun.ip6_un1.ip6_un1_flow = 0;
    ip6_hdr_set_version(&header_2);

    CU_ASSERT_EQUAL(ip6_hdr_set_payload_length(NULL, 0), -1);
    CU_ASSERT_EQUAL(ip6_hdr_set_payload_length(&header_1, 0), -2);
    CU_ASSERT_EQUAL(ip6_hdr_set_payload_length(&header_2, 0), 0);
}

void test_ip6_hdr_set_next_header(void)
{
    ip6_hdr header_1;
    ip6_hdr header_2;
    header_1.ip6_ctlun.ip6_un1.ip6_un1_flow = 0;
    ip6_hdr_set_version(&header_2);

    CU_ASSERT_EQUAL(ip6_hdr_set_next_header(NULL, 0), -1);
    CU_ASSERT_EQUAL(ip6_hdr_set_next_header(&header_1, 0), -2);
    CU_ASSERT_EQUAL(ip6_hdr_set_next_header(&header_2, 0), 0);
}

void test_ip6_hdr_set_hop_limit(void)
{
    ip6_hdr header_1;
    ip6_hdr header_2;
    header_1.ip6_ctlun.ip6_un1.ip6_un1_flow = 0;
    ip6_hdr_set_version(&header_2);

    CU_ASSERT_EQUAL(ip6_hdr_set_hop_limit(NULL, 0), -1);
    CU_ASSERT_EQUAL(ip6_hdr_set_hop_limit(&header_1, 0), -2);
    CU_ASSERT_EQUAL(ip6_hdr_set_hop_limit(&header_2, 0), 0);
}

void test_ip6_hdr_set_source(void)
{
    ip6_hdr header_1;
    ip6_hdr header_2;
    header_1.ip6_ctlun.ip6_un1.ip6_un1_flow = 0;
    ip6_hdr_set_version(&header_2);
    sockaddr_in6 address;

    CU_ASSERT_EQUAL(ip6_hdr_set_source(NULL, NULL), -1);
    CU_ASSERT_EQUAL(ip6_hdr_set_source(&header_1, NULL), -2);
    CU_ASSERT_EQUAL(ip6_hdr_set_source(&header_2, NULL), -1);
    CU_ASSERT_EQUAL(ip6_hdr_set_source(NULL, &address), -1);
    CU_ASSERT_EQUAL(ip6_hdr_set_source(&header_1, &address), -2);
    CU_ASSERT_EQUAL(ip6_hdr_set_source(&header_2, &address), 0);
}

void test_ip6_hdr_set_destination(void)
{
    ip6_hdr header_1;
    ip6_hdr header_2;
    header_1.ip6_ctlun.ip6_un1.ip6_un1_flow = 0;
    ip6_hdr_set_version(&header_2);
    sockaddr_in6 address;

    CU_ASSERT_EQUAL(ip6_hdr_set_destination(NULL, NULL), -1);
    CU_ASSERT_EQUAL(ip6_hdr_set_destination(&header_1, NULL), -2);
    CU_ASSERT_EQUAL(ip6_hdr_set_destination(&header_2, NULL), -1);
    CU_ASSERT_EQUAL(ip6_hdr_set_destination(NULL, &address), -1);
    CU_ASSERT_EQUAL(ip6_hdr_set_destination(&header_1, &address), -2);
    CU_ASSERT_EQUAL(ip6_hdr_set_destination(&header_2, &address), 0);
}

void test_fake_ip6_hdr_set_source(void)
{
    fake_ip6_hdr header;
    struct in6_addr address;

    CU_ASSERT_EQUAL(fake_ip6_hdr_set_source(NULL, NULL), -1);
    CU_ASSERT_EQUAL(fake_ip6_hdr_set_source(&header, NULL), -1);
    CU_ASSERT_EQUAL(fake_ip6_hdr_set_source(NULL, &address), -1);
    CU_ASSERT_EQUAL(fake_ip6_hdr_set_source(&header, &address), 0);
}

void test_fake_ip6_hdr_set_destination(void)
{
    fake_ip6_hdr header;
    struct in6_addr address;

    CU_ASSERT_EQUAL(fake_ip6_hdr_set_destination(NULL, NULL), -1);
    CU_ASSERT_EQUAL(fake_ip6_hdr_set_destination(&header, NULL), -1);
    CU_ASSERT_EQUAL(fake_ip6_hdr_set_destination(NULL, &address), -1);
    CU_ASSERT_EQUAL(fake_ip6_hdr_set_destination(&header, &address), 0);
}

void test_fake_ip6_hdr_set_length(void)
{
    fake_ip6_hdr header;

    CU_ASSERT_EQUAL(fake_ip6_hdr_set_length(NULL, 0), -1);
    CU_ASSERT_EQUAL(fake_ip6_hdr_set_length(&header, 0), 0);
}

void test_fake_ip6_hdr_set_zeros(void)
{
    fake_ip6_hdr header;

    CU_ASSERT_EQUAL(fake_ip6_hdr_set_zeros(NULL), -1);
    CU_ASSERT_EQUAL(fake_ip6_hdr_set_zeros(&header), 0);
}

void test_fake_ip6_hdr_set_next_header(void)
{
    fake_ip6_hdr header;

    CU_ASSERT_EQUAL(fake_ip6_hdr_set_next_header(NULL, 0), -1);
    CU_ASSERT_EQUAL(fake_ip6_hdr_set_next_header(&header, 0), 0);
}
