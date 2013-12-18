#include "test_checksum.h"

void test_checksum(void)
{
    /* Exemple Wikipedia
     * https://en.wikipedia.org/wiki/IPv4_header_checksum
     */
    unsigned short header_1[10];
    unsigned short header_2[10];
    header_1[0] = header_2[0] = 0x4500;
    header_1[1] = header_2[1] = 0x0073;
    header_1[2] = header_2[2] = 0x0000;
    header_1[3] = header_2[3] = 0x4000;
    header_1[4] = header_2[4] = 0x4011;
    /* Checksum. Mis à 0 avant le calcul. */
    header_1[5] = header_2[5] = 0x0000;
    header_1[6] = header_2[6] = 0xc0a8;
    header_1[7] = header_2[7] = 0x0001;
    header_1[8] = header_2[8] = 0xc0a8;
    header_1[9] = header_2[9] = 0x00c7;
    unsigned short expected_checksum_1 = 0xb861;
    /* Pour la vérification. La checksum du header, avec checksum incluse
     * doit être 0.
     */
    header_2[5] = expected_checksum_1;

    /* Autre exemple Wikipedia
     * https://en.wikipedia.org/wiki/IPv4_header#Header_Checksum
     */
    unsigned short header_3[10];
    unsigned short header_4[10];
    header_3[0] = header_4[0] = 0x4500;
    header_3[1] = header_4[1] = 0x0030;
    header_3[2] = header_4[2] = 0x4422;
    header_3[3] = header_4[3] = 0x4000;
    header_3[4] = header_4[4] = 0x8006;
    header_3[5] = header_4[5] = 0x0000;
    header_3[6] = header_4[6] = 0x8c7c;
    header_3[7] = header_4[7] = 0x19ac;
    header_3[8] = header_4[8] = 0xae24;
    header_3[9] = header_4[9] = 0x1e2b;
    unsigned short expected_checksum_2 = 0x442e;
    header_4[5] = expected_checksum_2;


    CU_ASSERT_EQUAL(checksum(header_1, 10), expected_checksum_1);
    CU_ASSERT_EQUAL(checksum(header_2, 10), 0);

    CU_ASSERT_EQUAL(checksum(header_3, 10), expected_checksum_2);
    CU_ASSERT_EQUAL(checksum(header_4, 10), 0);


}
