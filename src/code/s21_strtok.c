#include "../s21_string.h"

char* s21_strtok(char* str, const char* delim) {
  static char* olds = S21_NULL;
  char* token = S21_NULL;

  if (str != S21_NULL) {
    olds = str;
  }

  if (olds != S21_NULL && *olds != '\0') {
    while (*olds != '\0') {
      int is_delim = 0;
      for (int i = 0; delim[i] != '\0'; i++) {
        if (*olds == delim[i]) {
          is_delim = 1;
          break;
        }
      }
      if (!is_delim) break;
      olds++;
    }

    if (*olds != '\0') {
      token = olds;

      while (*olds != '\0') {
        int is_delim = 0;
        for (int i = 0; delim[i] != '\0'; i++) {
          if (*olds == delim[i]) {
            is_delim = 1;
            break;
          }
        }
        if (is_delim) {
          *olds = '\0';
          olds++;
          return token;
        }
        olds++;
      }
    }
  }

  return token;
}