#include "../s21_string.h"

void* s21_trim(const char* src, const char* trim_chars);

void* s21_trim(const char* src, const char* trim_chars) {
  char* result = S21_NULL;
  if (src && trim_chars) {
    int start = 0, end = s21_strlen(src);
    while (src[start] &&
           s21_memchr(trim_chars, src[start], s21_strlen(trim_chars))) {
      start++;
    }
    while (end > start &&
           s21_memchr(trim_chars, src[end], s21_strlen(trim_chars) + 1)) {
      end--;
    }
    result = (char*)calloc(end - start + 1, sizeof(char));
    if (result) {
      s21_strncpy(result, src + start, end - start + 1);
      result[end - start + 1] = '\0';
    }
  }
  return (void*)result;
}