#include "../s21_string.h"

char* s21_strtok(char* str, const char* delim) {
  static char* olds = S21_NULL;
  char* token = S21_NULL;

  if (str != S21_NULL) {
    olds = str;
  }

  if (olds != S21_NULL && *olds != '\0') {
    olds += s21_strspn(olds, delim);

    if (*olds != '\0') {
      token = olds;
      olds = s21_strpbrk(token, delim);

      if (olds != S21_NULL) {
        *olds = '\0';
        olds++;
      }
    }
  }

  return token;
}