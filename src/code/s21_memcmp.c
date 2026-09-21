#include "../s21_string.h"

int s21_memcmp(const void* str1, const void* str2, s21_size n) {
  int result = 0;
  const unsigned char* ptr1 = str1;
  const unsigned char* ptr2 = str2;
  for (s21_size i = 0; i < n && result == 0; i++) {
    if (ptr1[i] != ptr2[i]) result = ptr1[i] - ptr2[i];
  }
  return result;
}