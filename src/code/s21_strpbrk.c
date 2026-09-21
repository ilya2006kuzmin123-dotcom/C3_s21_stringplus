#include "../s21_string.h"

char* s21_strpbrk(const char* str1, const char* str2) {
  char* result = S21_NULL;

  if (str1 != S21_NULL && str2 != S21_NULL) {
    s21_size index = s21_strcspn(str1, str2);
    if (str1[index] != '\0') {
      result = (char*)str1 + index;
    }
  }

  return result;
}