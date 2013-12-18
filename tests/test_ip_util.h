#ifndef __TEST_IP_UTIL_H
#define __TEST_IP_UTIL_H

#include <CUnit/CUnit.h>
#include <netinet/ip.h>

#include "CUnit_util.h"
#include "ip_util.h"

void test_iphdr_set_version(void);
void test_iphdr_set_header_length(void);
void test_iphdr_set_type_of_service(void);
void test_iphdr_set_total_length(void);
void test_iphdr_set_id(void);
void test_iphdr_set_flags(void);
void test_iphdr_set_fragment_offset(void);
void test_iphdr_set_ttl(void);
void test_iphdr_set_protocol(void);
void test_iphdr_checksum(void);
void test_iphdr_set_source_address(void);
void test_iphdr_set_dest_address(void);

#endif /* __TEST_IP_UTIL_H */
