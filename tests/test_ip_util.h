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
void test_ip6_hdr_set_version(void);
void test_ip6_hdr_set_traffic_class(void);
void test_ip6_hdr_set_flow_label(void);
void test_ip6_hdr_set_payload_length(void);
void test_ip6_hdr_set_next_header(void);
void test_ip6_hdr_set_hop_limit(void);
void test_ip6_hdr_set_source(void);
void test_ip6_hdr_set_destination(void);
void test_fake_ip6_hdr_set_source(void);
void test_fake_ip6_hdr_set_destination(void);
void test_fake_ip6_hdr_set_length(void);
void test_fake_ip6_hdr_set_zeros(void);
void test_fake_ip6_hdr_set_next_header(void);

#endif /* __TEST_IP_UTIL_H */
