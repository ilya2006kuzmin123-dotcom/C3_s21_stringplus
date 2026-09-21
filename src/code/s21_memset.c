#include "../s21_string.h"

void* s21_memset(void* str, int c, s21_size n) {
  unsigned char* s = str;
  unsigned char c_0 = c;
  for (s21_size i = 0; i < n; i++) s[i] = c_0;
  return str;
}