#include <stdlib.h>

#include "s21_tests.h"

START_TEST(s21_to_upper_test_1) {
  char vod[] = "school 21 string to upper";
  char pol[] = "SCHOOL 21 STRING TO UPPER";
  char* program = s21_to_upper(vod);
  ck_assert_str_eq(program, pol);
  if (program) free(program);
}
END_TEST

START_TEST(s21_to_upper_test_2) {
  char vod_2[] = "lol lol";
  char pol_2[] = "LOL LOL";
  char* program_2 = s21_to_upper(vod_2);
  ck_assert_str_eq(program_2, pol_2);
  if (program_2) free(program_2);
}
END_TEST

START_TEST(s21_to_upper_test_3) {
  char vod_3[] = "more more3more";
  char pol_3[] = "MORE MORE3MORE";
  char* program_3 = s21_to_upper(vod_3);
  ck_assert_str_eq(program_3, pol_3);
  if (program_3) free(program_3);
}
END_TEST

Suite* test_suite_to_upper(void) {
  Suite* s = suite_create("s21_to_upper");
  TCase* tc_core = tcase_create("Core");

  tcase_add_test(tc_core, s21_to_upper_test_1);
  tcase_add_test(tc_core, s21_to_upper_test_2);
  tcase_add_test(tc_core, s21_to_upper_test_3);

  suite_add_tcase(s, tc_core);
  return s;
}