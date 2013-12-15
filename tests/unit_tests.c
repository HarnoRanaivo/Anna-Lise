#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <CUnit/Console.h>

#include "test_base.h"
#include "test_icmp_util.h"
#include "test_ip_util.h"
#include "test_checksum.h"

/* Infos des suites de tests. */
CU_TestInfo test_base_info[] =
{
    { "Test check_pointer", test_check_pointer },
    { "Test uint_in_array", test_uint_in_array },
    CU_TEST_INFO_NULL,
};

CU_TestInfo test_icmp_util_info[] =
{
    { "Test icmp_set_type", test_icmp_set_type },
    { "Test icmp_set_code", test_icmp_set_code },
    { "Test icmp_set_echo", test_icmp_set_echo },
    CU_TEST_INFO_NULL,
};

CU_TestInfo test_ip_util_info[] =
{
    { "Test iphdr_set_version", test_iphdr_set_version },
    { "Test iphdr_set_header_length", test_iphdr_set_header_length },
    { "Test iphdr_set_type_of_service", test_iphdr_set_type_of_service },
    { "Test iphdr_set_total_length", test_iphdr_set_total_length },
    { "Test iphdr_set_id", test_iphdr_set_id },
    { "Test iphdr_set_flags", test_iphdr_set_flags },
    { "Test iphdr_set_fragment_offset", test_iphdr_set_fragment_offset },
    { "Test iphdr_set_ttl", test_iphdr_set_ttl },
    { "Test iphdr_set_protocol", test_iphdr_set_protocol },
    { "Test iphdr_checksum", test_iphdr_checksum },
    { "Test iphdr_set_source_address", test_iphdr_set_source_address },
    { "Test iphdr_set_dest_address", test_iphdr_set_dest_address },
    CU_TEST_INFO_NULL,
};

CU_TestInfo test_checksum_info[] =
{
    { "Test checksum", test_checksum },
    CU_TEST_INFO_NULL,
};


/* Liste des suites de tests */
CU_SuiteInfo suites[] =
{
    { "Test base.h", do_nothing, do_nothing, test_base_info },
    { "Test icmp_util.h", do_nothing, do_nothing, test_icmp_util_info },
    { "Test ip_util.h", do_nothing, do_nothing, test_ip_util_info },
    { "Test checksum.h", do_nothing, do_nothing, test_checksum_info },
    CU_SUITE_INFO_NULL,
};

int main(int argc, char ** argv)
{
    if (CU_initialize_registry() != CUE_SUCCESS)
        return CU_get_error();

    CU_ErrorCode error = CU_register_suites(suites);

    if (error == CUE_SUCCESS)
    {
        if (argc == 1)
        {
            CU_basic_set_mode(CU_BRM_VERBOSE);
            CU_basic_run_tests();
        }
        else if (strcmp("--interactive", argv[1]) == 0)
        {
            CU_console_run_tests();
        }
    }

    CU_cleanup_registry();

    return CU_get_error();
}
