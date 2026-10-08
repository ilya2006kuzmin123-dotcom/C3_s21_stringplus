#ifndef S21_TESTS_H
#define S21_TESTS_H

#include <check.h>
#include <limits.h>
#include <stdio.h>

#include "../s21_string.h"

Suite *test_suite_strlen();
Suite *test_suite_memchr();
Suite *test_suite_memcpy();
Suite *test_suite_strncat();
Suite *test_suite_strncmp();
Suite *test_suite_strcspn();
Suite *test_suite_strpbrk();
Suite *test_suite_strtok();
Suite *test_suite_trim();
Suite *test_suite_memcmp();
Suite *test_suite_memset();
Suite *test_suite_strchr();
Suite *test_suite_strncpy();
Suite *test_suite_strerror();
Suite *test_suite_strrchr();
Suite *test_suite_strstr();
Suite *test_suite_to_lower();
Suite *test_suite_to_upper();
Suite *test_suite_insert();
Suite *test_suite_sprintf();
Suite *test_suite_sscanf();

#endif