#include "s21_tests.h"

int main() {
  int numberFailed = 0;
  SRunner* sr = srunner_create(NULL);

  srunner_add_suite(sr, test_suite_strlen());
  srunner_add_suite(sr, test_suite_memchr());
  srunner_add_suite(sr, test_suite_memcpy());
  srunner_add_suite(sr, test_suite_strncat());
  srunner_add_suite(sr, test_suite_strncmp());
  srunner_add_suite(sr, test_suite_strcspn());
  srunner_add_suite(sr, test_suite_strpbrk());
  srunner_add_suite(sr, test_suite_strtok());
  srunner_add_suite(sr, test_suite_to_lower());
  srunner_add_suite(sr, test_suite_to_upper());
  srunner_add_suite(sr, test_suite_memcmp());
  srunner_add_suite(sr, test_suite_memset());
  srunner_add_suite(sr, test_suite_strchr());
  srunner_add_suite(sr, test_suite_strncpy());
  srunner_add_suite(sr, test_suite_strerror());
  srunner_add_suite(sr, test_suite_strrchr());
  srunner_add_suite(sr, test_suite_strstr());
  srunner_add_suite(sr, test_suite_trim());
  srunner_add_suite(sr, test_suite_insert());

  srunner_run_all(sr, CK_NORMAL);

  numberFailed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return !numberFailed ? 0 : 1;
}