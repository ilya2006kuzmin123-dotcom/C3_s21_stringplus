#include "s21_tests.h"

int s21_sprintf(char* str, const char* format, ...);

START_TEST(sprintf_basic) {
  char buf1[200] = {0};
  char buf2[200] = {0};
  char c = 'Z';
  const char* str = "21School";

  int res1 = sprintf(buf1, "Char: %c, Percent: %%, String: %s", c, str);
  int res2 = my_sprintf(buf2, "Char: %c, Percent: %%, String: %s", c, str);

  ck_assert_int_eq(res1, res2);

  int i = 0;
  while (buf1[i] != '\0' || buf2[i] != '\0') {
    ck_assert_int_eq(buf1[i], buf2[i]);
    i++;
  }
}
END_TEST

START_TEST(sprintf_limits) {
  char buf1[200] = {0};
  char buf2[200] = {0};
  int min_int = INT_MIN;
  unsigned int max_uint = UINT_MAX;

  int res1 = sprintf(buf1, "Min: %d, MaxU: %u", min_int, max_uint);
  int res2 = my_sprintf(buf2, "Min: %d, MaxU: %u", min_int, max_uint);

  ck_assert_int_eq(res1, res2);

  int i = 0;
  while (buf1[i] != '\0' || buf2[i] != '\0') {
    ck_assert_int_eq(buf1[i], buf2[i]);
    i++;
  }
}
END_TEST

START_TEST(sprintf_floats) {
  char buf1[200] = {0};
  char buf2[200] = {0};
  double f1 = 0.123456;
  double f2 = -987.654321;

  int res1 = sprintf(buf1, "Float1: %f, Float2: %f", f1, f2);
  int res2 = my_sprintf(buf2, "Float1: %f, Float2: %f", f1, f2);

  ck_assert_int_eq(res1, res2);

  int i = 0;
  while (buf1[i] != '\0' || buf2[i] != '\0') {
    ck_assert_int_eq(buf1[i], buf2[i]);
    i++;
  }
}
END_TEST

Suite* sprintf_suite(void) {
  Suite* s = suite_create("sprintf_test_suite");
  TCase* tc = tcase_create("core");

  tcase_add_test(tc, sprintf_basic);
  tcase_add_test(tc, sprintf_limits);
  tcase_add_test(tc, sprintf_floats);
  suite_add_tcase(s, tc);

  return s;
}