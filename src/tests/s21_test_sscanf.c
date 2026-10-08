#include "s21_tests.h"

int s21_sscanf(const char* str, const char* format, ...);

START_TEST(sscanf_basic) {
  const char* src = "42 A School21 3.1415";
  int d1 = 0, d2 = 0;
  char c1 = 0, c2 = 0;
  char s1[100] = {0}, s2[100] = {0};
  float f1 = 0.0f, f2 = 0.0f;

  int res1 = sscanf(src, "%d %c %s %f", &d1, &c1, s1, &f1);
  int res2 = s21_sscanf(src, "%d %c %s %f", &d2, &c2, s2, &f2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
  ck_assert_int_eq(c1, c2);

  int i = 0;
  while (s1[i] != '\0' || s2[i] != '\0') {
    ck_assert_int_eq(s1[i], s2[i]);
    i++;
  }

  ck_assert_float_eq_tol(f1, f2, 1e-4);
}
END_TEST

START_TEST(sscanf_limits_and_widths) {
  const char* src = "-2147483648 9223372036854775807 12345";

  int d1 = 0, d2 = 0;
  long l1 = 0, l2 = 0;
  int w1 = 0, w2 = 0;

  int res1 = sscanf(src, "%d %ld %2d", &d1, &l1, &w1);
  int res2 = s21_sscanf(src, "%d %ld %2d", &d2, &l2, &w2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
  ck_assert_int_eq(l1, l2);
  ck_assert_int_eq(w1, w2);
}
END_TEST

START_TEST(sscanf_specials) {
  const char* src = "IgnoreMe 99";
  int d1 = 0, d2 = 0;
  int n1 = 0, n2 = 0;

  int res1 = sscanf(src, "%*s %d%n", &d1, &n1);
  int res2 = s21_sscanf(src, "%*s %d%n", &d2, &n2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
  ck_assert_int_eq(n1, n2);
}
END_TEST

Suite* test_suite_sscanf(void) {
  Suite* s = suite_create("sscanf_test_suite");
  TCase* tc = tcase_create("core");

  tcase_add_test(tc, sscanf_basic);
  tcase_add_test(tc, sscanf_limits_and_widths);
  tcase_add_test(tc, sscanf_specials);
  suite_add_tcase(s, tc);

  return s;
}