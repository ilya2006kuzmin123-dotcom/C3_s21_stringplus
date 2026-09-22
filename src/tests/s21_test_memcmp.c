#include "s21_tests.h"

START_TEST(test_memcmp_1) {
  char* a = "hihihihi";
  ck_assert_int_eq(s21_memcmp("hihihihi", a, 9), memcmp("hihihihi", a, 9));
}
END_TEST

START_TEST(test_memcmp_2) {
  char* a = "dmoqw;qoew";
  ck_assert_int_eq(s21_memcmp("dmo!qw;qoew", a, 11),
                   memcmp("dmo!qw;qoew", a, 11));
}
END_TEST

START_TEST(test_memcmp_3) {
  char* a = "aa";
  ck_assert_int_eq(s21_memcmp("ab", a, 2), memcmp("ab", a, 2));
}
END_TEST

START_TEST(test_memcmp_4) {
  char* a = "hjopa";
  ck_assert_int_eq(s21_memcmp("hihihihi", a, 5), memcmp("hihihihi", a, 5));
}
END_TEST

START_TEST(test_memcmp_5) {
  char* a = "";
  ck_assert_int_eq(s21_memcmp("", a, 1), memcmp("", a, 1));
}
END_TEST

START_TEST(test_memcmp_6) {
  char* a = "";
  ck_assert_int_eq(s21_memcmp("peep", a, 1), memcmp("peep", a, 1));
}
END_TEST

START_TEST(test_memcmp_7) {
  char* a = "";
  ck_assert_int_eq(s21_memcmp(a, "peep", 1), memcmp(a, "peep", 1));
}
END_TEST

START_TEST(test_memcmp_8) {
  int str1[] = {48, 49, 2, 3, 4, 5, 6, 7, 8, 9};
  int str2[] = {48, 49, 2, 3, 4, 5, 6, 7, 8, 9};
  ck_assert_int_eq(s21_memcmp(str1, str2, 9), memcmp(str1, str2, 9));
}
END_TEST

START_TEST(test_memcmp_9) {
  int str1[] = {48, 49, 2, 27, 4, 5, 6, 7, 8, 9};
  int str2[] = {48, 49, 2, 3, 4, 5, 6, 7, 8, 9};
  ck_assert_int_eq(s21_memcmp(str1, str2, 10), memcmp(str1, str2, 10));
}
END_TEST

START_TEST(test_memcmp_10) {
  int str1[] = {48, 49, 2, 3, 4, 5, 6, 7, 8, 9};
  int str2[] = {48, 49, 2, 3, 99, 5, 6, 7, 8, 9};
  ck_assert_int_eq(s21_memcmp(str1, str2, 10), memcmp(str1, str2, 10));
}
END_TEST

Suite* test_suite_memcmp() {
  Suite* suite = suite_create("s21_memcmp");
  TCase* tcase = tcase_create("s21_memcmp_case");

  tcase_add_test(tcase, test_memcmp_1);
  tcase_add_test(tcase, test_memcmp_2);
  tcase_add_test(tcase, test_memcmp_3);
  tcase_add_test(tcase, test_memcmp_4);
  tcase_add_test(tcase, test_memcmp_5);
  tcase_add_test(tcase, test_memcmp_6);
  tcase_add_test(tcase, test_memcmp_7);
  tcase_add_test(tcase, test_memcmp_8);
  tcase_add_test(tcase, test_memcmp_9);
  tcase_add_test(tcase, test_memcmp_10);

  suite_add_tcase(suite, tcase);

  return suite;
}