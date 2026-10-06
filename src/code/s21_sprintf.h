#ifndef S21_SPRINTF_H
#define S21_SPRINTF_H

#include <math.h>
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
int s21_process_token(char* str, s21_sprintf_token token, va_list* args,
                      int current_len);
int s21_parse_char(char* str, s21_sprintf_token token, va_list* args,
                   int current_len);
int s21_parse_string(char* str, s21_sprintf_token token, va_list* args,
                     int current_len);
int s21_parse_int(char* str, s21_sprintf_token token, va_list* args,
                  int current_len);
int s21_parse_unsigned(char* str, s21_sprintf_token token, va_list* args,
                       int current_len);
int s21_parse_float(char* str, s21_sprintf_token token, va_list* args,
                    int current_len, int is_g);
int s21_parse_hex(char* str, s21_sprintf_token token, va_list* args,
                  int current_len);
int s21_parse_octal(char* str, s21_sprintf_token token, va_list* args,
                    int current_len);
int s21_parse_pointer(char* str, s21_sprintf_token token, va_list* args,
                      int current_len);
int s21_parse_exponent(char* str, s21_sprintf_token token, va_list* args,
                       int current_len, int is_g);
int s21_parse_g(char* str, s21_sprintf_token token, va_list* args,
                int current_len);
int s21_apply_width(char* str, const char* tmp, int tmp_len, char sign,
                    s21_sprintf_token token, int current_len);
void s21_reverse(char* tmp, int tmp_len);
void s21_assemble_mantissa(char* tmp, int* tmp_len, long double val, int prec,
                           int is_g, s21_sprintf_token token);
const char* s21_parse_atoi(const char* f, int* res);
int s21_get_exp(long double val);
#endif