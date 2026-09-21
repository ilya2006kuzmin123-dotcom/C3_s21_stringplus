#include "../s21_string.h"

char* s21_strchr(const char* str, int c) {
  char* result = S21_NULL;
  for (s21_size i = 0; result == S21_NULL && (i == 0 || str[i - 1] != '\0');
       i++) {
    if (str[i] == (char)c) result = (char*)(str + i);
  }
  return result;
}