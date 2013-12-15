#include "test_icmp_util.h"

static const unsigned int valid_types[] =
{
    ICMP_ECHOREPLY, ICMP_DEST_UNREACH, ICMP_SOURCE_QUENCH, ICMP_REDIRECT,
    ICMP_ECHO, ICMP_TIME_EXCEEDED, ICMP_PARAMETERPROB, ICMP_TIMESTAMP,
    ICMP_TIMESTAMPREPLY, ICMP_INFO_REQUEST, ICMP_INFO_REPLY, ICMP_ADDRESS,
    ICMP_ADDRESSREPLY,
};

static const unsigned int invalid_types[] = { 1, 2, 6, 7, 9, 10 };

void test_icmp_set_type(void)
{
    struct icmphdr header;

    for (int i = 0; i < 6; i++)
    {
        CU_ASSERT_EQUAL(icmp_set_type(&header, invalid_types[i]), -2);
        CU_ASSERT_EQUAL(icmp_set_type(NULL, invalid_types[i]), -3);
    }

    for (int i = 0; i <= NR_ICMP_TYPES - 6; i++)
    {
        CU_ASSERT_EQUAL(icmp_set_type(NULL, valid_types[i]), -1);
        CU_ASSERT_EQUAL(icmp_set_type(&header, valid_types[i]), 0);
        CU_ASSERT_EQUAL(header.type, valid_types[i]);
    }
}

void test_icmp_set_code(void)
{
    struct icmphdr header_1;
    struct icmphdr header_2;
    header_2.type = ICMP_ECHO;

    CU_ASSERT_EQUAL(icmp_set_code(NULL, 0), -1);
    CU_ASSERT_EQUAL(icmp_set_code(&header_1, 0), 0);
    CU_ASSERT_EQUAL(icmp_set_code(&header_2, 0), 0);
    CU_ASSERT_EQUAL(header_2.code, 0);
}

void test_icmp_set_echo(void)
{
    struct icmphdr header;

    for (int i = 0; i <= NR_ICMP_TYPES; i++)
    {
        int expected_return;
        header.type = i;
        if (i == ICMP_ECHO)
            expected_return = 0;
        else
            expected_return = -2;
        CU_ASSERT_EQUAL(icmp_set_echo(&header, 0, 0), expected_return);
    }

    CU_ASSERT_EQUAL(icmp_set_echo(NULL, 0, 0), -1);
}

void test_icmp_checksum(void)
{
    struct icmphdr header;

    CU_ASSERT_EQUAL(icmp_checksum(NULL), -1);
    CU_ASSERT_EQUAL(icmp_checksum(&header), 0);
}
