#include "s21_tests.h"

START_TEST(test_strrchr_1) {
  char str[] =
      "Kindness is a language which the deaf can hear and the blind can see";
  int c = 'e';
  char* pointer1 = 0;
  char* pointer2 = 0;
  pointer1 = s21_strrchr(str, c);
  pointer2 = strrchr(str, c);
  ck_assert_pstr_eq(pointer1, pointer2);
}
END_TEST

START_TEST(test_strrchr_2) {
  char str[] =
      "Kindness is a language which the deaf can hear and the blind can see";
  int c = 'y';
  char* pointer1 = 0;
  char* pointer2 = 0;
  pointer1 = s21_strrchr(str, c);
  pointer2 = strrchr(str, c);
  ck_assert_pstr_eq(pointer1, pointer2);
}
END_TEST

START_TEST(test_strrchr_3) {
  char str[] = "";
  int c = 'i';
  char* pointer1 = 0;
  char* pointer2 = 0;
  pointer1 = s21_strrchr(str, c);
  pointer2 = strrchr(str, c);
  ck_assert_pstr_eq(pointer1, pointer2);
}
END_TEST

START_TEST(test_strrchr_4) {
  char str[] =
      "Kindness is a language which the deaf can hear and the blind can see";
  int c = 'w';
  char* pointer1 = 0;
  char* pointer2 = 0;
  pointer1 = s21_strrchr(str, c);
  pointer2 = strrchr(str, c);
  ck_assert_pstr_eq(pointer1, pointer2);
}
END_TEST

START_TEST(test_strrchr_5) {
  char str[] =
      "Kindness is a language which the deaf can hear and the blind can see";
  int c = 0;
  char* pointer1 = 0;
  char* pointer2 = 0;
  pointer1 = s21_strrchr(str, c);
  pointer2 = strrchr(str, c);
  ck_assert_pstr_eq(pointer1, pointer2);
}
END_TEST

START_TEST(test_strrchr_6) {
  char str[] =
      "Kindness is a language which the deaf can hear and the blind can see";
  int c = 0;
  char* pointer1 = 0;
  char* pointer2 = 0;
  pointer1 = s21_strrchr(str, c);
  pointer2 = strrchr(str, c);
  ck_assert_pstr_eq(pointer1, pointer2);
}
END_TEST

START_TEST(test_strrchr_7) {
  char str[] =
      "Kindness is a language which the deaf can hear and the blind can see";
  int c = 255;
  char* pointer1 = 0;
  char* pointer2 = 0;
  pointer1 = s21_strrchr(str, c);
  pointer2 = strrchr(str, c);
  ck_assert_pstr_eq(pointer1, pointer2);
}
END_TEST

Suite* test_suite_strrchr() {
  Suite* suite = suite_create("s21_strrchr");
  TCase* tcase = tcase_create("s21_strrchr_case");

  tcase_add_test(tcase, test_strrchr_1);
  tcase_add_test(tcase, test_strrchr_2);
  tcase_add_test(tcase, test_strrchr_3);
  tcase_add_test(tcase, test_strrchr_4);
  tcase_add_test(tcase, test_strrchr_5);
  tcase_add_test(tcase, test_strrchr_6);
  tcase_add_test(tcase, test_strrchr_7);

  suite_add_tcase(suite, tcase);

  return suite;
}