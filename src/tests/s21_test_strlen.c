#include "s21_tests.h"

START_TEST(test_s21_strlen_1) {
  char str1[] = "Hello, World!";
  ck_assert_uint_eq(s21_strlen(str1), strlen(str1));
}
END_TEST

START_TEST(test_s21_strlen_2) {
  char str1[] = "";
  ck_assert_uint_eq(s21_strlen(str1), strlen(str1));
}
END_TEST

START_TEST(test_s21_strlen_3) {
  char str1[] = "±123±";
  ck_assert_uint_eq(s21_strlen(str1), strlen(str1));
}
END_TEST

START_TEST(test_s21_strlen_4) {
  char str1[] = "Nikita\0Nikita\0Nikita\0";
  ck_assert_uint_eq(s21_strlen(str1), strlen(str1));
}
END_TEST

START_TEST(test_s21_strlen_5) {
  char str1[] = "123";
  ck_assert_uint_eq(s21_strlen(str1), strlen(str1));
}
END_TEST

Suite* test_suite_strlen() {
  Suite* s = suite_create("s21_strlen");
  TCase* tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_strlen_1);
  tcase_add_test(tc_core, test_s21_strlen_2);
  tcase_add_test(tc_core, test_s21_strlen_3);
  tcase_add_test(tc_core, test_s21_strlen_4);
  tcase_add_test(tc_core, test_s21_strlen_5);

  suite_add_tcase(s, tc_core);

  return s;
}