#include "../s21_string.h"

void* s21_memchr(const void* str, int c, s21_size n) {
  const unsigned char* ptr = str;
  for (s21_size i = 0; i < n; i++) {
    if (ptr[i] == (unsigned char)c) return (void*)(ptr + i);
  }
  return S21_NULL;
}