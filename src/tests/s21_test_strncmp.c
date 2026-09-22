#include "s21_tests.h"

START_TEST(test_s21_strncmp_1) {
  char str1[] = "";
  char str2[] = "";
  ck_assert_int_eq(s21_strncmp(str1, str2, strlen(str1)),
                   strncmp(str1, str2, strlen(str1)));
}
END_TEST

START_TEST(test_s21_strncmp_2) {
  char str1[] = "Hello, World!";
  char str2[] = "Hello, world!";
  ck_assert_int_eq(s21_strncmp(str1, str2, strlen(str1)),
                   strncmp(str1, str2, strlen(str1)));
}
END_TEST

START_TEST(test_s21_strncmp_3) {
  char str1[] = "\n\\0";
  char str2[] = "\n\\0";
  ck_assert_int_eq(s21_strncmp(str1, str2, strlen(str1)),
                   strncmp(str1, str2, strlen(str1)));
}
END_TEST

START_TEST(test_s21_strncmp_4) {
  char str1[] = "Hello, World!";
  char str2[] = "rld";
  ck_assert_int_eq(s21_strncmp(str1, str2, strlen(str1)),
                   strncmp(str1, str2, strlen(str1)));
}
END_TEST

START_TEST(test_s21_strncmp_5) {
  char str1[] = "Hello, World!";
  char str2[] = "\0";
  ck_assert_int_eq(s21_strncmp(str1, str2, strlen(str1)),
                   strncmp(str1, str2, strlen(str1)));
}
END_TEST

START_TEST(test_s21_strncmp_6) {
  char str1[] = "Hello, World!";
  char str2[] = "H";
  ck_assert_int_eq(s21_strncmp(str1, str2, strlen(str1)),
                   strncmp(str1, str2, strlen(str1)));
}
END_TEST

START_TEST(test_s21_strncmp_7) {
  char str1[] = "Hello, World!";
  char str2[] = "ol";
  ck_assert_int_eq(s21_strncmp(str1, str2, strlen(str1)),
                   strncmp(str1, str2, strlen(str1)));
}
END_TEST

START_TEST(test_s21_strncmp_8) {
  char str1[] = "Hello, World!";
  char str2[] = "lo";
  ck_assert_int_eq(s21_strncmp(str1, str2, strlen(str2)),
                   strncmp(str1, str2, strlen(str2)));
}
END_TEST

START_TEST(test_s21_strncmp_9) {
  char str1[] = "Hello, World!";
  char str2[] = "ZzZ";
  ck_assert_int_eq(s21_strncmp(str1, str2, strlen(str1) + 10),
                   strncmp(str1, str2, strlen(str1) + 10));
}
END_TEST

START_TEST(test_s21_strncmp_10) {
  char str1[] = "Hello, ";
  char str2[] = "Hello, World!";
  ck_assert_int_eq(s21_strncmp(str1, str2, strlen(str2)),
                   strncmp(str1, str2, strlen(str2)));
}
END_TEST

Suite* test_suite_strncmp() {
  Suite* s = suite_create("s21_strncmp");
  TCase* tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_strncmp_1);
  tcase_add_test(tc_core, test_s21_strncmp_2);
  tcase_add_test(tc_core, test_s21_strncmp_3);
  tcase_add_test(tc_core, test_s21_strncmp_4);
  tcase_add_test(tc_core, test_s21_strncmp_5);
  tcase_add_test(tc_core, test_s21_strncmp_6);
  tcase_add_test(tc_core, test_s21_strncmp_7);
  tcase_add_test(tc_core, test_s21_strncmp_8);
  tcase_add_test(tc_core, test_s21_strncmp_9);
  tcase_add_test(tc_core, test_s21_strncmp_10);

  suite_add_tcase(s, tc_core);

  return s;
}