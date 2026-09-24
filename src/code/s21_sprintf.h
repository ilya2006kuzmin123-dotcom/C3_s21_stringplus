#ifndef S21_SPRINTF_H
#define S21_SPRINTF_H

#include <stdarg.h>

#include "../s21_string.h"

typedef struct {
  int plus;
  int minus;
  int space;
  int hash;
  int zero;
  int width;
  int precision;
  int has_precision;
  char length;
  char specifier;
} s21_sprintf_token;

s21_sprintf_token s21_init_token(void);
const char* s21_parse_token(const char* format, s21_sprintf_token* token,
                            va_list* args);
int s21_process_token(char* str, s21_sprintf_token token, va_list* argc,
                      int current_len);

#endif