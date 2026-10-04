#include "s21_sprintf.h"

s21_sprintf_token s21_init_token(void) {
  s21_sprintf_token token;
  token.minus = 0;
  token.plus = 0;
  token.space = 0;
  token.hash = 0;
  token.zero = 0;
  token.width = -1;
  token.precision = -1;
  token.has_precision = 0;
  token.length = 0;
  token.specifier = 0;
  return token;
}

const char* s21_parse_token(const char* format, s21_sprintf_token* token,
                            va_list* args) {
  const char* f = format;
  while (*f == '-' || *f == '+' || *f == ' ' || *f == '#' || *f == '0') {
    if (*f == '-') token->minus = 1;
    if (*f == '+') token->plus = 1;
    if (*f == ' ') token->space = 1;
    if (*f == '#') token->hash = 1;
    if (*f == '0') token->zero = 1;
    f++;
  }
  if (*f == '*') {
    token->width = va_arg(*args, int);
    if (token->width < 0) {
      token->minus = 1;
      token->width = -token->width;
    }
    f++;
  } else if (*f >= '0' && *f <= '9') {
    token->width = 0;
    while (*f >= '0' && *f <= '9') {
      token->width = token->width * 10 + (*f - '0');
      f++;
    }
  }
  if (*f == '.') {
    token->has_precision = 1;
    token->precision = 0;
    f++;
    if (*f == '*') {
      token->precision = va_arg(*args, int);
      if (token->precision < 0) {
        token->precision = -1;
        token->has_precision = 0;
      }
      f++;
    } else if (*f >= '0' && *f <= '9') {
      while (*f >= '0' && *f <= '9') {
        token->precision = token->precision * 10 + (*f - '0');
        f++;
      }
    }
  }
  if (*f == 'h' || *f == 'l') {
    token->length = *f;
    f++;
  }
  token->specifier = *f;
  return f;
}

int s21_parse_char(char* str, s21_sprintf_token token, va_list* args,
                   int current_len) {
  int written = 0;
  char c = (char)va_arg(*args, int);
  int padding = (token.width > 1) ? token.width - 1 : 0;
  if (!token.minus) {
    for (int i = 0; i < padding; i++) {
      str[current_len + written] = ' ';
      written++;
    }
  }
  str[current_len + written] = c;
  written++;
  if (token.minus) {
    for (int i = 0; i < padding; i++) {
      str[current_len + written] = ' ';
      written++;
    }
  }
  return written;
}

int s21_parse_string(char* str, s21_sprintf_token token, va_list* args,
                     int current_len) {
  int written = 0;
  char* s = va_arg(*args, char*);
  if (s == S21_NULL) s = "(null)";
  int s_len = (int)s21_strlen(s);
  if (token.has_precision && token.precision < s_len) {
    s_len = token.precision;
  }
  int padding = (token.width > s_len) ? token.width - s_len : 0;
  if (!token.minus) {
    for (int i = 0; i < padding; i++) {
      str[current_len + written] = ' ';
      written++;
    }
  }
  for (int i = 0; i < s_len; i++) {
    str[current_len + written] = s[i];
    written++;
  }
  if (token.minus) {
    for (int i = 0; i < padding; i++) {
      str[current_len + written] = ' ';
      written++;
    }
  }
  return written;
}

s21_parse_int(char* str, s21_sprintf_token token, va_list* args,
              int current_len) {
  int written = 0;
  long val = 0;
  if (token.length == 'l')
    val = va_arg(*args, long);
  else if (token.length == 'h')
    val = (short)va_arg(*args, int);
  else
    val = va_arg(*args, int);
  char tmp[128] = {0};
  int tmp_len = 0;
  int is_zero = (val == 0);
  unsigned long uval = (val < 0) ? (unsigned long)(-val) : (unsigned long)val;
  if (!(is_zero && token.has_precision && token.precision == 0)) {
    if (uval == 0) tmp[tmp_len++] = '0';
    while (uval > 0) {
      tmp[tmp_len++] = (uval % 10) + '0';
      uval /= 10;
    }
    int start = 0;
    int end = tmp_len - 1;
    while (start < end) {
      char tmp_char = tmp[start];
      tmp[start] = tmp[end];
      tmp[end] = tmp_char;
      start++;
      end--;
    }
  }
  if (token.has_precision && token.precision > tmp_len) {
    int zeros_to_add = token.precision - tmp_len;
    for (int i = tmp_len - 1; i >= 0; i--) tmp[i + zeros_to_add] = tmp[i];
    for (int i = 0; i < zeros_to_add; i++) tmp[i] = '0';
    tmp_len = token.precision;
  }
  char sign = 0;
  if (val < 0)
    sign = '-';
  else if (token.plus)
    sign = '+';
  else if (token.space)
    sign = ' ';
  int total_len = tmp_len + (sign != 0 ? 1 : 0);
  int padding = (token.width > total_len) ? (token.width - total_len) : 0;
  char pad_char = ' ';
  if (token.zero && !token.minus && !token.has_precision) pad_char = '0';
  if (token.minus) {
    if (sign != 0) {
      str[current_len + written] = sign;
      written++;
    }
    for (int i = 0; i < tmp_len; i++) {
      str[current_len + written] = tmp[i];
      written++;
    }
    for (int i = 0; i < padding; i++) {
      str[current_len + written] = ' ';
      written++;
    }
  } else if (pad_char == '0') {
    if (sign != 0) {
      str[current_len + written] = sign;
      written++;
    }
    for (int i = 0; i < padding; i++) {
      str[current_len + written] = '0';
      written++;
    }
    for (int i = 0; i < tmp_len; i++) {
      str[current_len + written] = tmp[i];
      written++;
    }
  } else {
    for (int i = 0; i < padding; i++) {
      str[current_len + written] = ' ';
      written++;
    }
    if (sign != 0) {
      str[current_len + written] = sign;
      written++;
    }
    for (int i = 0; i < tmp_len; i++) {
      str[current_len + written] = tmp[i];
      written++;
    }
  }
  return written;
}

int s21_parse_unsigned(char* str, s21_sprintf_token token, va_list* args,
                       int current_len) {
  int written = 0;
  unsigned long val = 0;
  if (token.length == 'l')
    val = va_arg(*args, unsigned long);
  else if (token.length == 'h')
    val = (unsigned short)va_arg(*args, unsigned int);
  else
    val = va_arg(*args, unsigned int);
  char tmp[128] = {0};
  int tmp_len = 0;
  int is_zero = (val == 0);
  if (!(is_zero && token.has_precision && token.precision == 0)) {
    if (val == 0) tmp[tmp_len++] = '0';
    while (val > 0) {
      tmp[tmp_len++] = (val % 10) + '0';
      val /= 10;
    }
    int start = 0;
    int end = tmp_len - 1;
    while (start < end) {
      char tmp_char = tmp[start];
      tmp[start] = tmp[end];
      tmp[end] = tmp_char;
      start++;
      end--;
    }
  }
  if (token.has_precision && token.precision > tmp_len) {
    int zeros_to_add = token.precision - tmp_len;
    for (int i = tmp_len - 1; i >= 0; i--) tmp[i + zeros_to_add] = tmp[i];
    for (int i = 0; i < zeros_to_add; i++) tmp[i] = '0';
    tmp_len = token.precision;
  }
  int total_len = tmp_len;
  int padding = (token.width > total_len) ? (token.width - total_len) : 0;
  char pad_char = ' ';
  if (token.zero && !token.minus && !token.has_precision) pad_char = '0';
  if (token.minus) {
    for (int i = 0; i < tmp_len; i++) {
      str[current_len + written] = tmp[i];
      written++;
    }
    for (int i = 0; i < padding; i++) {
      str[current_len + written] = ' ';
      written++;
    }
  } else {
    for (int i = 0; i < padding; i++) {
      str[current_len + written] = pad_char;
      written++;
    }
    for (int i = 0; i < tmp_len; i++) {
      str[current_len + written] = tmp[i];
      written++;
    }
  }
  return written;
}

int s21_parse_float(char* str, s21_sprintf_token token, va_list* args,
                    int current_len) {
  int written = 0;
  long double val = 0;
  if (token.length == 'L')
    val = va_arg(*args, long double);
  else
    val = va_arg(*args, double);
  int prec = (token.has_precision) ? token.precision : 6;
  int negative = signbit(val);
  if (negative) val = -val;
  long double round_offset = 0.5;
  for (int i = 0; i < prec; i++) round_offset /= 10.0;
  val += round_offset;
  long long int_part = (long long)val;
  long double frac_part = val - (long double)int_part;
  char tmp[256] = {0};
  int tmp_len = 0;
  int start_int_idx = tmp_len;
  if (int_part == 0) tmp[tmp_len++] = '0';
  while (int_part > 0) {
    tmp[tmp_len++] = (int_part % 10) + '0';
    int_part /= 10;
  }
  int start = start_int_idx;
  int end = tmp_len - 1;
  while (start < end) {
    char temp_char = tmp[start];
    tmp[start] = tmp[end];
    tmp[end] = temp_char;
    start++;
    end--;
  }
  if (prec > 0 || token.hash) tmp[tmp_len++] = '.';
  for (int i = 0; i < prec; i++) {
    frac_part *= 10.0;
    int digit = (int)frac_part;
    tmp[tmp_len++] = digit + '0';
    frac_part -= digit;
  }
  char sign = 0;
  if (negative)
    sign = '-';
  else if (token.plus)
    sign = '+';
  else if (token.space)
    sign = ' ';
  int total_len = tmp_len + (sign != 0 ? 1 : 0);
  int padding = (token.width > total_len) ? (token.width - total_len) : 0;
  char pad_char = ' ';
  if (token.zero && !token.minus) pad_char = '0';
  if (token.minus) {
    if (sign != 0) {
      str[current_len + written] = sign;
      written++;
    }
    for (int i = 0; i < tmp_len; i++) {
      str[current_len + written] = tmp[i];
      written++;
    }
    for (int i = 0; i < padding; i++) {
      str[current_len + written] = ' ';
      written++;
    }
  } else if (pad_char == '0') {
    if (sign != 0) {
      str[current_len + written] = sign;
      written++;
    }
    for (int i = 0; i < padding; i++) {
      str[current_len + written] = '0';
      written++;
    }
    for (int i = 0; i < tmp_len; i++) {
      str[current_len + written] = tmp[i];
      written++;
    }
  } else {
    for (int i = 0; i < padding; i++) {
      str[current_len + written] = ' ';
      written++;
    }
    if (sign != 0) {
      str[current_len + written] = sign;
      written++;
    }
    for (int i = 0; i < tmp_len; i++) {
      str[current_len + written] = tmp[i];
      written++;
    }
  }
  return written;
}

int s21_process_token(char* str, s21_sprintf_token token, va_list* args,
                      int current_len) {
  int written = 0;
  switch (token.specifier) {
    case '%':
      str[current_len] = '%';
      written = 1;
      break;
    case 'c':
      written = s21_parse_char(str, token, args, current_len);
      break;
    case 'd':
    case 'i':
      written = s21_parse_int(str, token, args, current_len);
      break;
    case 's':
      written = s21_parse_string(str, token, args, current_len);
      break;
    case 'u':
      written = s21_parse_unsigned(str, token, args, current_len);
      break;
    case 'f':
      written = s21_parse_float(str, token, args, current_len);
      break;
    default:
      break;
  }
  return written;
}

int s21_sprintf(char* str, const char* format, ...) {
  s21_size str_len = 0;
  const char* f = format;
  va_list args;
  va_start(args, format);
  while (*f != '\0') {
    if (*f != '%') {
      str[str_len] = *f;
      str_len++;
      f++;
    } else {
      f++;
      s21_sprintf_token token = s21_init_token();
      f = s21_parse_token(f, &token, &args);
      int written = s21_process_token(str, token, &args, (int)str_len);
      str_len += written;
      f++;
    }
  }
  str[str_len] = '\0';
  va_end(args);
  return (int)str_len;
}