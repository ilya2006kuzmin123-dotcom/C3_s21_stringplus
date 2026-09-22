#include "s21_tests.h"

START_TEST(test_memset_1) {
  char str1[] = "Hihihi lalala";
  char str2[] = "Hihihi lalala";
  s21_memset(str1, '_', 10);
  memset(str2, '_', 10);
  ck_assert_mem_eq(str1, str2, 14);
}
END_TEST

START_TEST(test_memset_2) {
  char str1[] = "Hihihi lalala";
  char str2[] = "Hihihi lalala";
  s21_memset(str1, '0', 1);
  memset(str2, '0', 1);
  ck_assert_mem_eq(str1, str2, 13);
}
END_TEST

START_TEST(test_memset_3) {
  char str1[] = "Hihihi lalala";
  char str2[] = "Hihihi lalala";
  s21_memset(str1, '!', 13);
  memset(str2, '!', 13);
  ck_assert_mem_eq(str1, str2, 13);
}
END_TEST

START_TEST(test_memset_4) {
  int str1[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  int str2[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  s21_memset(str1, 5, 40);
  memset(str2, 5, 40);
  ck_assert_mem_eq(str1, str2, 9);
}
END_TEST

START_TEST(test_memset_5) {
  int str1[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  int str2[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  s21_memset(str1, 5, 20);
  memset(str2, 5, 20);
  ck_assert_mem_eq(str1, str2, 9);
}
END_TEST

START_TEST(test_memset_6) {
  int str1[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  int str2[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  s21_memset(str1, 5, 1);
  memset(str2, 5, 1);
  ck_assert_mem_eq(str1, str2, 9);
}
END_TEST

Suite* test_suite_memset() {
  Suite* suite = suite_create("s21_memset");
  TCase* tcase = tcase_create("s21_memset_case");

  tcase_add_test(tcase, test_memset_1);
  tcase_add_test(tcase, test_memset_2);
  tcase_add_test(tcase, test_memset_3);
  tcase_add_test(tcase, test_memset_4);
  tcase_add_test(tcase, test_memset_5);
  tcase_add_test(tcase, test_memset_6);

  suite_add_tcase(suite, tcase);

  return suite;
}