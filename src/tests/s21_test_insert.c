#include "s21_tests.h"

START_TEST(test_s21_insert_1) {
  char str1[] = "Yabloko";
  char str2[] = "I love my . He is very kind!";
  s21_size index = 10;
  char expected[] = "I love my Yabloko. He is very kind!";
  char* got = (char*)s21_insert(str2, str1, index);
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(test_s21_insert_2) {
  char str1[] = "Hello, ";
  char str2[] = "Aboba!";
  s21_size index = 0;
  char expected[] = "Hello, Aboba!";
  char* got = (char*)s21_insert(str2, str1, index);
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(test_s21_insert_3) {
  char str1[] = "";
  char str2[] = "";
  s21_size index = 100;
  char* expected = S21_NULL;
  char* got = (char*)s21_insert(str2, str1, index);
  ck_assert_pstr_eq(got, expected);
}
END_TEST

START_TEST(test_s21_insert_4) {
  char* str2 = NULL;
  char* str1 = NULL;
  s21_size index = 100;
  char* expected = NULL;
  char* got = (char*)s21_insert(str2, str1, index);
  ck_assert_ptr_eq(got, expected);
}
END_TEST

START_TEST(test_s21_insert_5) {
  char str1[] = "Monkey";
  char str2[] = "Space  ";
  s21_size index = 6;
  char expected[] = "Space Monkey ";
  char* got = (char*)s21_insert(str2, str1, index);
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(insert_str_null) {
  char* str1 = S21_NULL;
  char str2[] = "Space  ";
  s21_size index = 6;
  void* expected = S21_NULL;
  char* got = (char*)s21_insert(str2, str1, index);
  ck_assert_pstr_eq(got, expected);
}
END_TEST

Suite* test_suite_insert() {
  Suite* s = suite_create("s21_insert");
  TCase* tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_insert_1);
  tcase_add_test(tc_core, test_s21_insert_2);
  tcase_add_test(tc_core, test_s21_insert_3);
  tcase_add_test(tc_core, test_s21_insert_4);
  tcase_add_test(tc_core, test_s21_insert_5);
  tcase_add_test(tc_core, insert_str_null);

  suite_add_tcase(s, tc_core);

  return s;
}