#include "s21_tests.h"

START_TEST(test_strncpy_1) {
  char d1[] = "123456789";
  char s1[] = "000000000";
  char d2[] = "123456789";
  char s2[] = "000000000";
  strncpy(d1, s1, 9);
  s21_strncpy(d2, s2, 9);
  ck_assert_pstr_eq(d1, d2);
}
END_TEST

START_TEST(test_strncpy_2) {
  char d1[] = "12345";
  char s1[] = "000000000";
  char d2[] = "12345";
  char s2[] = "000000000";
  strncpy(d1, s1, 5);
  s21_strncpy(d2, s2, 5);
  ck_assert_pstr_eq(d1, d2);
}
END_TEST

START_TEST(test_strncpy_3) {
  char d1[] = "123456789";
  char s1[] = "00000";
  char d2[] = "123456789";
  char s2[] = "00000";
  strncpy(d1, s1, 9);
  s21_strncpy(d2, s2, 9);
  ck_assert_pstr_eq(d1, d2);
}
END_TEST

START_TEST(test_strncpy_4) {
  char d1[] = "\0";
  char s1[] = "mewmewmew";
  char d2[] = "\0";
  char s2[] = "mewmewmew";
  strncpy(d1, s1, 1);
  s21_strncpy(d2, s2, 1);
  ck_assert_pstr_eq(d1, d2);
}
END_TEST

START_TEST(test_strncpy_5) {
  char d1[] = "mewmewmew";
  char s1[] = "";
  char d2[] = "mewmewmew";
  char s2[] = "";
  strncpy(d1, s1, 5);
  s21_strncpy(d2, s2, 5);
  ck_assert_pstr_eq(d1, d2);
}
END_TEST

START_TEST(test_strncpy_6) {
  char d1[] = "";
  char s1[] = "";
  char d2[] = "";
  char s2[] = "";
  strncpy(d1, s1, 1);
  s21_strncpy(d2, s2, 1);
  ck_assert_pstr_eq(d1, d2);
}
END_TEST

Suite* test_suite_strncpy() {
  Suite* suite = suite_create("s21_strncpy");
  TCase* tcase = tcase_create("s21_strncpy_case");

  tcase_add_test(tcase, test_strncpy_1);
  tcase_add_test(tcase, test_strncpy_2);
  tcase_add_test(tcase, test_strncpy_3);
  tcase_add_test(tcase, test_strncpy_4);
  tcase_add_test(tcase, test_strncpy_5);
  tcase_add_test(tcase, test_strncpy_6);

  suite_add_tcase(suite, tcase);

  return suite;
}