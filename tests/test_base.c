#include "test_base.h"

void test_check_pointer(void)
{
    int i = 0;
    int * j = NULL;
    int * h = &i;
    int * k = j;
    int ** l = &j;

    CU_ASSERT_EQUAL(check_pointer(NULL), -1);
    CU_ASSERT_EQUAL(check_pointer(&i), 0);
    CU_ASSERT_EQUAL(check_pointer(j), -1);
    CU_ASSERT_EQUAL(check_pointer(&j), 0);
    CU_ASSERT_EQUAL(check_pointer(h), 0);
    CU_ASSERT_EQUAL(check_pointer(&h), 0);
    CU_ASSERT_EQUAL(check_pointer(k), -1);
    CU_ASSERT_EQUAL(check_pointer(&k), 0);
    CU_ASSERT_EQUAL(check_pointer(l), 0);
    CU_ASSERT_EQUAL(check_pointer(&l), 0);
}

void test_uint_in_array(void)
{
    int array_1[] = { 0, 1, 2, 3, -1 };
    int array_2[] = { 42, 0, 13, 2, -1000 };
    int array_3[] = { 100, 101, 102, 103, 104, 105, -1 };

    /* /!\ array_{1, 2} de taille 5 */
    for (int i = 0; i < 4; i++)
    {
        CU_ASSERT_EQUAL(uint_in_array(array_1, array_1[i]), i);
        CU_ASSERT_EQUAL(uint_in_array(array_2, array_2[i]), i);
    }

    for (int i = 0; i < 6; i++)
    {
        CU_ASSERT_EQUAL(uint_in_array(array_1, array_3[i]), -1);
        CU_ASSERT_EQUAL(uint_in_array(array_2, array_3[i]), -1);
        CU_ASSERT_EQUAL(uint_in_array(array_3, array_3[i]), i);
    }
}
