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
