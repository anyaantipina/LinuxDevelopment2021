#include <check.h>
#include "buf.h"

float *a = 0;

#suite tests
#test init
	ck_assert_int_eq(buf_capacity(a), 0);
	ck_assert_int_eq(buf_size(a), 0);

    buf_push(a, 1.3f);
    ck_assert_int_eq(buf_size(a), 1);
    ck_assert_int_eq(a[0], (float)1.3f);

#test clear_and_free
    buf_push(a, 1.3f);
    buf_clear(a);
    ck_assert_int_eq(buf_size(a), 0);
    ck_assert_ptr_ne(a, NULL);
    buf_free(a);
    ck_assert_ptr_eq(a, NULL);
    buf_clear(a);
    ck_assert_int_eq(buf_size(a), 0);
    ck_assert_ptr_eq(a, NULL);

#test buf_push_and_element_access_operatiion
    long *ai = 0;
    for (int i = 0; i < 10000; i++)
        buf_push(ai, i);
	ck_assert_int_eq(buf_size(ai), 10000);
    int match = 0;
    for (int i = 0; i < (int)(buf_size(ai)); i++)
        match += ai[i] == i;
	ck_assert_int_eq((int)match, 10000);

#test buf_pop_test
    buf_push(a, 1.1);
    buf_push(a, 1.2);
    buf_push(a, 1.3);
    buf_push(a, 1.4);
	ck_assert_int_eq(buf_size(a), 4);
    ck_assert_int_eq(buf_pop(a), (float)1.4f);
    buf_trunc(a, 3);
	ck_assert_int_eq(buf_size(a), 3);
    ck_assert_int_eq(buf_pop(a), (float)1.3f);
    ck_assert_int_eq(buf_pop(a), (float)1.2f);
    ck_assert_int_eq(buf_pop(a), (float)1.1f);
	ck_assert_int_eq(buf_size(a), 0);
    buf_free(a);