#include "../s21_string.h"

char* s21_strrchr(const char* str, int c) {
  char* pointer = S21_NULL;
  if (str != S21_NULL) {
    for (s21_size i = 0; i < s21_strlen(str) + 1; i++) {
      if (str[i] == c) pointer = (char*)str + i;
    }
  }
  return pointer;
}