#include "../s21_string.h"

void* s21_to_upper(const char* str) {
  char* address = S21_NULL;

  if (str != S21_NULL) {
    s21_size strle = s21_strlen(str);
    address = (char*)calloc(strle + 1, sizeof(char));

    if (address != S21_NULL) {
      for (s21_size i = 0; i < strle; i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
          address[i] = str[i] - ('a' - 'A');
        } else {
          address[i] = str[i];
        }
      }
    }
  }

  return (void*)address;
}