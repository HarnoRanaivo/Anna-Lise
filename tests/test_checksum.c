#include "test_checksum.h"

void test_checksum(void)
{
    /* Exemple Wikipédia
     * https://en.wikipedia.org/wiki/IPv4_header_checksum
     */
    unsigned short header[10];
    header[0] = 0x4500;
    header[1] = 0x0073;
    header[2] = 0x0000;
    header[3] = 0x4000;
    header[4] = 0x4011;
    header[5] = 0x0000;
    header[6] = 0xc0a8;
    header[7] = 0x0001;
    header[8] = 0xc0a8;
    header[9] = 0x00c7;

    CU_ASSERT_EQUAL(checksum(header, 10), 0xb861);

}
