#include "s21_tests.h"

START_TEST(test_strchr_1) {
  ck_assert_str_eq(s21_strchr("123456789", '4'), strchr("123456789", '4'));
}
END_TEST

START_TEST(test_strchr_2) {
  char testStr[] = "hihihihihi";
  ck_assert_pstr_eq(s21_strchr(testStr, 'n'), strchr(testStr, 'n'));
}
END_TEST

START_TEST(test_strchr_3) {
  ck_assert_str_eq(s21_strchr("hiohihiohihiohihio", 'o'),
                   strchr("hiohihiohihiohihio", 'o'));
}
END_TEST

START_TEST(test_strchr_4) {
  ck_assert_pstr_eq(s21_strchr("", 'a'), strchr("", 'a'));
}
END_TEST

Suite* test_suite_strchr() {
  Suite* suite = suite_create("s21_strchr");
  TCase* tcase = tcase_create("s21_strchr_case");

  tcase_add_test(tcase, test_strchr_1);
  tcase_add_test(tcase, test_strchr_2);
  tcase_add_test(tcase, test_strchr_3);
  tcase_add_test(tcase, test_strchr_4);

  suite_add_tcase(suite, tcase);

  return suite;
}