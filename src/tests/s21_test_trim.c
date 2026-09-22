#include "s21_tests.h"

START_TEST(test_s21_trim_1) {
  char str1[] = "123HELLO123";
  char str2[] = "123";
  ck_assert_str_eq(s21_trim(str1, str2), "HELLO");
}
END_TEST

START_TEST(test_s21_trim_2) {
  char str1[] = "123HELL123O123";
  char str2[] = "123";
  ck_assert_str_eq(s21_trim(str1, str2), "HELL123O");
}
END_TEST

START_TEST(test_s21_trim_3) {
  char str1[] = " HELLO ";
  char str2[] = " ";
  ck_assert_str_eq(s21_trim(str1, str2), "HELLO");
}

START_TEST(test_s21_trim_4) {
  char str1[] = "   HELLO   ";
  char str2[] = " ";
  ck_assert_str_eq(s21_trim(str1, str2), "HELLO");
}

START_TEST(test_s21_trim_5) {
  char str1[] = "123321";
  char str2[] = "123";
  ck_assert_str_eq(s21_trim(str1, str2), "");
}

START_TEST(test_s21_trim_6) {
  char str1[] = "123HELLO123";
  char str2[] = "321";
  ck_assert_str_eq(s21_trim(str1, str2), "HELLO");
}

Suite* test_suite_trim() {
  Suite* s = suite_create("s21_trim");
  TCase* tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_trim_1);
  tcase_add_test(tc_core, test_s21_trim_2);
  tcase_add_test(tc_core, test_s21_trim_3);
  tcase_add_test(tc_core, test_s21_trim_4);
  tcase_add_test(tc_core, test_s21_trim_5);
  tcase_add_test(tc_core, test_s21_trim_6);

  suite_add_tcase(s, tc_core);

  return s;
}