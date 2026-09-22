#include "s21_tests.h"

START_TEST(test_s21_strcspn_1) {
  char str1[] = "Hello, World!";
  char str2[] = "rld";
  ck_assert_uint_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST

START_TEST(test_s21_strcspn_2) {
  char str1[] = "Hello, World!";
  char str2[] = "H";
  ck_assert_uint_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST

START_TEST(test_s21_strcspn_3) {
  char str1[] = "Hello, World!";
  char str2[] = "h";
  ck_assert_uint_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST

START_TEST(test_s21_strcspn_4) {
  char str1[] = "Hello, World!";
  char str2[] = "Japan";
  ck_assert_uint_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST

START_TEST(test_s21_strcspn_5) {
  char str1[] = "";
  char str2[] = "Mexico";
  ck_assert_uint_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST

START_TEST(test_s21_strcspn_6) {
  char str1[] = "";
  char str2[] = "";
  ck_assert_uint_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST

START_TEST(test_s21_strcspn_7) {
  char str1[] = "Please, let us pass this project uwu";
  char str2[] = "";
  ck_assert_uint_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST

START_TEST(test_s21_strcspn_8) {
  char str1[] = "";
  char str2[] = "I'll love you always";
  ck_assert_uint_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST

Suite* test_suite_strcspn() {
  Suite* s = suite_create("s21_strcspn");
  TCase* tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_strcspn_1);
  tcase_add_test(tc_core, test_s21_strcspn_2);
  tcase_add_test(tc_core, test_s21_strcspn_3);
  tcase_add_test(tc_core, test_s21_strcspn_4);
  tcase_add_test(tc_core, test_s21_strcspn_5);
  tcase_add_test(tc_core, test_s21_strcspn_6);
  tcase_add_test(tc_core, test_s21_strcspn_7);
  tcase_add_test(tc_core, test_s21_strcspn_8);

  suite_add_tcase(s, tc_core);

  return s;
}