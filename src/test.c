#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include "sfleta_decimal.h"

#define TRUE 0
#define FALSE 1

void test(sfleta_decimal test, unsigned orig_bits_0, unsigned orig_bits_1, unsigned orig_bits_2,
            unsigned orig_bits_3, unsigned orig_value_type) {
    ck_assert_uint_eq(test.bits[0], orig_bits_0);
    ck_assert_uint_eq(test.bits[1], orig_bits_1);
    ck_assert_uint_eq(test.bits[2], orig_bits_2);
    ck_assert_uint_eq(test.bits[3], orig_bits_3);
    ck_assert_uint_eq(test.value_type, orig_value_type);
}

START_TEST(add_test_1) {
    sfleta_decimal dec1 = {{0, 0, 0, 0}, 0};
    sfleta_decimal dec2 = {{0, 0, 0, 0}, 0};
    test(sfleta_add(dec1, dec2), 0, 0, 0, 0, 0);
} END_TEST

START_TEST(add_test_2) {
    sfleta_decimal dec1 = {{0, 0, 0, 0}, 0};
    sfleta_decimal dec2 = {{1, 0, 0, 0}, 0};
    test(sfleta_add(dec1, dec2), 1, 0, 0, 0, 0);
} END_TEST

START_TEST(add_test_3) {
    sfleta_decimal dec1 = {{3, 0, 0, 0}, 0};
    sfleta_setSign(&dec1, 1);
    sfleta_decimal dec2 = {{5, 0, 0, 0}, 0};
    test(sfleta_add(dec1, dec2), 2, 0, 0, 0, 0);
} END_TEST

START_TEST(add_test_4) {
    sfleta_decimal dec1 = {{20, 0, 0, 0}, 0};
    sfleta_decimal dec2 = {{15, 0, 0, 0}, 0};
    test(sfleta_add(dec1, dec2), 35, 0, 0, 0, 0);
} END_TEST

START_TEST(add_test_5) {
    sfleta_decimal dec1 = {{5, 0, 0, 0}, 0};
    sfleta_decimal dec2 = {{3, 0, 0, 0}, 0};
    sfleta_setSign(&dec2, 1);
    test(sfleta_add(dec1, dec2), 2, 0, 0, 0, 0);
} END_TEST

START_TEST(add_test_6) {
    sfleta_decimal dec1 = {{0, 0, 0, 0}, 0};
    sfleta_decimal dec2 = {{1, 2, 3, 4}, 1};
    test(sfleta_add(dec1, dec2), 0, 0, 0, 0, 1);
} END_TEST

START_TEST(add_test_7) {
    sfleta_decimal dec1 = {{0, 0, 0, 0}, 0};
    sfleta_decimal dec2 = {{1, 2, 3, 4}, 2};
    test(sfleta_add(dec1, dec2), 0, 0, 0, 0, 2);
} END_TEST

START_TEST(add_test_8) {
    sfleta_decimal dec1 = {{0, 0, 0, 0}, 0};
    sfleta_decimal dec2 = {{1, 2, 3, 4}, 3};
    test(sfleta_add(dec1, dec2), 0, 0, 0, 0, 3);
} END_TEST

START_TEST(add_test_9) {
    sfleta_decimal dec1 = {{1, 0, 0, 0}, 0};
    sfleta_decimal dec2 = {{1, 0, 0, 0}, 0};
    sfleta_setSign(&dec2, 1);
    test(sfleta_add(dec1, dec2), 0, 0, 0, 0, 0);
} END_TEST

START_TEST(add_test_10) {
    sfleta_decimal dec1 = {{1, 2, 3, 4}, 1};
    sfleta_decimal dec2 = {{1, 0, 0, 0}, 0};
    sfleta_setSign(&dec2, 1);
    test(sfleta_add(dec1, dec2), 0, 0, 0, 0, 1);
} END_TEST

START_TEST(add_test_11) {
    sfleta_decimal dec1 = {{1, 2, 3, 4}, 1};
    sfleta_decimal dec2 = {{1, 2, 3, 4}, 2};
    test(sfleta_add(dec1, dec2), 0, 0, 0, 0, 3);
} END_TEST

START_TEST(add_test_12) {
    sfleta_decimal dec1 = {{1, 2, 3, 4}, 1};
    sfleta_decimal dec2 = {{1, 2, 3, 4}, 3};
    test(sfleta_add(dec1, dec2), 0, 0, 0, 0, 3);
} END_TEST

START_TEST(add_test_13) {
    sfleta_decimal dec1 = {{1, 2, 3, 4}, 2};
    sfleta_decimal dec2 = {{1, 0, 0, 0}, 0};
    test(sfleta_add(dec1, dec2), 0, 0, 0, 0, 2);
} END_TEST

START_TEST(add_test_14) {
    sfleta_decimal dec1 = {{2, 0, 0, 0}, 0};
    sfleta_decimal dec2 = {{2, 0, 0, 0x80000000}, 0};
    test(sfleta_add(dec1, dec2), 0, 0, 0, 0, 0);
}
END_TEST

START_TEST(add_test_15) {
    sfleta_decimal dec1 = {{0xffffffff, 0xffffffff, 0xffffffff, 0}, 0};
    sfleta_decimal dec2 = {{1, 0, 0, 0}, 0};
    test(sfleta_add(dec1, dec2), 0, 0, 0, 0, 1);
}
END_TEST

START_TEST(add_test_16) {
    sfleta_decimal dec1 = {{0xffffffff, 0xffffffff, 0xffffffff, -2147483648}, 0};
    sfleta_decimal dec2 = {{1, 0, 0, 0}, 0};
    sfleta_setSign(&dec2, 1);
    test(sfleta_add(dec1, dec2), 0, 0, 0, 0, 2);
}
END_TEST

START_TEST(add_test_17) {
    sfleta_decimal dec1 = {{0xffffffff, 0x0, 0x0, 0x0}, 0x0};
    sfleta_decimal dec2 = {{1, 0, 0, 0}, 0};
    test(sfleta_add(dec1, dec2), 0, 1, 0, 0, 0);
}
END_TEST

START_TEST(add_test_18) {
    sfleta_decimal dec1 = {{0xffffffff, 0x0, 0x0, 0x0}, 0x0};
    sfleta_decimal dec2 = {{1, 1, 1, 0}, 0};
    test(sfleta_add(dec1, dec2), 0, 2, 1, 0, 0);
}
END_TEST

START_TEST(add_test_19) {
    sfleta_decimal dec1 = {{0xffffffff, 0x0, 0x0, 0x0}, 0x0};
    sfleta_decimal dec2 = {{1, 1, 1, 0}, 0};
    test(sfleta_add(dec1, dec2), 0, 2, 1, 0, 0);
}
END_TEST

START_TEST(add_test_20) {
    sfleta_decimal dec1 = {{0xffffffff, 0x0, 0x0, 0x0}, 0x0};
    sfleta_decimal dec2 = {{0xffffffff, 0x0, 0x0, 0x0}, 0x0};
    test(sfleta_add(dec1, dec2), 0xfffffffe, 1, 0, 0, 0);
}
END_TEST

START_TEST(sub_test_1) {
    sfleta_decimal dec1 = {{8, 0, 0, 0}, 0};
    sfleta_decimal dec2 = {{5, 0, 0, 0}, 0};
    test(sfleta_sub(dec1, dec2), 3, 0, 0, 0, 0);
} END_TEST

START_TEST(sub_test_2) {
    sfleta_decimal dec1 = {{8, 0, 0, 0}, 0};
    sfleta_setSign(&dec1, 1);
    sfleta_decimal dec2 = {{5, 0, 0, 0}, 0};
    sfleta_setSign(&dec2, 1);
    test(sfleta_sub(dec1, dec2), 3, 0, 0, -2147483648, 0);
} END_TEST

START_TEST(sub_test_3) {
    sfleta_decimal dec1 = {{3, 0, 0, 0}, 0};
    sfleta_setSign(&dec1, 1);
    sfleta_decimal dec2 = {{8, 0, 0, 0}, 0};
    sfleta_setSign(&dec2, 1);
    test(sfleta_sub(dec1, dec2), 5, 0, 0, 0, 0);
} END_TEST

START_TEST(sub_test_4) {
    sfleta_decimal dec1 = {{0, 0, 0, 0}, 0};
    sfleta_decimal dec2 = {{5, 0, 0, 0}, 0};
    test(sfleta_sub(dec1, dec2), 5, 0, 0, -2147483648, 0);
} END_TEST

START_TEST(sub_test_5) {
    sfleta_decimal dec1 = {{2, 0, 0, 0}, 0};
    sfleta_decimal dec2 = {{8, 0, 0, 0}, 0};
    sfleta_setSign(&dec2, 1);
    test(sfleta_sub(dec1, dec2), 10, 0, 0, 0, 0);
} END_TEST

START_TEST(sub_test_6) {
    sfleta_decimal dec1 = {{8, 0, 0, 0}, 0};
    sfleta_setSign(&dec1, 1);
    sfleta_decimal dec2 = {{2, 0, 0, 0}, 0};
    test(sfleta_sub(dec1, dec2), 10, 0, 0, -2147483648, 0);
} END_TEST

START_TEST(sub_test_7) {
    sfleta_decimal dec1 = {{1, 0, 0, 0}, 2};
    sfleta_decimal dec2 = {{1, 2, 3, 4}, 0};
    test(sfleta_sub(dec1, dec2), 0, 0, 0, 0, 2);
} END_TEST

START_TEST(sub_test_8) {
    sfleta_decimal dec1 = {{1, 0, 0, 0}, 0};
    sfleta_decimal dec2 = {{1, 2, 3, 4}, 3};
    test(sfleta_sub(dec1, dec2), 0, 0, 0, 0, 3);
} END_TEST

START_TEST(sub_test_9) {
    sfleta_decimal dec1 = {{1, 2, 3, 4}, 1};
    sfleta_decimal dec2 = {{1, 2, 3, 4}, 2};
    test(sfleta_sub(dec1, dec2), 0, 0, 0, 0, 1);
} END_TEST

START_TEST(sub_test_10) {
    sfleta_decimal dec1 = {{1, 2, 3, 4}, 2};
    sfleta_decimal dec2 = {{1, 2, 3, 4}, 3};
    test(sfleta_sub(dec1, dec2), 0, 0, 0, 0, 3);
} END_TEST

START_TEST(sub_test_11) {
    sfleta_decimal dec1 = {{0xffffffff, 0xffffffff, 0xffffffff, 0}, 0};
    sfleta_decimal dec2 = {{0xffffffff, 0xffffffff, 0xffffffff, 0}, 0};
    test(sfleta_sub(dec1, dec2), 0, 0, 0, 0, 0);
} END_TEST

START_TEST(sub_test_12) {
    sfleta_decimal dec1 = {{1, 2, 3, 4}, 3};
    sfleta_decimal dec2 = {{1, 2, 3, 4}, 3};
    test(sfleta_sub(dec1, dec2), 0, 0, 0, 0, 3);
} END_TEST

START_TEST(sub_test_13) {
    sfleta_decimal dec1 = {{1, 2, 3, 4}, 3};
    sfleta_decimal dec2 = {{1, 2, 3, 4}, 1};
    test(sfleta_sub(dec1, dec2), 0, 0, 0, 0, 3);
} END_TEST

START_TEST(sub_test_14) {
    sfleta_decimal dec1 = {{1, 2, 3, 4}, 2};
    sfleta_decimal dec2 = {{1, 2, 3, 4}, 2};
    test(sfleta_sub(dec1, dec2), 0, 0, 0, 0, 3);
} END_TEST

START_TEST(sub_test_15) {
    sfleta_decimal dec1 = {{1, 2, 3, 4}, 2};
    sfleta_decimal dec2 = {{1, 2, 3, 4}, 1};
    test(sfleta_sub(dec1, dec2), 0, 0, 0, 0, 2);
} END_TEST

START_TEST(mul_test_1) {
    sfleta_decimal dec1 = {{0, 0, 0, 0}, 0};
    sfleta_decimal dec2 = {{0, 0, 0, 0}, 0};
    test(sfleta_mul(dec1, dec2), 0, 0, 0, 0, 0);
}
END_TEST

START_TEST(mul_test_2) {
    sfleta_decimal dec1 = {{5, 0, 0, 0}, 0};
    sfleta_decimal dec2 = {{4, 0, 0, 0}, 0};
    sfleta_setSign(&dec2, 1);
    test(sfleta_mul(dec1, dec2), 20, 0, 0, -2147483648, 0);
}
END_TEST

START_TEST(mul_test_3) {
    sfleta_decimal dec1 = {{0, 0, 0, 0}, 0};
    sfleta_decimal dec2 = {{1, 2, 3, 4}, 1};
    test(sfleta_mul(dec1, dec2), 0, 0, 0, 0, 3);
}
END_TEST

START_TEST(mul_test_4) {
    sfleta_decimal dec1;
  // dec1 = 79228162514264337593543950335;
    dec1.value_type = sfleta_NORMAL_VALUE;
    dec1.bits[0] = 0b11111111111111111111111111111111;
    dec1.bits[1] = 0b11111111111111111111111111111111;
    dec1.bits[2] = 0b11111111111111111111111111111111;
    dec1.bits[3] = 0b00000000000000000000000000000000;
    test(sfleta_mul(dec1, dec1), 0, 0, 0, 0, 1);
}
END_TEST

START_TEST(mul_test_5) {
    sfleta_decimal dec1 = {{0, 0, 0, 0}, 0};
    sfleta_decimal dec2 = {{1, 2, 3, 4}, 2};
    test(sfleta_mul(dec1, dec2), 0, 0, 0, 0, 3);
}
END_TEST

START_TEST(mul_test_6) {
    sfleta_decimal dec1 = {{0, 0, 0, 0}, 0};
    sfleta_decimal dec2 = {{1, 2, 3, 4}, 3};
    test(sfleta_mul(dec1, dec2), 0, 0, 0, 0, 3);
}
END_TEST

START_TEST(mul_test_7) {
    sfleta_decimal dec1 = {{10, 0, 0, 0}, 0};
    sfleta_decimal dec2 = {{0xffffffff, 0xffffffff, 0xffffffff, 0}, 0};
    test(sfleta_mul(dec1, dec2), 0, 0, 0, 0, 1);
}
END_TEST

START_TEST(mul_test_8) {
    sfleta_decimal dec1 = {{1, 0, 0, 0}, 0};
    sfleta_decimal dec2 = {{1, 0, 0, 0}, 0};
    test(sfleta_mul(dec1, dec2), 1, 0, 0, 0, 0);
}
END_TEST

START_TEST(mul_test_9) {
    sfleta_decimal dec1 = {{1, 0, 0, 0}, 0};
    sfleta_setSign(&dec1, 1);
    sfleta_decimal dec2 = {{1, 0, 0, 0}, 0};
    sfleta_setSign(&dec2, 1);

    test(sfleta_mul(dec1, dec2), 1, 0, 0, 0, 0);
}
END_TEST

START_TEST(mul_test_10) {
    sfleta_decimal dec1 = {{1, 0, 0, 0}, 0};
    sfleta_decimal dec2 = {{1, 2, 3, 4}, 1};
    test(sfleta_mul(dec1, dec2), 0, 0, 0, 0, 1);
}
END_TEST

START_TEST(mul_test_11) {
    sfleta_decimal dec1 = {{1, 0, 0, 0}, 0};
    sfleta_decimal dec2 = {{1, 2, 3, 4}, 2};
    test(sfleta_mul(dec1, dec2), 0, 0, 0, 0, 2);
}
END_TEST

START_TEST(mul_test_12) {
    sfleta_decimal dec1 = {{1, 0, 0, 0}, 0};
    sfleta_decimal dec2 = {{1, 2, 3, 4}, 3};
    test(sfleta_mul(dec1, dec2), 0, 0, 0, 0, 3);
}
END_TEST

START_TEST(mul_test_13) {
    sfleta_decimal dec1 = {{1, 0, 0, 0}, 0};
    sfleta_setSign(&dec1, 1);
    sfleta_decimal dec2 = {{0, 0, 0, 0}, 0};
    test(sfleta_mul(dec1, dec2), 0, 0, 0, -2147483648, 0);
}
END_TEST

START_TEST(mul_test_14) {
    sfleta_decimal dec1 = {{1, 0, 0, 0}, 0};
    sfleta_setSign(&dec1, 1);
    sfleta_decimal dec2 = {{1, 0, 0, 0}, 0};
    test(sfleta_mul(dec1, dec2), 1, 0, 0, -2147483648, 0);
}
END_TEST

START_TEST(mul_test_15) {
    sfleta_decimal dec1 = {{1, 0, 0, -2147483648}, 0};
    sfleta_decimal dec2 = {{1, 0, 0, -2147483648}, 0};
    test(sfleta_mul(dec1, dec2), 1, 0, 0, 0, 0);
}
END_TEST

START_TEST(mul_test_16) {
    sfleta_decimal dec1 = {{1, 0, 0, 0}, 0};
    sfleta_setSign(&dec1, 1);
    sfleta_decimal dec2 = {{1, 2, 3, 4}, 1};
    test(sfleta_mul(dec1, dec2), 0, 0, 0, 0, 2);
}
END_TEST

START_TEST(mul_test_17) {
    sfleta_decimal dec1 = {{1, 0, 0, -2147483648}, 0};
    sfleta_decimal dec2 = {{1, 2, 3, 4}, 2};
    test(sfleta_mul(dec1, dec2), 0, 0, 0, 0, 1);
}
END_TEST

START_TEST(mul_test_18) {
    sfleta_decimal dec1 = {{1, 0, 0, -2147483648}, 0};
    sfleta_decimal dec2 = {{1, 2, 3, 4}, 3};
    test(sfleta_mul(dec1, dec2), 0, 0, 0, 0, 3);
}
END_TEST

START_TEST(mul_test_19) {
    sfleta_decimal dec1 = {{1, 2, 3, 4}, 1};
    sfleta_decimal dec2 = {{0, 0, 0, 0}, 0};
    test(sfleta_mul(dec1, dec2), 0, 0, 0, 0, 3);
}
END_TEST

START_TEST(mul_test_20) {
    sfleta_decimal dec1 = {{1, 2, 3, 4}, 1};
    sfleta_decimal dec2 = {{1, 0, 0, 0}, 0};
    test(sfleta_mul(dec1, dec2), 0, 0, 0, 0, 1);
}
END_TEST

START_TEST(mul_test_21) {
    sfleta_decimal dec1 = {{1, 2, 3, 4}, 1};
    sfleta_decimal dec2 = {{1, 0, 0, -2147483648}, 0};
    test(sfleta_mul(dec1, dec2), 0, 0, 0, 0, 2);
}
END_TEST

START_TEST(mul_test_22) {
    sfleta_decimal dec1 = {{1, 2, 3, 4}, 1};
    sfleta_decimal dec2 = {{1, 2, 3, 4}, 1};
    test(sfleta_mul(dec1, dec2), 0, 0, 0, 0, 1);
}
END_TEST

START_TEST(mul_test_23) {
    sfleta_decimal dec1 = {{1, 2, 3, 4}, 1};
    sfleta_decimal dec2 = {{1, 2, 3, 4}, 2};
    test(sfleta_mul(dec1, dec2), 0, 0, 0, 0, 2);
}
END_TEST

START_TEST(mul_test_24) {
    sfleta_decimal dec1 = {{1, 2, 3, 4}, 1};
    sfleta_decimal dec2 = {{1, 2, 3, 4}, 3};
    test(sfleta_mul(dec1, dec2), 0, 0, 0, 0, 3);
}
END_TEST

START_TEST(mul_test_25) {
    sfleta_decimal dec1 = {{1, 2, 3, 4}, 2};
    sfleta_decimal dec2 = {{0, 0, 0, 0}, 0};
    test(sfleta_mul(dec1, dec2), 0, 0, 0, 0, 3);
}
END_TEST

START_TEST(mul_test_26) {
    sfleta_decimal dec1 = {{0xffffffff, 0xffffffff, 0xffffffff, 0}, 0};
    sfleta_decimal dec2 = {{0xffffffff, 0xffffffff, 0xffffffff, 0}, 0};
    test(sfleta_mul(dec1, dec2), 0, 0, 0, 0, 1);
}
END_TEST

START_TEST(mul_test_27) {
    sfleta_decimal dec1 = {{1, 2, 3, 4}, 2};
    sfleta_decimal dec2 = {{1, 2, 3, 4}, 2};
    test(sfleta_mul(dec1, dec2), 0, 0, 0, 0, 1);
}
END_TEST

START_TEST(mul_test_28) {
    sfleta_decimal dec1 = {{1, 2, 3, 4}, 2};
    sfleta_decimal dec2 = {{1, 2, 3, 4}, 3};
    test(sfleta_mul(dec1, dec2), 0, 0, 0, 0, 3);
}
END_TEST

START_TEST(mul_test_29) {
    sfleta_decimal dec1 = {{1, 2, 3, 4}, 3};
    sfleta_decimal dec2 = {{1, 2, 3, 4}, 1};
    test(sfleta_mul(dec1, dec2), 0, 0, 0, 0, 3);
}
END_TEST

START_TEST(mul_test_30) {
    sfleta_decimal dec1 = {{1, 2, 3, 4}, 3};
    sfleta_decimal dec2 = {{1, 2, 3, 4}, 3};
    test(sfleta_mul(dec1, dec2), 0, 0, 0, 0, 3);
}
END_TEST

START_TEST(div_test_1) {
    sfleta_decimal dec1 = {{0, 0, 0, 0}, 0};
    sfleta_decimal dec2 = {{0, 0, 0, 0}, 0};
    test(sfleta_div(dec1, dec2), 0, 0, 0, 0, 3);
}
END_TEST

START_TEST(div_test_2) {
    sfleta_decimal dec1 = {{0, 0, 0, 0}, 0};
    sfleta_decimal dec2 = {{1, 0, 0, 0}, 0};
    test(sfleta_div(dec1, dec2), 0, 0, 0, 0, 0);
}
END_TEST

START_TEST(div_test_3) {
    sfleta_decimal dec1 = {{0, 0, 0, 0}, 0};
    sfleta_decimal dec2 = {{1, 0, 0, -2147483648}, 0};
    test(sfleta_div(dec1, dec2), 0, 0, 0, -2147483648, 0);
}
END_TEST

START_TEST(div_test_4) {
    sfleta_decimal dec1 = {{20, 0, 0, 0}, 0};
    sfleta_decimal dec2 = {{4, 0, 0, 0}, 0};
    test(sfleta_div(dec1, dec2), 5, 0, 0, 0, 0);
}
END_TEST

START_TEST(div_test_5) {
    sfleta_decimal dec1 = {{5, 0, 0, 0}, 0};
    sfleta_decimal dec2 = {{10, 0, 0, 0}, 0};
    test(sfleta_div(dec1, dec2), 5, 0, 0, 65536, 0);
}
END_TEST

START_TEST(div_test_6) {
    sfleta_decimal dec1 = {{0, 0, 0, 0}, 0};
    sfleta_decimal dec2 = {{1, 2, 3, 4}, 3};
    test(sfleta_div(dec1, dec2), 0, 0, 0, 0, 3);
}
END_TEST

START_TEST(div_test_7) {
    sfleta_decimal dec1 = {{1, 0, 0, 0}, 0};
    sfleta_decimal dec2 = {{0, 0, 0, 0}, 0};
    test(sfleta_div(dec1, dec2), 0, 0, 0, 0, 1);
}
END_TEST

START_TEST(div_test_8) {
    sfleta_decimal dec1 = {{1, 0, 0, 0}, 0};
    sfleta_decimal dec2 = {{1, 0, 0, 0}, 0};
    test(sfleta_div(dec1, dec2), 1, 0, 0, 0, 0);
}
END_TEST

START_TEST(div_test_9) {
    sfleta_decimal dec1 = {{1, 0, 0, 0}, 0};
    sfleta_decimal dec2 = {{1, 0, 0, -2147483648}, 0};
    test(sfleta_div(dec1, dec2), 1, 0, 0, -2147483648, 0);
}
END_TEST

START_TEST(div_test_10) {
    sfleta_decimal dec1 = {{1, 0, 0, 0}, 0};
    sfleta_decimal dec2 = {{1, 2, 3, 4}, 1};
    test(sfleta_div(dec1, dec2), 0, 0, 0, 0, 0);
}
END_TEST

START_TEST(div_test_11) {
    sfleta_decimal dec1 = {{1, 0, 0, 0}, 0};
    sfleta_decimal dec2 = {{1, 2, 3, 4}, 2};
    test(sfleta_div(dec1, dec2), 0, 0, 0, -2147483648, 0);
}
END_TEST

START_TEST(div_test_12) {
    sfleta_decimal dec1 = {{1, 0, 0, 0}, 0};
    sfleta_decimal dec2 = {{1, 2, 3, 4}, 3};
    test(sfleta_div(dec1, dec2), 0, 0, 0, 0, 3);
}
END_TEST

START_TEST(div_test_13) {
    sfleta_decimal dec1 = {{1, 0, 0, -2147483648}, 0};
    sfleta_decimal dec2 = {{0, 0, 0, 0}, 0};
    test(sfleta_div(dec1, dec2), 0, 0, 0, 0, 2);
}
END_TEST

START_TEST(div_test_14) {
    sfleta_decimal dec1 = {{1, 0, 0, -2147483648}, 0};
    sfleta_decimal dec2 = {{1, 0, 0, 0}, 0};
    test(sfleta_div(dec1, dec2), 1, 0, 0, -2147483648, 0);
}
END_TEST

START_TEST(div_test_15) {
    sfleta_decimal dec1 = {{1, 0, 0, -2147483648}, 0};
    sfleta_decimal dec2 = {{1, 0, 0, -2147483648}, 0};
    test(sfleta_div(dec1, dec2), 1, 0, 0, 0, 0);
}
END_TEST

START_TEST(div_test_16) {
    sfleta_decimal dec1 = {{1, 0, 0, -2147483648}, 0};
    sfleta_decimal dec2 = {{1, 2, 3, 4}, 1};
    test(sfleta_div(dec1, dec2), 0, 0, 0, -2147483648, 0);
}
END_TEST

START_TEST(div_test_17) {
    sfleta_decimal dec1 = {{1, 0, 0, -2147483648}, 0};
    sfleta_decimal dec2 = {{1, 2, 3, 4}, 2};
    test(sfleta_div(dec1, dec2), 0, 0, 0, 0, 0);
}
END_TEST

START_TEST(div_test_18) {
    sfleta_decimal dec1 = {{1, 0, 0, -2147483648}, 0};
    sfleta_decimal dec2 = {{1, 2, 3, 4}, 3};
    test(sfleta_div(dec1, dec2), 0, 0, 0, 0, 3);
}
END_TEST

START_TEST(div_test_19) {
    sfleta_decimal dec1 = {{1, 2, 3, 4}, 1};
    sfleta_decimal dec2 = {{0, 0, 0, 0}, 0};
    test(sfleta_div(dec1, dec2), 0, 0, 0, 0, 1);
}
END_TEST

START_TEST(div_test_20) {
    sfleta_decimal dec1 = {{1, 2, 3, 4}, 1};
    sfleta_decimal dec2 = {{1, 0, 0, 0}, 0};
    test(sfleta_div(dec1, dec2), 0, 0, 0, 0, 1);
}
END_TEST

START_TEST(mod_test_1) {
    sfleta_decimal dec1 = {{0, 0, 0, 0}, 0};
    sfleta_decimal dec2 = {{0, 0, 0, 0}, 0};
    test(sfleta_mod(dec1, dec2), 0, 0, 0, 0, 3);
}
END_TEST

START_TEST(mod_test_2) {
    sfleta_decimal dec1 = {{0, 0, 0, 0}, 0};
    sfleta_decimal dec2 = {{1, 0, 0, 0}, 0};
    test(sfleta_mod(dec1, dec2), 0, 0, 0, 0, 0);
}
END_TEST

START_TEST(mod_test_3) {
    sfleta_decimal dec1 = {{0, 0, 0, 0}, 0};
    sfleta_decimal dec2 = {{1, 0, 0, -2147483648}, 0};
    test(sfleta_mod(dec1, dec2), 0, 0, 0, 0, 0);
}
END_TEST

START_TEST(mod_test_4) {
    sfleta_decimal dec1 = {{0, 0, 0, 0}, 0};
    sfleta_decimal dec2 = {{1, 2, 3, 4}, 1};
    test(sfleta_mod(dec1, dec2), 0, 0, 0, 0, 0);
}
END_TEST

START_TEST(mod_test_5) {
    sfleta_decimal dec1 = {{0, 0, 0, 0}, 0};
    sfleta_decimal dec2 = {{1, 2, 3, 4}, 2};
    test(sfleta_mod(dec1, dec2), 0, 0, 0, 0, 0);
}
END_TEST

START_TEST(mod_test_6) {
    sfleta_decimal dec1 = {{0, 0, 0, 0}, 0};
    sfleta_decimal dec2 = {{1, 2, 3, 4}, 3};
    test(sfleta_mod(dec1, dec2), 0, 0, 0, 0, 3);
}
END_TEST

START_TEST(mod_test_7) {
    sfleta_decimal dec1 = {{1, 0, 0, 0}, 0};
    sfleta_decimal dec2 = {{0, 0, 0, 0}, 0};
    test(sfleta_mod(dec1, dec2), 0, 0, 0, 0, 3);
}
END_TEST

START_TEST(mod_test_8) {
    sfleta_decimal dec1 = {{1, 0, 0, 0}, 0};
    sfleta_decimal dec2 = {{1, 0, 0, 0}, 0};
    test(sfleta_mod(dec1, dec2), 0, 0, 0, 0, 0);
}
END_TEST

START_TEST(mod_test_9) {
    sfleta_decimal dec1 = {{1, 0, 0, 0}, 0};
    sfleta_decimal dec2 = {{1, 0, 0, -2147483648}, 0};
    test(sfleta_mod(dec1, dec2), 0, 0, 0, 0, 0);
}
END_TEST

START_TEST(mod_test_10) {
    sfleta_decimal dec1 = {{1, 0, 0, 0}, 0};
    sfleta_decimal dec2 = {{1, 2, 3, 4}, 1};
    test(sfleta_mod(dec1, dec2), 1, 0, 0, 0, 0);
}
END_TEST

START_TEST(mod_test_11) {
    sfleta_decimal dec1 = {{1, 0, 0, 0}, 0};
    sfleta_decimal dec2 = {{1, 2, 3, 4}, 2};
    test(sfleta_mod(dec1, dec2), 1, 0, 0, 0, 0);
}
END_TEST

START_TEST(mod_test_12) {
    sfleta_decimal dec1 = {{1, 0, 0, 0}, 0};
    sfleta_decimal dec2 = {{1, 2, 3, 4}, 3};
    test(sfleta_mod(dec1, dec2), 0, 0, 0, 0, 3);
}
END_TEST

START_TEST(mod_test_13) {
    sfleta_decimal dec1 = {{1, 0, 0, -2147483648}, 0};
    sfleta_decimal dec2 = {{0, 0, 0, 0}, 0};
    test(sfleta_mod(dec1, dec2), 0, 0, 0, 0, 3);
}
END_TEST

START_TEST(mod_test_14) {
    sfleta_decimal dec1 = {{1, 0, 0, -2147483648}, 0};
    sfleta_decimal dec2 = {{1, 0, 0, 0}, 0};
    test(sfleta_mod(dec1, dec2), 0, 0, 0, -2147483648, 0);
}
END_TEST

START_TEST(mod_test_15) {
    sfleta_decimal dec1 = {{1, 0, 0, -2147483648}, 0};
    sfleta_decimal dec2 = {{1, 0, 0, -2147483648}, 0};
    test(sfleta_mod(dec1, dec2), 0, 0, 0, -2147483648, 0);
}
END_TEST

START_TEST(mod_test_16) {
    sfleta_decimal dec1 = {{1, 0, 0, -2147483648}, 0};
    sfleta_decimal dec2 = {{1, 2, 3, 4}, 1};
    test(sfleta_mod(dec1, dec2), 1, 0, 0, -2147483648, 0);
}
END_TEST

START_TEST(mod_test_17) {
    sfleta_decimal dec1 = {{1, 0, 0, -2147483648}, 0};
    sfleta_decimal dec2 = {{1, 2, 3, 4}, 2};
    test(sfleta_mod(dec1, dec2), 1, 0, 0, -2147483648, 0);
}
END_TEST

START_TEST(mod_test_18) {
    sfleta_decimal dec1 = {{1, 0, 0, -2147483648}, 0};
    sfleta_decimal dec2 = {{1, 2, 3, 4}, 3};
    test(sfleta_mod(dec1, dec2), 0, 0, 0, 0, 3);
}
END_TEST

START_TEST(mod_test_19) {
    sfleta_decimal dec1 = {{10, 0, 0, 0}, 0};
    sfleta_decimal dec2 = {{3, 0, 0, 0}, 0};
    test(sfleta_mod(dec1, dec2), 1, 0, 0, 0, 0);
}
END_TEST

START_TEST(mod_test_20) {
    sfleta_decimal dec1 = {{1, 2, 3, 4}, 1};
    sfleta_decimal dec2 = {{1, 0, 0, 0}, 0};
    test(sfleta_mod(dec1, dec2), 0, 0, 0, 0, 3);
}
END_TEST

START_TEST(less_test_1) {
    sfleta_decimal dec1 = {{0, 0, 0, 0}, 0};
    sfleta_decimal dec2 = {{5, 0, 0, 0}, 0};
    ck_assert_int_eq(sfleta_is_less(dec1, dec2), TRUE);
} END_TEST

START_TEST(less_test_2) {
    sfleta_decimal dec1 = {{0, 0, 0, 0}, 0};
    sfleta_decimal dec2 = {{5, 0, 0, -2147483648}, 0};
    ck_assert_int_eq(sfleta_is_less(dec1, dec2), FALSE);
} END_TEST

START_TEST(less_test_3) {
    sfleta_decimal dec1 = {{8, 0, 0, -2147483648}, 0};
    sfleta_decimal dec2 = {{5, 0, 0, -2147483648}, 0};
    ck_assert_int_eq(sfleta_is_less(dec1, dec2), TRUE);
} END_TEST

START_TEST(less_test_4) {
    sfleta_decimal dec1 = {{8, 0, 0, -2147483648}, 0};
    sfleta_decimal dec2 = {{8, 0, 0, -2147483648}, 0};
    ck_assert_int_eq(sfleta_is_less(dec1, dec2), FALSE);
} END_TEST

START_TEST(less_test_5) {
    sfleta_decimal dec1 = {{0, 0, 0, 0}, 0};
    sfleta_decimal dec2 = {{1, 2, 3, 4}, 2};
    ck_assert_int_eq(sfleta_is_less(dec1, dec2), FALSE);
} END_TEST

START_TEST(less_test_6) {
    sfleta_decimal dec1 = {{0, 0, 0, 0}, 0};
    sfleta_decimal dec2 = {{1, 2, 3, 4}, 3};
    ck_assert_int_eq(sfleta_is_less(dec1, dec2), FALSE);
} END_TEST

START_TEST(less_test_7) {
    sfleta_decimal dec1 = {{1, 0, 0, 0}, 0};
    sfleta_decimal dec2 = {{1, 2, 3, 4}, 1};
    ck_assert_int_eq(sfleta_is_less(dec1, dec2), TRUE);
} END_TEST

START_TEST(less_test_8) {
    sfleta_decimal dec1 = {{1, 0, 0, 0}, 0};
    sfleta_decimal dec2 = {{1, 2, 3, 4}, 2};
    ck_assert_int_eq(sfleta_is_less(dec1, dec2), FALSE);
} END_TEST

START_TEST(less_test_9) {
    sfleta_decimal dec1 = {{1, 0, 0, -2147483648}, 0};
    sfleta_decimal dec2 = {{1, 2, 3, 4}, 1};
    ck_assert_int_eq(sfleta_is_less(dec1, dec2), TRUE);
} END_TEST

START_TEST(less_test_10) {
    sfleta_decimal dec1 = {{1, 2, 3, 4}, 1};
    sfleta_decimal dec2 = {{1, 2, 3, 4}, 1};
    ck_assert_int_eq(sfleta_is_less(dec1, dec2), FALSE);
} END_TEST

START_TEST(less_test_11) {
    sfleta_decimal dec1 = {{1, 2, 3, 4}, 2};
    sfleta_decimal dec2 = {{0, 0, 0, 0}, 0};
    ck_assert_int_eq(sfleta_is_less(dec1, dec2), TRUE);
} END_TEST

START_TEST(less_test_12) {
    sfleta_decimal dec1 = {{1, 2, 3, 4}, 2};
    sfleta_decimal dec2 = {{1, 0, 0, 0}, 0};
    ck_assert_int_eq(sfleta_is_less(dec1, dec2), TRUE);
}
END_TEST

START_TEST(less_test_13) {
    sfleta_decimal dec1 = {{1, 2, 3, 4}, 3};
    sfleta_decimal dec2 = {{1, 0, 0, 0}, 0};
    ck_assert_int_eq(sfleta_is_less(dec1, dec2), FALSE);
}
END_TEST

START_TEST(less_equal_test_1) {
    sfleta_decimal dec1 = {{0, 0, 0, 0}, 0};
    sfleta_decimal dec2 = {{0, 0, 0, 0}, 0};
    ck_assert_int_eq(sfleta_is_less_or_equal(dec1, dec2), TRUE);
}
END_TEST

START_TEST(less_equal_test_2) {
    sfleta_decimal dec1 = {{0, 0, 0, 0}, 0};
    sfleta_decimal dec2 = {{1, 0, 0, 0}, 0};
    ck_assert_int_eq(sfleta_is_less_or_equal(dec1, dec2), TRUE);
}
END_TEST

START_TEST(less_equal_test_3) {
    sfleta_decimal dec1 = {{1, 2, 3, 4}, 2};
    sfleta_decimal dec2 = {{1, 0, 0, 0}, 0};
    ck_assert_int_eq(sfleta_is_less_or_equal(dec1, dec2), TRUE);
}
END_TEST

START_TEST(less_equal_test_4) {
    sfleta_decimal dec1 = {{0, 0, 0, 0}, 0};
    sfleta_decimal dec2 = {{1, 2, 3, 4}, 1};
    ck_assert_int_eq(sfleta_is_less_or_equal(dec1, dec2), TRUE);
}
END_TEST

START_TEST(less_equal_test_5) {
    sfleta_decimal dec1 = {{0, 0, 0, 0}, 0};
    sfleta_decimal dec2 = {{1, 2, 3, 4}, 2};
    ck_assert_int_eq(sfleta_is_less_or_equal(dec1, dec2), FALSE);
}
END_TEST

START_TEST(less_equal_test_6) {
    sfleta_decimal dec1 = {{0, 0, 0, 0}, 0};
    sfleta_decimal dec2 = {{1, 2, 3, 4}, 3};
    ck_assert_int_eq(sfleta_is_less_or_equal(dec1, dec2), FALSE);
}
END_TEST

START_TEST(less_equal_test_7) {
    sfleta_decimal dec1 = {{1, 0, 0, 0}, 0};
    sfleta_decimal dec2 = {{0, 0, 0, 0}, 0};
    ck_assert_int_eq(sfleta_is_less_or_equal(dec1, dec2), FALSE);
}
END_TEST

START_TEST(less_equal_test_8) {
    sfleta_decimal dec1 = {{1, 0, 0, 0}, 0};
    sfleta_decimal dec2 = {{1, 0, 0, 0}, 0};
    ck_assert_int_eq(sfleta_is_less_or_equal(dec1, dec2), TRUE);
}
END_TEST

START_TEST(less_equal_test_9) {
    sfleta_decimal dec1 = {{1, 0, 0, 0}, 0};
    sfleta_decimal dec2 = {{1, 0, 0, -2147483648}, 0};
    ck_assert_int_eq(sfleta_is_less_or_equal(dec1, dec2), FALSE);
}
END_TEST

START_TEST(less_equal_test_10) {
    sfleta_decimal dec1 = {{1, 0, 0, 0}, 0};
    sfleta_decimal dec2 = {{1, 2, 3, 4}, 1};
    ck_assert_int_eq(sfleta_is_less_or_equal(dec1, dec2), TRUE);
}
END_TEST

START_TEST(greater_test_1) {
    sfleta_decimal dec1 = {{3, 0, 0, 0}, 0};
    sfleta_setSign(&dec1, 1);
    sfleta_decimal dec2 = {{5, 0, 0, 0}, 0};
    sfleta_setSign(&dec2, 1);
    ck_assert_int_eq(sfleta_is_greater(dec1, dec2), TRUE);
} END_TEST

START_TEST(greater_test_2) {
    sfleta_decimal dec1 = {{3, 0, 0, 0}, 0};
    sfleta_decimal dec2 = {{5, 0, 0, 0}, 0};
    sfleta_setSign(&dec2, 1);
    ck_assert_int_eq(sfleta_is_greater(dec1, dec2), TRUE);
} END_TEST

START_TEST(greater_test_3) {
    sfleta_decimal dec1 = {{8, 0, 0, 0}, 0};
    sfleta_setSign(&dec1, 1);
    sfleta_decimal dec2 = {{5, 0, 0, 0}, 0};
    sfleta_setSign(&dec2, 1);
    ck_assert_int_eq(sfleta_is_greater(dec1, dec2), FALSE);
} END_TEST

START_TEST(greater_test_4) {
    sfleta_decimal dec1 = {{8, 0, 0, 0}, 0};
    sfleta_setSign(&dec1, 1);
    sfleta_decimal dec2 = {{8, 0, 0, 0}, 0};
    sfleta_setSign(&dec2, 1);
    ck_assert_int_eq(sfleta_is_greater(dec1, dec2), FALSE);
} END_TEST

START_TEST(greater_test_5) {
    sfleta_decimal dec1 = {{1, 0, 0, 0}, 0};
    sfleta_decimal dec2 = {{1, 2, 3, 4}, 2};
    ck_assert_int_eq(sfleta_is_greater(dec1, dec2), TRUE);
} END_TEST

START_TEST(greater_test_6) {
    sfleta_decimal dec1 = {{1, 0, 0, 0}, 0};
    sfleta_decimal dec2 = {{1, 2, 3, 4}, 3};
    ck_assert_int_eq(sfleta_is_greater(dec1, dec2), FALSE);
} END_TEST

START_TEST(greater_test_7) {
    sfleta_decimal dec1 = {{5, 0, 0, 32768}, 0};
    sfleta_decimal dec2 = {{10, 0, 0, 0}, 0};
    ck_assert_int_eq(sfleta_is_greater(dec1, dec2), FALSE);
} END_TEST

START_TEST(greater_test_8) {
    sfleta_decimal dec1 = {{5, 0, 0, 0}, 0};
    sfleta_decimal dec2 = {{10, 0, 0, 0}, 0};
    sfleta_setScale(&dec2, 1);
    ck_assert_int_eq(sfleta_is_greater(dec1, dec2), TRUE);
} END_TEST

START_TEST(greater_test_9) {
    sfleta_decimal dec1 = {{5, 0, 0, 2064384}, 0};
    sfleta_decimal dec2 = {{10, 0, 0, 32768}, 0};
    ck_assert_int_eq(sfleta_is_greater(dec1, dec2), FALSE);
} END_TEST

START_TEST(greater_test_10) {
    sfleta_decimal dec1 = {{5, 0, 0, 2064384}, 0};
    sfleta_decimal dec2 = {{1, 0, 0, 2064384}, 0};
    ck_assert_int_eq(sfleta_is_greater(dec1, dec2), TRUE);
} END_TEST

START_TEST(greater_equal_test_1) {
    sfleta_decimal dec1 = {{8, 0, 0, -2147483648}, 0};
    sfleta_decimal dec2 = {{8, 0, 0, -2147483648}, 0};
    ck_assert_int_eq(sfleta_is_greater_or_equal(dec1, dec2), TRUE);
} END_TEST

START_TEST(greater_equal_test_2) {
    sfleta_decimal dec1 = {{8, 0, 0, 0}, 0};
    sfleta_decimal dec2 = {{1, 0, 0, -2147483648}, 0};
    ck_assert_int_eq(sfleta_is_greater_or_equal(dec1, dec2), TRUE);
} END_TEST

START_TEST(greater_equal_test_3) {
    sfleta_decimal dec1 = {{0, 0, 0, 0}, 0};
    sfleta_decimal dec2 = {{1, 0, 0, 0}, 0};
    ck_assert_int_eq(sfleta_is_greater_or_equal(dec1, dec2), FALSE);
} END_TEST

START_TEST(greater_equal_test_4) {
    sfleta_decimal dec1 = {{5, 0, 0, 2064384}, 0};
    sfleta_decimal dec2 = {{1, 0, 0, 2064384}, 0};
    ck_assert_int_eq(sfleta_is_greater(dec1, dec2), TRUE);
} END_TEST

START_TEST(greater_equal_test_5) {
    sfleta_decimal dec1 = {{5, 0, 0, 0}, 0};
    sfleta_decimal dec2 = {{1, 0, 0, 32768}, 0};
    ck_assert_int_eq(sfleta_is_greater(dec1, dec2), TRUE);
} END_TEST

START_TEST(equal_test_1) {
    sfleta_decimal dec1 = {{0, 0, 0, 0}, 0};
    sfleta_decimal dec2 = {{1, 0, 0, 0}, 0};
    ck_assert_int_eq(sfleta_is_equal(dec1, dec2), FALSE);
} END_TEST

START_TEST(equal_test_2) {
    sfleta_decimal dec1 = {{0, 0, 0, 0}, 0};
    sfleta_decimal dec2 = {{0, 0, 0, 0}, 0};
    ck_assert_int_eq(sfleta_is_equal(dec1, dec2), TRUE);
} END_TEST

START_TEST(equal_test_3) {
    sfleta_decimal dec1 = {{100000, 0, 0, 0}, 0};
    sfleta_decimal dec2 = {{100000, 0, 0, -2147483648}, 0};
    ck_assert_int_eq(sfleta_is_equal(dec1, dec2), FALSE);
} END_TEST

START_TEST(equal_test_4) {
    sfleta_decimal dec1 = {{2, 0, 0, 0}, 0};
    sfleta_setScale(&dec1, 3);
    sfleta_decimal dec2 = {{2, 0, 0, 0}, 0};
    ck_assert_int_eq(sfleta_is_equal(dec1, dec2), FALSE);
} END_TEST

START_TEST(equal_test_5) {
    sfleta_decimal dec1 = {{0, 0, 0, 0}, 0};
    sfleta_decimal dec2 = {{1, 2, 3, 4}, 3};
    ck_assert_int_eq(sfleta_is_equal(dec1, dec2), FALSE);
} END_TEST

START_TEST(equal_test_6) {
    sfleta_decimal dec1 = {{1, 2, 3, 4}, 1};
    sfleta_decimal dec2 = {{1, 2, 3, 4}, 1};
    ck_assert_int_eq(sfleta_is_equal(dec1, dec2), TRUE);
} END_TEST

START_TEST(equal_test_7) {
    sfleta_decimal dec1 = {{1, 2, 3, 4}, 2};
    sfleta_decimal dec2 = {{1, 0, 0, 0}, 0};
    ck_assert_int_eq(sfleta_is_equal(dec1, dec2), FALSE);
} END_TEST

START_TEST(equal_test_8) {
    sfleta_decimal dec1 = {{1, 2, 3, 4}, 2};
    sfleta_decimal dec2 = {{1, 2, 3, 4}, 2};
    ck_assert_int_eq(sfleta_is_equal(dec1, dec2), TRUE);
} END_TEST

START_TEST(equal_test_9) {
  sfleta_decimal dec1 = {{4294967295, 4294967295, 4294967295, 0}, 0};
  sfleta_decimal dec2 = {{1, 0, 0, 0}, 0};
  sfleta_setScale(&dec2, 28);
  sfleta_setSign(&dec2, 0);
  ck_assert_int_eq(sfleta_is_equal(dec1, dec2), FALSE);
}
END_TEST

START_TEST(equal_test_10) {
  sfleta_decimal dec1 = {{4294967295, 4294967295, 4294967295, 0}, 0};
  sfleta_decimal dec2 = {{4294967295, 0, 0, 0}, 0};
  sfleta_setScale(&dec2, 28);
  sfleta_setSign(&dec2, 0);
  ck_assert_int_eq(sfleta_is_equal(dec1, dec2), FALSE);
}
END_TEST

START_TEST(equal_test_11) {
  sfleta_decimal dec1 = {{4294967295, 4294967295, 4294967295, 0}, 0};
  sfleta_decimal dec2 = {{4294967295, 4294967295, 0, 0}, 0};
  sfleta_setScale(&dec2, 28);
  sfleta_setSign(&dec2, 0);
  ck_assert_int_eq(sfleta_is_equal(dec1, dec2), FALSE);
}
END_TEST

START_TEST(equal_test_12) {
  sfleta_decimal dec1 = {{4294967295, 4294967295, 4294967295, 0}, 0};
  sfleta_decimal dec2 = {{4294967295, 4294967295, 4294967295, 0}, 0};
  sfleta_setScale(&dec2, 28);
  sfleta_setSign(&dec2, 0);
  ck_assert_int_eq(sfleta_is_equal(dec1, dec2), FALSE);
}
END_TEST

START_TEST(equal_test_13) {
  sfleta_decimal dec1 = {{4294967295, 4294967295, 4294967295, 0}, 0};
  sfleta_decimal dec2 = {{4294967295, 4294967295, 4294967295, 0}, 0};
  ck_assert_int_eq(sfleta_is_equal(dec1, dec2), TRUE);
}
END_TEST

START_TEST(equal_test_14) {
  sfleta_decimal dec1 = {{4294967295, 4294967295, 4294967295, 0}, 0};
  sfleta_decimal dec2 = {{4294967295, 4294967295, 4294967295, 0}, 0};
  sfleta_setScale(&dec2, 1);
  sfleta_setSign(&dec2, 0);
  ck_assert_int_eq(sfleta_is_equal(dec1, dec2), FALSE);
}
END_TEST

START_TEST(equal_test_15) {
  sfleta_decimal dec1 = {{4294967295, 4294967295, 4294967295, 0}, 0};
  sfleta_decimal dec2 = {{4294967295, 4294967295, 4294967295, 0}, 0};
  sfleta_setScale(&dec1, 1);
  sfleta_setSign(&dec1, 0);
  sfleta_setScale(&dec2, 1);
  sfleta_setSign(&dec2, 0);
  ck_assert_int_eq(sfleta_is_equal(dec1, dec2), TRUE);
}
END_TEST

START_TEST(equal_test_16) {
  sfleta_decimal dec1 = {{4294967295, 4294967295, 4294967295, 0}, 0};
  sfleta_decimal dec2 = {{4294967295, 4294967295, 4294967295, 0}, 0};
  sfleta_setScale(&dec1, 15);
  sfleta_setSign(&dec1, 0);
  sfleta_setScale(&dec2, 20);
  sfleta_setSign(&dec2, 0);
  ck_assert_int_eq(sfleta_is_equal(dec1, dec2), FALSE);
}
END_TEST

START_TEST(equal_test_17) {
  sfleta_decimal dec1 = {{4294967295, 4294967295, 4294967295, 0},
                      0};
  sfleta_decimal dec2 = {{4294967295, 4294967295, 4294967295, 0},
                      0};
  sfleta_setScale(&dec1, 20);
  sfleta_setSign(&dec1, 1);
  sfleta_setScale(&dec2, 20);
  sfleta_setSign(&dec2, 0);
  ck_assert_int_eq(sfleta_is_equal(dec1, dec2), FALSE);
}
END_TEST

START_TEST(equal_test_18) {
  sfleta_decimal dec1 = {{4294967295, 4294967295, 4294967295, 0}, 0};
  sfleta_decimal dec2 = {{1, 0, 0, 0}, 0};
  sfleta_setScale(&dec1, 20);
  sfleta_setSign(&dec1, 1);
  sfleta_setScale(&dec2, 28);
  sfleta_setSign(&dec2, 1);
  ck_assert_int_eq(sfleta_is_equal(dec1, dec2), FALSE);
}
END_TEST

START_TEST(equal_test_19) {
  sfleta_decimal dec1 = {{4294967295, 4294967295, 4294967295, 0}, 0};
  sfleta_decimal dec2 = {{1, 0, 0, 0}, 0};
  sfleta_setScale(&dec1, 0);
  sfleta_setSign(&dec1, 1);
  sfleta_setScale(&dec2, 28);
  sfleta_setSign(&dec2, 1);
  ck_assert_int_eq(sfleta_is_equal(dec1, dec2), FALSE);
}
END_TEST

START_TEST(equal_test_20) {
  sfleta_decimal dec1 = {{4294967295, 4294967295, 4294967295, 0}, 0};
  sfleta_decimal dec2 = {{4294967295, 4294967295, 4294967295, 0}, 0};
  sfleta_setScale(&dec1, 27);
  sfleta_setSign(&dec1, 1);
  sfleta_setScale(&dec2, 28);
  sfleta_setSign(&dec2, 1);
  ck_assert_int_eq(sfleta_is_equal(dec1, dec2), FALSE);
}
END_TEST

START_TEST(not_equal_test_1) {
    sfleta_decimal dec1 = {{0, 0, 0, 0}, 0};
    sfleta_decimal dec2 = {{1, 0, 0, 0}, 0};
    ck_assert_int_eq(sfleta_is_not_equal(dec1, dec2), TRUE);
} END_TEST

START_TEST(not_equal_test_2) {
    sfleta_decimal dec1 = {{0, 0, 0, 0}, 0};
    sfleta_decimal dec2 = {{0, 0, 0, 0}, 0};
    ck_assert_int_eq(sfleta_is_not_equal(dec1, dec2), FALSE);
} END_TEST

START_TEST(not_equal_test_3) {
    sfleta_decimal dec1 = {{100000, 0, 0, 0}, 0};
    sfleta_decimal dec2 = {{100000, 0, 0, -2147483648}, 0};
    ck_assert_int_eq(sfleta_is_not_equal(dec1, dec2), TRUE);
} END_TEST

START_TEST(not_equal_test_4) {
    sfleta_decimal dec1 = {{2, 0, 0, 0}, 0};
    sfleta_setScale(&dec1, 3);
    sfleta_decimal dec2 = {{2, 0, 0, 0}, 0};
    ck_assert_int_eq(sfleta_is_not_equal(dec1, dec2), TRUE);
} END_TEST

START_TEST(not_equal_test_5) {
    sfleta_decimal dec1 = {{1, 0, 0, -2147483648}, 0};
    sfleta_decimal dec2 = {{1, 2, 3, 4}, 3};
    ck_assert_int_eq(sfleta_is_not_equal(dec1, dec2), TRUE);
}
END_TEST

START_TEST(decToInt_test_1) {
    float a = 5.0f;
    int sfleta_int = 0;
    int std_int = 0;
    sfleta_decimal dec = {{0, 0, 0, 0}, 0};
    sfleta_from_float_to_decimal(a, &dec);
    sfleta_from_decimal_to_int(dec, &sfleta_int);
    std_int = (int)a;
    ck_assert_int_eq(std_int, sfleta_int);
}
END_TEST

START_TEST(decToInt_test_2) {
    sfleta_decimal dec = {{0, 0xffffffff, 0, 0}, 0};
    int a = 3;
    int result = 0;
    result = sfleta_from_decimal_to_int(dec, &a);
    ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(decToFloat_test_1) {
    float src = 1113.312f;
    float result = 0.0f;
    sfleta_decimal dec = {{0, 0, 0, 0}, 0};
    sfleta_from_float_to_decimal(src, &dec);
    sfleta_from_decimal_to_float(dec, &result);
    ck_assert_float_eq(src, result);
}
END_TEST

START_TEST(decToFloat_test_2) {
    float src = -1.5e6;
    float result = 0.0f;
    sfleta_decimal dec = {{0, 0, 0, 0}, 0};
    sfleta_from_float_to_decimal(src, &dec);
    sfleta_from_decimal_to_float(dec, &result);
    ck_assert_float_eq(src, result);
}
END_TEST

START_TEST(decToFloat_test_3) {
    float src = 1.5e-6;
    float result = 0.0f;
    sfleta_decimal dec = {{0, 0, 0, 0}, 0};
    sfleta_from_float_to_decimal(src, &dec);
    sfleta_from_decimal_to_float(dec, &result);
    ck_assert_float_eq(src, result);
}
END_TEST

START_TEST(decToFloat_test_4) {
    float src = 1.5e-6;
    float result = 0.0f;
    sfleta_decimal dec = {{13, 12, 31, 31}, 0};
    sfleta_from_float_to_decimal(src, &dec);
    sfleta_from_decimal_to_float(dec, &result);
    ck_assert_float_eq(src, result);
}
END_TEST

START_TEST(decToFloat_test_5) {
    int a = 5;
    float sfleta_float = 0.0f;
    float std_float = 0.0f;
    sfleta_decimal dec = {{0, 0, 0, 0}, 0};
    sfleta_from_int_to_decimal(a, &dec);
    sfleta_from_decimal_to_float(dec, &sfleta_float);
    std_float = (float)a;
    ck_assert_float_eq(std_float, sfleta_float);
}
END_TEST

START_TEST(intToDec_test_1) {
    int src = -2147483648;
    int result = 0;
    sfleta_decimal dec = {{0, 0, 0, 0}, 0};
    sfleta_from_int_to_decimal(src, &dec);
    sfleta_from_decimal_to_int(dec, &result);
    ck_assert_int_eq(src, result);
}
END_TEST

START_TEST(intToDec_test_2) {
    int src = 2147483647;
    int result = 0;
    sfleta_decimal dec = {{0, 0, 0, 0}, 0};
    sfleta_from_int_to_decimal(src, &dec);
    sfleta_from_decimal_to_int(dec, &result);
    ck_assert_int_eq(src, result);
}
END_TEST

START_TEST(intToDec_test_3) {
    int src = 2147483647;
    int result = 0;
    sfleta_decimal dec = {{312.231, 12, 0xffffff, 021}, 4};
    sfleta_from_int_to_decimal(src, &dec);
    sfleta_from_decimal_to_int(dec, &result);
    ck_assert_int_eq(src, result);
}
END_TEST

START_TEST(floatToDec_test_1) {
    float src = 1.5e30;
    sfleta_decimal dec = {{0, 0, 0, 0}, 0};
    sfleta_from_float_to_decimal(src, &dec);
    test(dec, 0, 0, 0, 0, 1);
}
END_TEST

START_TEST(floatToDec_test_2) {
    float src = 1;
    sfleta_decimal dec = {{0, 0, 0, 0}, 0};
    sfleta_from_float_to_decimal(src, &dec);
    test(dec, 1, 0, 0, 0, 0);
}
END_TEST

START_TEST(floatToDec_test_3) {
  float src = 1.928318;
  sfleta_decimal dec = {{0, 0, 0, 0}, 0};
  sfleta_from_float_to_decimal(src, &dec);
  test(dec, 1928318, 0, 0, 393216, 0);
}
END_TEST

START_TEST(round_test_1) {
    sfleta_decimal dec1 = {{1, 2, 3, 0}, 1};
    test(sfleta_round(dec1), 0, 0, 0, 0, 1);
}
END_TEST

START_TEST(round_test_2) {
    sfleta_decimal dec1 = {{1, 2, 3, 0}, 2};
    test(sfleta_round(dec1), 0, 0, 0, 0, 2);
}
END_TEST

START_TEST(round_test_3) {
    sfleta_decimal dec1 = {{1, 2, 3, 0}, 3};
    test(sfleta_round(dec1), 0, 0, 0, 0, 3);
}
END_TEST

START_TEST(round_test_4) {
    sfleta_decimal dec1 = {{1, 2, 3, -2147483648}, 1};
    test(sfleta_round(dec1), 0, 0, 0, 0, 1);
}
END_TEST

START_TEST(round_test_5) {
    sfleta_decimal dec1 = {{1, 2, 3, -2147483648}, 2};
    test(sfleta_round(dec1), 0, 0, 0, 0, 2);
}
END_TEST

START_TEST(round_test_6) {
    sfleta_decimal dec1 = {{1, 2, 3, -2147483648}, 3};
    test(sfleta_round(dec1), 0, 0, 0, 0, 3);
}
END_TEST

START_TEST(round_test_7) {
    sfleta_decimal dec1 = {{0, 0, 0, 0}, 0};
    test(sfleta_round(dec1), 0, 0, 0, 0, 0);
}
END_TEST

START_TEST(round_test_8) {
    sfleta_decimal dec1 = {{0x1DF5AD8, 0, 0, 0x50000}, 0};  // 314.15
    test(sfleta_round(dec1), 314, 0, 0, 0, 0);
}
END_TEST

START_TEST(round_test_9) {
    sfleta_decimal dec1 = {{0x16E360, 0, 0, 0x80060000}, 0};  // -1.5
    test(sfleta_round(dec1), 2, 0, 0, -2147483648, 0);
}
END_TEST

START_TEST(round_test_10) {
  sfleta_decimal dec1 = {{121, 0, 0, 0}, 0};
  sfleta_setSign(&dec1, 0);
  sfleta_setScale(&dec1, 1);
  test(sfleta_round(dec1), 12, 0, 0, 0, 0);
}
END_TEST

START_TEST(round_test_11) {
  sfleta_decimal dec2 = {{121, 0, 0, 0}, 0};
  sfleta_setSign(&dec2, 1);
  sfleta_setScale(&dec2, 1);
  test(sfleta_round(dec2), 12, 0, 0, 0x80000000, 0);
}
END_TEST

START_TEST(round_test_12) {
  sfleta_decimal dec3 = {{125, 0, 0, 0}, 0};
  sfleta_setSign(&dec3, 0);
  sfleta_setScale(&dec3, 1);
  test(sfleta_round(dec3), 13, 0, 0, 0, 0);
}
END_TEST

START_TEST(round_test_13) {
  sfleta_decimal dec4 = {{125, 0, 0, 0}, 0};
  sfleta_setSign(&dec4, 1);
  sfleta_setScale(&dec4, 1);
  test(sfleta_round(dec4), 13, 0, 0, 0x80000000, 0);
}
END_TEST

START_TEST(round_test_14) {
  sfleta_decimal dec5 = {{126, 0, 0, 0}, 0};
  sfleta_setSign(&dec5, 0);
  sfleta_setScale(&dec5, 1);
  test(sfleta_round(dec5), 13, 0, 0, 0, 0);
}
END_TEST

START_TEST(round_test_15) {
  sfleta_decimal dec6 = {{126, 0, 0, 0}, 0};
  sfleta_setSign(&dec6, 1);
  sfleta_setScale(&dec6, 1);
  test(sfleta_round(dec6), 13, 0, 0, 0x80000000, 0);
}
END_TEST

START_TEST(round_test_16) {
  sfleta_decimal dec7 = {{1, 0, 0, 0}, 0};
  sfleta_setSign(&dec7, 1);
  sfleta_setScale(&dec7, 1);
  test(sfleta_round(dec7), 0, 0, 0, 0x80000000, 0);
}
END_TEST

START_TEST(round_test_17) {
  sfleta_decimal dec8 = {{1011, 0, 0, 0}, 0};
  sfleta_setSign(&dec8, 0);
  sfleta_setScale(&dec8, 1);
  test(sfleta_round(dec8), 101, 0, 0, 0, 0);
}
END_TEST

START_TEST(round_test_18) {
  sfleta_decimal dec9 = {{1011, 0, 0, 0}, 0};
  sfleta_setSign(&dec9, 1);
  sfleta_setScale(&dec9, 1);
  test(sfleta_round(dec9), 101, 0, 0, 0x80000000, 0);
}
END_TEST

START_TEST(round_test_19) {
  sfleta_decimal dec10 = {{1015, 0, 0, 0}, 0};
  sfleta_setSign(&dec10, 0);
  sfleta_setScale(&dec10, 1);
  test(sfleta_round(dec10), 102, 0, 0, 0, 0);
}
END_TEST

START_TEST(round_test_20) {
#line 85
  sfleta_decimal dec11 = {{1015, 0, 0, 0}, 0};
  sfleta_setSign(&dec11, 1);
  sfleta_setScale(&dec11, 1);
  test(sfleta_round(dec11), 102, 0, 0, 0x80000000, 0);
}
END_TEST

START_TEST(round_test_21) {
  sfleta_decimal dec12 = {{1019, 0, 0, 0}, 0};
  sfleta_setSign(&dec12, 0);
  sfleta_setScale(&dec12, 1);
  test(sfleta_round(dec12), 102, 0, 0, 0, 0);
}
END_TEST

START_TEST(round_test_22) {
  sfleta_decimal dec13 = {{1019, 0, 0, 0}, 0};
  sfleta_setSign(&dec13, 1);
  sfleta_setScale(&dec13, 1);
  test(sfleta_round(dec13), 102, 0, 0, 0x80000000, 0);
}
END_TEST

START_TEST(round_test_23) {
  sfleta_decimal dec14 = {{1, 0, 0, 0}, 0};
  sfleta_setSign(&dec14, 0);
  sfleta_setScale(&dec14, 28);
  test(sfleta_round(dec14), 0, 0, 0, 0, 0);
}
END_TEST

START_TEST(round_test_24) {
  sfleta_decimal dec15 = {{1, 0, 0, 0}, 0};
  sfleta_setSign(&dec15, 1);
  sfleta_setScale(&dec15, 28);
  test(sfleta_round(dec15), 0, 0, 0, 0x80000000, 0);
}
END_TEST

START_TEST(round_test_25) {
  sfleta_decimal dec16 = {{4294967295, 4294967295, 4294967295, 0}, 0};
  sfleta_setSign(&dec16, 0);
  sfleta_setScale(&dec16, 28);
  test(sfleta_round(dec16), 8, 0, 0, 0, 0);
}
END_TEST

START_TEST(round_test_26) {
  sfleta_decimal dec17 = {{4294967295, 4294967295, 4294967295, 0}, 0};
  sfleta_setSign(&dec17, 1);
  sfleta_setScale(&dec17, 28);
  test(sfleta_round(dec17), 8, 0, 0, 0x80000000, 0);
}
END_TEST

START_TEST(round_test_27) {
  sfleta_decimal dec18 = {{4294967295, 4294967295, 4294967295, 0}, 1};
  sfleta_setSign(&dec18, 1);
  sfleta_setScale(&dec18, 28);
  test(sfleta_round(dec18), 0, 0, 0, 0, 1);
}
END_TEST

START_TEST(round_test_28) {
  sfleta_decimal dec19 = {{4294967295, 4294967295, 4294967295, 0}, 2};
  sfleta_setSign(&dec19, 1);
  sfleta_setScale(&dec19, 28);
  test(sfleta_round(dec19), 0, 0, 0, 0, 2);
}
END_TEST

START_TEST(round_test_29) {
  sfleta_decimal dec19 = {{4294967295, 4294967295, 4294967295, 0}, 3};
  sfleta_setScale(&dec19, 28);
  test(sfleta_round(dec19), 0, 0, 0, 0, 3);
}
END_TEST

START_TEST(floor_test_1) {
    sfleta_decimal dec1 = {{1, 2, 3, 0}, 1};
    test(sfleta_floor(dec1), 0, 0, 0, 0, 1);
}
END_TEST

START_TEST(floor_test_2) {
    sfleta_decimal dec1 = {{1, 2, 3, 0}, 2};
    test(sfleta_floor(dec1), 0, 0, 0, 0, 2);
}
END_TEST

START_TEST(floor_test_3) {
    sfleta_decimal dec1 = {{1, 2, 3, 0}, 3};
    test(sfleta_floor(dec1), 0, 0, 0, 0, 3);
}
END_TEST

START_TEST(floor_test_4) {
    sfleta_decimal dec1 = {{1, 2, 3, -2147483648}, 1};
    test(sfleta_floor(dec1), 0, 0, 0, 0, 1);
}
END_TEST

START_TEST(floor_test_5) {
    sfleta_decimal dec1 = {{1, 2, 3, -2147483648}, 2};
    test(sfleta_floor(dec1), 0, 0, 0, 0, 2);
}
END_TEST

START_TEST(floor_test_6) {
    sfleta_decimal dec1 = {{1, 2, 3, -2147483648}, 3};
    test(sfleta_floor(dec1), 0, 0, 0, 0, 3);
}
END_TEST

START_TEST(floor_test_7) {
    sfleta_decimal dec1 = {{0, 0, 0, 0}, 0};
    test(sfleta_floor(dec1), 0, 0, 0, 0, 0);
}
END_TEST

START_TEST(floor_test_8) {
    sfleta_decimal dec1 = {{0x1DF5AD8, 0, 0, 0x50000}, 0};  // 314.15
    test(sfleta_floor(dec1), 314, 0, 0, 0, 0);
}
END_TEST

START_TEST(floor_test_9) {
    sfleta_decimal dec1 = {{0x16E360, 0, 0, 0x80060000}, 0};  // -1.5
    test(sfleta_floor(dec1), 2, 0, 0, -2147483648, 0);
}
END_TEST

START_TEST(floor_test_10) {
  sfleta_decimal dec10 = {{126, 0, 0, 0x10000}, 0};
  test(sfleta_floor(dec10), 12, 0, 0, 0, 0);
}
END_TEST

START_TEST(floor_test_11) {
  sfleta_decimal dec11 = {{121, 0, 0, 0x10000}, 0};
  test(sfleta_floor(dec11), 12, 0, 0, 0, 0);
}
END_TEST

START_TEST(floor_test_12) {
  sfleta_decimal dec12 = {{95, 0, 0, 0x10000}, 0};
  test(sfleta_floor(dec12), 9, 0, 0, 0, 0);
}
END_TEST

START_TEST(floor_test_13) {
  sfleta_decimal dec13 = {{816, 0, 0, 0x20000}, 0};
  test(sfleta_floor(dec13), 8, 0, 0, 0, 0);
}
END_TEST

START_TEST(floor_test_14) {
  sfleta_decimal dec14 = {{1, 0, 0, 0x10000}, 0};
  test(sfleta_floor(dec14), 0, 0, 0, 0, 0);
}
END_TEST

START_TEST(floor_test_15) {
  sfleta_decimal dec15 = {{1, 0, 0, 0x80010000}, 0};
  test(sfleta_floor(dec15), 1, 0, 0, 0x80000000, 0);
}
END_TEST

START_TEST(floor_test_16) {
  sfleta_decimal dec16 = {{0, 0, 0, 0x80000000}, 0};
  test(sfleta_floor(dec16), 0, 0, 0, 0x80000000, 0);
}
END_TEST

START_TEST(floor_test_17) {
  sfleta_decimal dec17 = {{11, 0, 0, 0x80010000}, 0};
  test(sfleta_floor(dec17), 2, 0, 0, 0x80000000, 0);
}
END_TEST

START_TEST(floor_test_18) {
  sfleta_decimal dec18 = {{19, 0, 0, 0x80010000}, 0};
  test(sfleta_floor(dec18), 2, 0, 0, 0x80000000, 0);
}
END_TEST

START_TEST(floor_test_19) {
  sfleta_decimal dec19 = {{39, 0, 0, 0x80010000}, 0};
  test(sfleta_floor(dec19), 4, 0, 0, 0x80000000, 0);
}
END_TEST

START_TEST(floor_test_20) {
  sfleta_decimal dec20 = {{1, 0, 0, 0x801C0000}, 0};
  test(sfleta_floor(dec20), 1, 0, 0, 0x80000000, 0);
}
END_TEST

START_TEST(floor_test_21) {
  sfleta_decimal dec21 = {{4294967295, 4294967295, 4294967295, 0x1C0000}, 0};
  test(sfleta_floor(dec21), 7, 0, 0, 0, 0);
}
END_TEST

START_TEST(floor_test_22) {
  sfleta_decimal dec22 = {{4294967295, 4294967295, 4294967295, 0x801C0000}, 0};
  test(sfleta_floor(dec22), 8, 0, 0, 0x80000000, 0);
}
END_TEST

START_TEST(truncate_test_1) {
    sfleta_decimal dec1 = {{1, 2, 3, 0}, 1};
    test(sfleta_truncate(dec1), 0, 0, 0, 0, 1);
}
END_TEST

START_TEST(truncate_test_2) {
    sfleta_decimal dec1 = {{1, 2, 3, 0}, 2};
    test(sfleta_truncate(dec1), 0, 0, 0, 0, 2);
}
END_TEST

START_TEST(truncate_test_3) {
    sfleta_decimal dec1 = {{1, 2, 3, 0}, 3};
    test(sfleta_truncate(dec1), 0, 0, 0, 0, 3);
}
END_TEST

START_TEST(truncate_test_4) {
    sfleta_decimal dec1 = {{1, 2, 3, -2147483648}, 1};
    test(sfleta_truncate(dec1), 0, 0, 0, 0, 1);
}
END_TEST

START_TEST(truncate_test_5) {
    sfleta_decimal dec1 = {{1, 2, 3, -2147483648}, 2};
    test(sfleta_truncate(dec1), 0, 0, 0, 0, 2);
}
END_TEST

START_TEST(truncate_test_6) {
    sfleta_decimal dec1 = {{1, 2, 3, -2147483648}, 3};
    test(sfleta_truncate(dec1), 0, 0, 0, 0, 3);
}
END_TEST

START_TEST(truncate_test_7) {
    sfleta_decimal dec1 = {{0, 0, 0, 0}, 0};
    test(sfleta_truncate(dec1), 0, 0, 0, 0, 0);
}
END_TEST

START_TEST(truncate_test_8) {
    sfleta_decimal dec1 = {{0x1DF5AD8, 0, 0, 0x50000}, 0};  // 314.15
    test(sfleta_truncate(dec1), 314, 0, 0, 0, 0);
}
END_TEST

START_TEST(truncate_test_9) {
    sfleta_decimal dec1 = {{0x16E360, 0, 0, 0x80060000}, 0};  // -1.5
    test(sfleta_truncate(dec1), 1, 0, 0, -2147483648, 0);
}
END_TEST

START_TEST(truncate_test_10) {
    sfleta_decimal dec1 = {{0x6ACFC0, 0, 0, 0x70000}, 0};  // 0.7
    test(sfleta_truncate(dec1), 0, 0, 0, 0, 0);
}
END_TEST

START_TEST(negate_test_1) {
    sfleta_decimal dec1 = {{0, 0, 0, 0}, 0};
    test(sfleta_negate(dec1), 0, 0, 0, -2147483648, 0);
}
END_TEST

START_TEST(negate_test_2) {
    sfleta_decimal dec1 = {{1, 0, 0, 0}, 0};
    test(sfleta_negate(dec1), 1, 0, 0, -2147483648, 0);
}
END_TEST

START_TEST(negate_test_3) {
    sfleta_decimal dec1 = {{1, 0, 0, -2147483648}, 0};
    test(sfleta_negate(dec1), 1, 0, 0, 0, 0);
}
END_TEST

START_TEST(negate_test_4) {
    sfleta_decimal dec1 = {{1, 2, 3, 4}, 1};
    test(sfleta_negate(dec1), 0, 0, 0, 0, 2);
}
END_TEST

START_TEST(negate_test_5) {
    sfleta_decimal dec1 = {{1, 2, 3, 4}, 2};
    test(sfleta_negate(dec1), 0, 0, 0, 0, 1);
}
END_TEST

START_TEST(negate_test_6) {
    sfleta_decimal dec1 = {{1, 2, 3, 4}, 3};
    test(sfleta_negate(dec1), 0, 0, 0, 0, 3);
}
END_TEST

Suite* decimal_suite_create(void) {
    Suite* suite = suite_create("Decimal");

    TCase* tcase_core = tcase_create("Core of Decimal");

    tcase_add_test(tcase_core, add_test_1);
    tcase_add_test(tcase_core, add_test_2);
    tcase_add_test(tcase_core, add_test_3);
    tcase_add_test(tcase_core, add_test_4);
    tcase_add_test(tcase_core, add_test_5);
    tcase_add_test(tcase_core, add_test_6);
    tcase_add_test(tcase_core, add_test_7);
    tcase_add_test(tcase_core, add_test_8);
    tcase_add_test(tcase_core, add_test_9);
    tcase_add_test(tcase_core, add_test_10);
    tcase_add_test(tcase_core, add_test_11);
    tcase_add_test(tcase_core, add_test_12);
    tcase_add_test(tcase_core, add_test_13);
    tcase_add_test(tcase_core, add_test_14);
    tcase_add_test(tcase_core, add_test_15);
    tcase_add_test(tcase_core, add_test_16);
    tcase_add_test(tcase_core, add_test_17);
    tcase_add_test(tcase_core, add_test_18);
    tcase_add_test(tcase_core, add_test_19);
    tcase_add_test(tcase_core, add_test_20);
    tcase_add_test(tcase_core, sub_test_1);
    tcase_add_test(tcase_core, sub_test_2);
    tcase_add_test(tcase_core, sub_test_3);
    tcase_add_test(tcase_core, sub_test_4);
    tcase_add_test(tcase_core, sub_test_5);
    tcase_add_test(tcase_core, sub_test_6);
    tcase_add_test(tcase_core, sub_test_7);
    tcase_add_test(tcase_core, sub_test_8);
    tcase_add_test(tcase_core, sub_test_9);
    tcase_add_test(tcase_core, sub_test_10);
    tcase_add_test(tcase_core, sub_test_11);
    tcase_add_test(tcase_core, sub_test_12);
    tcase_add_test(tcase_core, sub_test_13);
    tcase_add_test(tcase_core, sub_test_14);
    tcase_add_test(tcase_core, sub_test_15);
    tcase_add_test(tcase_core, mul_test_1);
    tcase_add_test(tcase_core, mul_test_2);
    tcase_add_test(tcase_core, mul_test_3);
    tcase_add_test(tcase_core, mul_test_4);
    tcase_add_test(tcase_core, mul_test_5);
    tcase_add_test(tcase_core, mul_test_6);
    tcase_add_test(tcase_core, mul_test_7);
    tcase_add_test(tcase_core, mul_test_8);
    tcase_add_test(tcase_core, mul_test_9);
    tcase_add_test(tcase_core, mul_test_10);
    tcase_add_test(tcase_core, mul_test_11);
    tcase_add_test(tcase_core, mul_test_12);
    tcase_add_test(tcase_core, mul_test_13);
    tcase_add_test(tcase_core, mul_test_14);
    tcase_add_test(tcase_core, mul_test_15);
    tcase_add_test(tcase_core, mul_test_16);
    tcase_add_test(tcase_core, mul_test_17);
    tcase_add_test(tcase_core, mul_test_18);
    tcase_add_test(tcase_core, mul_test_19);
    tcase_add_test(tcase_core, mul_test_20);
    tcase_add_test(tcase_core, mul_test_21);
    tcase_add_test(tcase_core, mul_test_22);
    tcase_add_test(tcase_core, mul_test_23);
    tcase_add_test(tcase_core, mul_test_24);
    tcase_add_test(tcase_core, mul_test_25);
    tcase_add_test(tcase_core, mul_test_26);
    tcase_add_test(tcase_core, mul_test_27);
    tcase_add_test(tcase_core, mul_test_28);
    tcase_add_test(tcase_core, mul_test_29);
    tcase_add_test(tcase_core, mul_test_30);
    tcase_add_test(tcase_core, div_test_1);
    tcase_add_test(tcase_core, div_test_2);
    tcase_add_test(tcase_core, div_test_3);
    tcase_add_test(tcase_core, div_test_4);
    tcase_add_test(tcase_core, div_test_5);
    tcase_add_test(tcase_core, div_test_6);
    tcase_add_test(tcase_core, div_test_7);
    tcase_add_test(tcase_core, div_test_8);
    tcase_add_test(tcase_core, div_test_9);
    tcase_add_test(tcase_core, div_test_10);
    tcase_add_test(tcase_core, div_test_11);
    tcase_add_test(tcase_core, div_test_12);
    tcase_add_test(tcase_core, div_test_13);
    tcase_add_test(tcase_core, div_test_14);
    tcase_add_test(tcase_core, div_test_15);
    tcase_add_test(tcase_core, div_test_16);
    tcase_add_test(tcase_core, div_test_17);
    tcase_add_test(tcase_core, div_test_18);
    tcase_add_test(tcase_core, div_test_19);
    tcase_add_test(tcase_core, div_test_20);
    tcase_add_test(tcase_core, mod_test_1);
    tcase_add_test(tcase_core, mod_test_2);
    tcase_add_test(tcase_core, mod_test_3);
    tcase_add_test(tcase_core, mod_test_4);
    tcase_add_test(tcase_core, mod_test_5);
    tcase_add_test(tcase_core, mod_test_6);
    tcase_add_test(tcase_core, mod_test_7);
    tcase_add_test(tcase_core, mod_test_8);
    tcase_add_test(tcase_core, mod_test_9);
    tcase_add_test(tcase_core, mod_test_10);
    tcase_add_test(tcase_core, mod_test_11);
    tcase_add_test(tcase_core, mod_test_12);
    tcase_add_test(tcase_core, mod_test_13);
    tcase_add_test(tcase_core, mod_test_14);
    tcase_add_test(tcase_core, mod_test_15);
    tcase_add_test(tcase_core, mod_test_16);
    tcase_add_test(tcase_core, mod_test_17);
    tcase_add_test(tcase_core, mod_test_18);
    tcase_add_test(tcase_core, mod_test_19);
    tcase_add_test(tcase_core, mod_test_20);
    tcase_add_test(tcase_core, less_test_1);
    tcase_add_test(tcase_core, less_test_2);
    tcase_add_test(tcase_core, less_test_3);
    tcase_add_test(tcase_core, less_test_4);
    tcase_add_test(tcase_core, less_test_5);
    tcase_add_test(tcase_core, less_test_6);
    tcase_add_test(tcase_core, less_test_7);
    tcase_add_test(tcase_core, less_test_8);
    tcase_add_test(tcase_core, less_test_9);
    tcase_add_test(tcase_core, less_test_10);
    tcase_add_test(tcase_core, less_test_11);
    tcase_add_test(tcase_core, less_test_12);
    tcase_add_test(tcase_core, less_test_13);
    tcase_add_test(tcase_core, less_equal_test_1);
    tcase_add_test(tcase_core, less_equal_test_2);
    tcase_add_test(tcase_core, less_equal_test_3);
    tcase_add_test(tcase_core, less_equal_test_4);
    tcase_add_test(tcase_core, less_equal_test_5);
    tcase_add_test(tcase_core, less_equal_test_6);
    tcase_add_test(tcase_core, less_equal_test_7);
    tcase_add_test(tcase_core, less_equal_test_8);
    tcase_add_test(tcase_core, less_equal_test_9);
    tcase_add_test(tcase_core, less_equal_test_10);
    tcase_add_test(tcase_core, greater_test_1);
    tcase_add_test(tcase_core, greater_test_2);
    tcase_add_test(tcase_core, greater_test_3);
    tcase_add_test(tcase_core, greater_test_4);
    tcase_add_test(tcase_core, greater_test_5);
    tcase_add_test(tcase_core, greater_test_6);
    tcase_add_test(tcase_core, greater_test_7);
    tcase_add_test(tcase_core, greater_test_8);
    tcase_add_test(tcase_core, greater_test_9);
    tcase_add_test(tcase_core, greater_test_10);
    tcase_add_test(tcase_core, greater_equal_test_1);
    tcase_add_test(tcase_core, greater_equal_test_2);
    tcase_add_test(tcase_core, greater_equal_test_3);
    tcase_add_test(tcase_core, greater_equal_test_4);
    tcase_add_test(tcase_core, greater_equal_test_5);
    tcase_add_test(tcase_core, equal_test_1);
    tcase_add_test(tcase_core, equal_test_2);
    tcase_add_test(tcase_core, equal_test_3);
    tcase_add_test(tcase_core, equal_test_4);
    tcase_add_test(tcase_core, equal_test_5);
    tcase_add_test(tcase_core, equal_test_6);
    tcase_add_test(tcase_core, equal_test_7);
    tcase_add_test(tcase_core, equal_test_8);
    tcase_add_test(tcase_core, equal_test_9);
    tcase_add_test(tcase_core, equal_test_10);
    tcase_add_test(tcase_core, equal_test_11);
    tcase_add_test(tcase_core, equal_test_12);
    tcase_add_test(tcase_core, equal_test_13);
    tcase_add_test(tcase_core, equal_test_14);
    tcase_add_test(tcase_core, equal_test_15);
    tcase_add_test(tcase_core, equal_test_16);
    tcase_add_test(tcase_core, equal_test_17);
    tcase_add_test(tcase_core, equal_test_18);
    tcase_add_test(tcase_core, equal_test_19);
    tcase_add_test(tcase_core, equal_test_20);
    tcase_add_test(tcase_core, not_equal_test_1);
    tcase_add_test(tcase_core, not_equal_test_2);
    tcase_add_test(tcase_core, not_equal_test_3);
    tcase_add_test(tcase_core, not_equal_test_4);
    tcase_add_test(tcase_core, not_equal_test_5);
    tcase_add_test(tcase_core, intToDec_test_1);
    tcase_add_test(tcase_core, intToDec_test_2);
    tcase_add_test(tcase_core, intToDec_test_3);
    tcase_add_test(tcase_core, floatToDec_test_1);
    tcase_add_test(tcase_core, floatToDec_test_2);
    tcase_add_test(tcase_core, floatToDec_test_3);
    tcase_add_test(tcase_core, decToInt_test_1);
    tcase_add_test(tcase_core, decToInt_test_2);
    tcase_add_test(tcase_core, decToFloat_test_1);
    tcase_add_test(tcase_core, decToFloat_test_2);
    tcase_add_test(tcase_core, decToFloat_test_3);
    tcase_add_test(tcase_core, decToFloat_test_4);
    tcase_add_test(tcase_core, decToFloat_test_5);
    tcase_add_test(tcase_core, floor_test_1);
    tcase_add_test(tcase_core, floor_test_2);
    tcase_add_test(tcase_core, floor_test_3);
    tcase_add_test(tcase_core, floor_test_4);
    tcase_add_test(tcase_core, floor_test_5);
    tcase_add_test(tcase_core, floor_test_6);
    tcase_add_test(tcase_core, floor_test_7);
    tcase_add_test(tcase_core, floor_test_8);
    tcase_add_test(tcase_core, floor_test_9);
    tcase_add_test(tcase_core, floor_test_10);
    tcase_add_test(tcase_core, floor_test_11);
    tcase_add_test(tcase_core, floor_test_12);
    tcase_add_test(tcase_core, floor_test_13);
    tcase_add_test(tcase_core, floor_test_14);
    tcase_add_test(tcase_core, floor_test_15);
    tcase_add_test(tcase_core, floor_test_16);
    tcase_add_test(tcase_core, floor_test_17);
    tcase_add_test(tcase_core, floor_test_18);
    tcase_add_test(tcase_core, floor_test_19);
    tcase_add_test(tcase_core, floor_test_20);
    tcase_add_test(tcase_core, floor_test_21);
    tcase_add_test(tcase_core, floor_test_22);
    tcase_add_test(tcase_core, round_test_1);
    tcase_add_test(tcase_core, round_test_2);
    tcase_add_test(tcase_core, round_test_3);
    tcase_add_test(tcase_core, round_test_4);
    tcase_add_test(tcase_core, round_test_5);
    tcase_add_test(tcase_core, round_test_6);
    tcase_add_test(tcase_core, round_test_7);
    tcase_add_test(tcase_core, round_test_8);
    tcase_add_test(tcase_core, round_test_9);
    tcase_add_test(tcase_core, round_test_10);
    tcase_add_test(tcase_core, round_test_11);
    tcase_add_test(tcase_core, round_test_12);
    tcase_add_test(tcase_core, round_test_13);
    tcase_add_test(tcase_core, round_test_14);
    tcase_add_test(tcase_core, round_test_15);
    tcase_add_test(tcase_core, round_test_16);
    tcase_add_test(tcase_core, round_test_17);
    tcase_add_test(tcase_core, round_test_18);
    tcase_add_test(tcase_core, round_test_19);
    tcase_add_test(tcase_core, round_test_20);
    tcase_add_test(tcase_core, round_test_21);
    tcase_add_test(tcase_core, round_test_22);
    tcase_add_test(tcase_core, round_test_23);
    tcase_add_test(tcase_core, round_test_24);
    tcase_add_test(tcase_core, round_test_25);
    tcase_add_test(tcase_core, round_test_26);
    tcase_add_test(tcase_core, round_test_27);
    tcase_add_test(tcase_core, round_test_28);
    tcase_add_test(tcase_core, round_test_29);
    tcase_add_test(tcase_core, truncate_test_1);
    tcase_add_test(tcase_core, truncate_test_2);
    tcase_add_test(tcase_core, truncate_test_3);
    tcase_add_test(tcase_core, truncate_test_4);
    tcase_add_test(tcase_core, truncate_test_5);
    tcase_add_test(tcase_core, truncate_test_6);
    tcase_add_test(tcase_core, truncate_test_7);
    tcase_add_test(tcase_core, truncate_test_8);
    tcase_add_test(tcase_core, truncate_test_9);
    tcase_add_test(tcase_core, truncate_test_10);
    tcase_add_test(tcase_core, negate_test_1);
    tcase_add_test(tcase_core, negate_test_2);
    tcase_add_test(tcase_core, negate_test_3);
    tcase_add_test(tcase_core, negate_test_4);
    tcase_add_test(tcase_core, negate_test_5);
    tcase_add_test(tcase_core, negate_test_6);
    suite_add_tcase(suite, tcase_core);

    return suite;
}

int main() {
    Suite* suite = decimal_suite_create();
    SRunner* suite_runner = srunner_create(suite);

    srunner_run_all(suite_runner, CK_NORMAL);
    int failed_count = srunner_ntests_failed(suite_runner);
    srunner_free(suite_runner);
    return failed_count == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
