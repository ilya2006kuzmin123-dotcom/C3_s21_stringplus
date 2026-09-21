#include "../s21_string.h"

char* s21_strncat(char* dest, const char* src, s21_size n) {
  s21_size dest_len = s21_strlen(dest);
  s21_size i = 0;
  for (; i < n && src[i] != '\0'; i++) {
    dest[dest_len + i] = src[i];
  }
  dest[dest_len + i] = '\0';
  return dest;
}