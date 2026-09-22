#include "s21_tests.h"

START_TEST(test_s21_memchr_1) {
  char str1[] = "Hello, World!";
  char str2 = 'e';
  ck_assert_ptr_eq(s21_memchr(str1, str2, strlen(str1)),
                   memchr(str1, str2, strlen(str1)));
}
END_TEST

START_TEST(test_s21_memchr_2) {
  char str1[] = "";
  char str2 = ' ';
  ck_assert_ptr_eq(s21_memchr(str1, str2, strlen(str1)),
                   memchr(str1, str2, strlen(str1)));
}
END_TEST

START_TEST(test_s21_memchr_3) {
  char str1[] = "±123±";
  char str2 = '+';
  ck_assert_ptr_eq(s21_memchr(str1, str2, strlen(str1)),
                   memchr(str1, str2, strlen(str1)));
}
END_TEST

START_TEST(test_s21_memchr_4) {
  char str1[] = "Nikita\\0Nikitos";
  char str2 = 's';
  ck_assert_ptr_eq(s21_memchr(str1, str2, strlen(str1)),
                   memchr(str1, str2, strlen(str1)));
}
END_TEST

START_TEST(test_s21_memchr_5) {
  char str1[] = "123";
  char str2 = ' ';
  ck_assert_ptr_eq(s21_memchr(str1, str2, strlen(str1)),
                   memchr(str1, str2, strlen(str1)));
}
END_TEST

Suite* test_suite_memchr() {
  Suite* s = suite_create("s21_memchr");
  TCase* tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_memchr_1);
  tcase_add_test(tc_core, test_s21_memchr_2);
  tcase_add_test(tc_core, test_s21_memchr_3);
  tcase_add_test(tc_core, test_s21_memchr_4);
  tcase_add_test(tc_core, test_s21_memchr_5);

  suite_add_tcase(s, tc_core);

  return s;
}