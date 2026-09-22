#include "s21_tests.h"

START_TEST(test_s21_strncat_1) {
  char str1[] = "World!";
  char str2[30] = "Hello, ";
  ck_assert_pstr_eq(s21_strncat(str2, str1, strlen(str2)),
                    strncat(str2, str1, strlen(str2)));
}
END_TEST

START_TEST(test_s21_strncat_2) {
  char str1[] = " ";
  char str2[] = "";
  ck_assert_pstr_eq(s21_strncat(str2, str1, strlen(str2)),
                    strncat(str2, str1, strlen(str2)));
}
END_TEST

START_TEST(test_s21_strncat_3) {
  char str1[] = "";
  char str2[] = "";
  ck_assert_pstr_eq(s21_strncat(str2, str1, strlen(str2)),
                    strncat(str2, str1, strlen(str2)));
}
END_TEST

START_TEST(test_s21_strncat_4) {
  char str1[] = "World!";
  char str2[30] = "Hello, ";
  ck_assert_pstr_eq(s21_strncat(str2, str1, strlen(str2)),
                    strncat(str2, str1, strlen(str2)));
}
END_TEST

START_TEST(test_s21_strncat_5) {
  char str1[] = "World!";
  char str2[30] = "Hello, ";
  ck_assert_pstr_eq(s21_strncat(str2 + 7, str1, strlen(str2)),
                    strncat(str2 + 7, str1, strlen(str2)));
}
END_TEST

START_TEST(test_s21_strncat_6) {
  char str1[] = "World!";
  char str2[30] = "Hello, ";
  ck_assert_pstr_eq(s21_strncat(str2, str1, 3), strncat(str2, str1, 3));
}
END_TEST

START_TEST(test_s21_strncat_7) {
  char str1[] = "";
  char str2[] = "";
  ck_assert_pstr_eq(s21_strncat(str2, str1, 0), strncat(str2, str1, 0));
}
END_TEST

START_TEST(test_s21_strncat_8) {
  char str1[] = "World!";
  char str2[] = "Hello, ";
  ck_assert_pstr_eq(s21_strncat(str2, str1, 0), strncat(str2, str1, 0));
}
END_TEST

Suite* test_suite_strncat() {
  Suite* s = suite_create("s21_strncat");
  TCase* tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_strncat_1);
  tcase_add_test(tc_core, test_s21_strncat_2);
  tcase_add_test(tc_core, test_s21_strncat_3);
  tcase_add_test(tc_core, test_s21_strncat_4);
  tcase_add_test(tc_core, test_s21_strncat_5);
  tcase_add_test(tc_core, test_s21_strncat_6);
  tcase_add_test(tc_core, test_s21_strncat_7);
  tcase_add_test(tc_core, test_s21_strncat_8);

  suite_add_tcase(s, tc_core);

  return s;
}