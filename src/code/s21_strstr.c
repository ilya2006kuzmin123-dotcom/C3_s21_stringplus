#include "../s21_string.h"

char* s21_strstr(const char* haystack, const char* needle) {
  char* ans = S21_NULL;
  int len_src = s21_strlen(haystack);
  int len_search = s21_strlen(needle);
  for (int i = 0; i <= len_src - len_search && !ans; i++) {
    int flag = 1;
    for (int j = 0; j < len_search && flag; j++) {
      if (haystack[i + j] != needle[j]) {
        flag = 0;
      }
    }
    if (flag) {
      ans = (char*)&haystack[i];
    }
  }
  return ans;
}