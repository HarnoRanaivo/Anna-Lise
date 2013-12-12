#ifndef __TEST_ICMP_UTIL_H
#define __TEST_ICMP_UTIL_H

#include <CUnit/CUnit.h>
#include <netinet/ip_icmp.h>

#include "CUnit_util.h"
#include "icmp_util.h"

void test_icmp_set_type(void);

void test_icmp_set_code(void);

void test_icmp_set_echo(void);

#endif /* __TEST_ICMP_UTIL_H */
