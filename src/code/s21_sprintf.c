#include "s21_sprintf.h"

s21_sprintf_token s21_init_token(void) {}

const char* s21_parse_token(const char* format, s21_sprintf_token* token,
                            va_list* args) {}

int s21_process_token(char* str, s21_sprintf_token token, va_list* args,
                      int current_len) {}

int s21_sprintf(char* str, const char* format, ...) {
  va_list args;
  va_start(args, format);
  s21_size str_len = 0;
  while (*format != '\0') {
    if (*format != '%') {
      str[str_len] = *format;
      str_len++;
    } else {
      format++;
      s21_sprintf_token token = s21_init_token();
      format = s21_parse_token(format, &token, &args);
      int written = s21_process_token(str, token, &args, str_len);
      str_len += written;
    }
    format++;
    str[str_len] = '\0';
    va_end(args);
    return (int)str_len;
  }
}