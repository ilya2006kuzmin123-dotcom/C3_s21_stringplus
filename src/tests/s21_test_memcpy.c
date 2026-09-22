#include "s21_tests.h"

START_TEST(test_s21_memcpy_1) {
  char str1[] = "World!";
  char str2[] = "Hello, ";
  ck_assert_ptr_eq(s21_memcpy(str2, str1, strlen(str2)),
                   memcpy(str2, str1, strlen(str2)));
}
END_TEST

START_TEST(test_s21_memcpy_2) {
  char str1[] = "Hello!";
  char str2[] = "";
  ck_assert_ptr_eq(s21_memcpy(str2, str1, strlen(str2)),
                   memcpy(str2, str1, strlen(str2)));
}
END_TEST

START_TEST(test_s21_memcpy_3) {
  char str1[] = "";
  char str2[] = "Hello!";
  ck_assert_ptr_eq(s21_memcpy(str2, str1, strlen(str2)),
                   memcpy(str2, str1, strlen(str2)));
}
END_TEST

START_TEST(test_s21_memcpy_4) {
  char str1[] = "";
  char str2[] = "";
  ck_assert_ptr_eq(s21_memcpy(str2, str1, strlen(str2)),
                   memcpy(str2, str1, strlen(str2)));
}
END_TEST

START_TEST(test_s21_memcpy_5) {
  char str1[] = "   ";
  char str2[] = " ";
  ck_assert_ptr_eq(s21_memcpy(str2, str1, strlen(str2)),
                   memcpy(str2, str1, strlen(str2)));
}
END_TEST

Suite* test_suite_memcpy() {
  Suite* s = suite_create("s21_memcpy");
  TCase* tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_memcpy_1);
  tcase_add_test(tc_core, test_s21_memcpy_2);
  tcase_add_test(tc_core, test_s21_memcpy_3);
  tcase_add_test(tc_core, test_s21_memcpy_4);
  tcase_add_test(tc_core, test_s21_memcpy_5);

  suite_add_tcase(s, tc_core);

  return s;
}