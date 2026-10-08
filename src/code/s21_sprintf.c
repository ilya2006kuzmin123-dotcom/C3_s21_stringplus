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

const char* s21_parse_atoi(const char* f, int* res) {
  *res = 0;
  while (*f >= '0' && *f <= '9') {
    *res = *res * 10 + (*f - '0');
    f++;
  }
  return f;
}

const char* s21_parse_token(const char* format, s21_sprintf_token* token,
                            va_list* args) {
  const char* f = format;
  while (*f == '-' || *f == '+' || *f == ' ' || *f == '#' || *f == '0') {
    token->minus = (*f == '-') ? 1 : token->minus;
    token->plus = (*f == '+') ? 1 : token->plus;
    token->space = (*f == ' ') ? 1 : token->space;
    token->hash = (*f == '#') ? 1 : token->hash;
    token->zero = (*f == '0') ? 1 : token->zero;
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
    f = s21_parse_atoi(f, &token->width);
  }
  if (*f == '.') {
    token->has_precision = 1;
    f++;
    if (*f == '*') {
      token->precision = va_arg(*args, int);
      if (token->precision < 0) {
        token->precision = -1;
        token->has_precision = 0;
      }
      f++;
    } else {
      f = s21_parse_atoi(f, &token->precision);
    }
  }
  if (*f == 'h' || *f == 'l' || *f == 'L') token->length = *f++;
  token->specifier = *f;
  return f;
}

int s21_apply_width(char* str, const char* tmp, int tmp_len, char sign,
                    s21_sprintf_token token, int current_len) {
  int wr = 0, total = tmp_len + (sign != 0 ? 1 : 0);
  int pad = (token.width > total) ? (token.width - total) : 0;
  char p_ch = (token.zero && !token.minus && !token.has_precision) ? '0' : ' ';
  if (token.specifier == 'f' || token.specifier == 'e' ||
      token.specifier == 'E') {
    if (token.zero && !token.minus) p_ch = '0';
  }
  if (token.minus) {
    if (sign) str[current_len + wr++] = sign;
    for (int i = 0; i < tmp_len; i++) str[current_len + wr++] = tmp[i];
    for (int i = 0; i < pad; i++) str[current_len + wr++] = ' ';
  } else if (p_ch == '0') {
    if (sign) str[current_len + wr++] = sign;
    int start_idx = 0;
    if (tmp_len >= 2 && tmp[0] == '0' && (tmp[1] == 'x' || tmp[1] == 'X')) {
      str[current_len + wr++] = tmp[0];
      str[current_len + wr++] = tmp[1];
      start_idx = 2;
    } else if (tmp_len >= 1 && tmp[0] == '0' && token.specifier == 'o') {
      str[current_len + wr++] = tmp[0];
      start_idx = 1;
    }
    for (int i = 0; i < pad; i++) str[current_len + wr++] = '0';
    for (int i = start_idx; i < tmp_len; i++) str[current_len + wr++] = tmp[i];
  } else {
    for (int i = 0; i < pad; i++) str[current_len + wr++] = ' ';
    if (sign) str[current_len + wr++] = sign;
    for (int i = 0; i < tmp_len; i++) str[current_len + wr++] = tmp[i];
  }
  return wr;
}

void s21_reverse(char* tmp, int tmp_len) {
  int start = 0, end = tmp_len - 1;
  while (start < end) {
    char ch = tmp[start];
    tmp[start] = tmp[end];
    tmp[end] = ch;
    start++;
    end--;
  }
}

void s21_assemble_mantissa(char* tmp, int* tmp_len, long double val, int prec,
                           int is_g, s21_sprintf_token token) {
  long long int_part = (long long)val;
  long double frac_part = val - (long double)int_part;

  if (int_part == 0) tmp[(*tmp_len)++] = '0';
  while (int_part > 0) {
    tmp[(*tmp_len)++] = (int_part % 10) + '0';
    int_part /= 10;
  }
  s21_reverse(tmp, *tmp_len);

  if (prec > 0 || token.hash) tmp[(*tmp_len)++] = '.';
  for (int i = 0; i < prec; i++) {
    frac_part *= 10.0;
    int digit = (int)frac_part;
    tmp[(*tmp_len)++] = digit + '0';
    frac_part -= (long double)digit;
  }

  if (is_g && !token.hash && *tmp_len > 0) {
    int has_dot = 0;
    for (int i = 0; i < *tmp_len; i++) {
      if (tmp[i] == '.') has_dot = 1;
    }
    while (has_dot && *tmp_len > 0 && tmp[*tmp_len - 1] == '0') {
      tmp[--(*tmp_len)] = '\0';
    }
    if (has_dot && *tmp_len > 0 && tmp[*tmp_len - 1] == '.') {
      tmp[--(*tmp_len)] = '\0';
    }
  }
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
  char* s = va_arg(*args, char*);
  char tmp[4096] = {0};
  int s_len = 0;
  if (s == S21_NULL) s = "(null)";
  s_len = (int)s21_strlen(s);
  if (token.has_precision && token.precision >= 0 && token.precision < s_len) {
    s_len = token.precision;
  }
  for (int i = 0; i < s_len; i++) tmp[i] = s[i];
  return s21_apply_width(str, tmp, s_len, 0, token, current_len);
}

int s21_parse_int(char* str, s21_sprintf_token token, va_list* args,
                  int current_len) {
  long val = (token.length == 'l')   ? va_arg(*args, long)
             : (token.length == 'h') ? (short)va_arg(*args, int)
                                     : va_arg(*args, int);
  char tmp[128] = {0};
  int tmp_len = 0, is_zero = (val == 0);
  unsigned long uval = (val < 0) ? (unsigned long)(-val) : (unsigned long)val;
  if (!(is_zero && token.has_precision && token.precision == 0)) {
    if (uval == 0) tmp[tmp_len++] = '0';
    while (uval > 0) {
      tmp[tmp_len++] = (uval % 10) + '0';
      uval /= 10;
    }
    s21_reverse(tmp, tmp_len);
  }
  if (token.has_precision && token.precision > tmp_len) {
    int zeros_to_add = token.precision - tmp_len;
    for (int i = tmp_len - 1; i >= 0; i--) tmp[i + zeros_to_add] = tmp[i];
    for (int i = 0; i < zeros_to_add; i++) tmp[i] = '0';
    tmp_len = token.precision;
  }
  char sign = (val < 0) ? '-' : (token.plus) ? '+' : (token.space) ? ' ' : 0;
  return s21_apply_width(str, tmp, tmp_len, sign, token, current_len);
}

int s21_parse_unsigned(char* str, s21_sprintf_token token, va_list* args,
                       int current_len) {
  unsigned long val = (token.length == 'l') ? va_arg(*args, unsigned long)
                      : (token.length == 'h')
                          ? (unsigned short)va_arg(*args, unsigned int)
                          : va_arg(*args, unsigned int);
  char tmp[128] = {0};
  int tmp_len = 0, is_zero = (val == 0);
  if (!(is_zero && token.has_precision && token.precision == 0)) {
    if (val == 0) tmp[tmp_len++] = '0';
    while (val > 0) {
      tmp[tmp_len++] = (val % 10) + '0';
      val /= 10;
    }
    s21_reverse(tmp, tmp_len);
  }
  if (token.has_precision && token.precision > tmp_len) {
    int zeros_to_add = token.precision - tmp_len;
    for (int i = tmp_len - 1; i >= 0; i--) tmp[i + zeros_to_add] = tmp[i];
    for (int i = 0; i < zeros_to_add; i++) tmp[i] = '0';
    tmp_len = token.precision;
  }
  return s21_apply_width(str, tmp, tmp_len, 0, token, current_len);
}

int s21_parse_float(char* str, s21_sprintf_token token, va_list* args,
                    int current_len, int is_g) {
  int tmp_len = 0;
  long double val = (token.length == 'L') ? va_arg(*args, long double)
                                          : va_arg(*args, double);
  int prec = (token.has_precision) ? token.precision : 6;
  int negative = !!signbit(val);
  if (negative) val = -val;
  if (!is_g) {
    long double round_offset = 0.5;
    for (int i = 0; i < prec; i++) round_offset /= 10.0;
    val += round_offset;
  }
  long long int_part = (long long)val;
  long double frac_part = val - (long double)int_part;
  char tmp[256] = {0};
  if (int_part == 0) tmp[tmp_len++] = '0';
  while (int_part > 0) {
    tmp[tmp_len++] = (int_part % 10) + '0';
    int_part /= 10;
  }
  s21_reverse(tmp, tmp_len);
  if (prec > 0 || token.hash) tmp[tmp_len++] = '.';
  for (int i = 0; i < prec; i++) {
    frac_part *= 10.0;
    int digit = (int)frac_part;
    tmp[tmp_len++] = digit + '0';
    frac_part -= (long double)digit;
  }
  if (is_g && !token.hash && tmp_len > 0) {
    int has_dot = 0;
    for (int i = 0; i < tmp_len; i++)
      if (tmp[i] == '.') has_dot = 1;
    while (has_dot && tmp_len > 0 && tmp[tmp_len - 1] == '0')
      tmp[--tmp_len] = '\0';
    if (has_dot && tmp_len > 0 && tmp[tmp_len - 1] == '.')
      tmp[--tmp_len] = '\0';
  }
  char sign = (negative) ? '-' : (token.plus) ? '+' : (token.space) ? ' ' : 0;
  return s21_apply_width(str, tmp, tmp_len, sign, token, current_len);
}

int s21_parse_hex(char* str, s21_sprintf_token token, va_list* args,
                  int current_len) {
  unsigned long val = (token.length == 'l') ? va_arg(*args, unsigned long)
                      : (token.length == 'h')
                          ? (unsigned short)va_arg(*args, unsigned int)
                          : va_arg(*args, unsigned int);
  char tmp[128] = {0};
  int tmp_len = 0, is_zero = (val == 0);
  if (!(is_zero && token.has_precision && token.precision == 0)) {
    if (val == 0) tmp[tmp_len++] = '0';
    while (val > 0) {
      int rem = val % 16;
      if (rem < 10) {
        tmp[tmp_len++] = rem + '0';
      } else {
        char base_char = (token.specifier == 'X') ? 'A' : 'a';
        tmp[tmp_len++] = (rem - 10) + base_char;
      }
      val /= 16;
    }
    s21_reverse(tmp, tmp_len);
  }
  if (token.has_precision && token.precision > tmp_len) {
    int zeros_to_add = token.precision - tmp_len;
    for (int i = tmp_len - 1; i >= 0; i--) tmp[i + zeros_to_add] = tmp[i];
    for (int i = 0; i < zeros_to_add; i++) tmp[i] = '0';
    tmp_len = token.precision;
  }
  if (token.hash && !is_zero) {
    for (int i = tmp_len - 1; i >= 0; i--) tmp[i + 2] = tmp[i];
    tmp[0] = '0';
    tmp[1] = (token.specifier == 'X') ? 'X' : 'x';
    tmp_len += 2;
  }
  return s21_apply_width(str, tmp, tmp_len, 0, token, current_len);
}

int s21_parse_octal(char* str, s21_sprintf_token token, va_list* args,
                    int current_len) {
  unsigned long val = (token.length == 'l') ? va_arg(*args, unsigned long)
                      : (token.length == 'h')
                          ? (unsigned short)va_arg(*args, unsigned int)
                          : va_arg(*args, unsigned int);
  char tmp[128] = {0};
  int tmp_len = 0, is_zero = (val == 0);
  if (!(is_zero && token.has_precision && token.precision == 0)) {
    if (val == 0) tmp[tmp_len++] = '0';
    while (val > 0) {
      int rem = val % 8;
      tmp[tmp_len++] = rem + '0';
      val /= 8;
    }
    s21_reverse(tmp, tmp_len);
  }
  if (token.has_precision && token.precision > tmp_len) {
    int zeros_to_add = token.precision - tmp_len;
    for (int i = tmp_len - 1; i >= 0; i--) tmp[i + zeros_to_add] = tmp[i];
    for (int i = 0; i < zeros_to_add; i++) tmp[i] = '0';
    tmp_len = token.precision;
  }
  if (token.hash && (tmp_len == 0 || tmp[0] != '0')) {
    for (int i = tmp_len - 1; i >= 0; i--) tmp[i + 1] = tmp[i];
    tmp[0] = '0';
    tmp_len += 1;
  }
  return s21_apply_width(str, tmp, tmp_len, 0, token, current_len);
}

int s21_parse_pointer(char* str, s21_sprintf_token token, va_list* args,
                      int current_len) {
  int tmp_len = 0;
  void* ptr = va_arg(*args, void*);
  unsigned long long val = (unsigned long long)ptr;
  char tmp[128] = {0};
  int is_zero = (val == 0);
  (void)is_zero;
#if defined(__linux__)
  if (is_zero) {
    tmp[0] = '(';
    tmp[1] = 'n';
    tmp[2] = 'i';
    tmp[3] = 'l';
    tmp[4] = ')';
    tmp_len = 5;
  }
#endif
  if (tmp_len == 0) {
    if (!(is_zero && token.has_precision && token.precision == 0)) {
      if (val == 0) tmp[tmp_len++] = '0';
      while (val > 0) {
        int rem = val % 16;
        tmp[tmp_len++] = (rem < 10) ? rem + '0' : (rem - 10) + 'a';
        val /= 16;
      }
      s21_reverse(tmp, tmp_len);
    }
    if (token.has_precision && token.precision > tmp_len) {
      int zeros_to_add = token.precision - tmp_len;
      for (int i = tmp_len - 1; i >= 0; i--) tmp[i + zeros_to_add] = tmp[i];
      for (int i = 0; i < zeros_to_add; i++) tmp[i] = '0';
      tmp_len = token.precision;
    }
    for (int i = tmp_len - 1; i >= 0; i--) tmp[i + 2] = tmp[i];
    tmp[0] = '0';
    tmp[1] = 'x';
    tmp_len += 2;
  }
  return s21_apply_width(str, tmp, tmp_len, 0, token, current_len);
}

int s21_parse_exponent(char* str, s21_sprintf_token token, va_list* args,
                       int current_len, int is_g) {
  int tmp_len = 0, exp = 0;
  long double val = (token.length == 'L') ? va_arg(*args, long double)
                                          : va_arg(*args, double);
  int prec = (token.has_precision) ? token.precision : 6;
  int negative = signbit(val);
  if (negative) val = -val;
  if (val > 0.0) {
    while (val >= 10.0) {
      val /= 10.0;
      exp++;
    }
    while (val < 1.0) {
      val *= 10.0;
      exp--;
    }
    if (!is_g) {
      long double offset = 0.5;
      for (int i = 0; i < prec; i++) offset /= 10.0;
      val += offset;
      if (val >= 10.0) {
        val /= 10.0;
        exp++;
      }
    }
  }
  char tmp[256] = {0};
  s21_assemble_mantissa(tmp, &tmp_len, val, prec, is_g, token);
  tmp[tmp_len++] = token.specifier;
  tmp[tmp_len++] = (exp >= 0) ? '+' : '-';
  int abs_exp = (exp < 0) ? -exp : exp;
  tmp[tmp_len++] = (abs_exp / 10) + '0';
  tmp[tmp_len++] = (abs_exp % 10) + '0';
  char sign = (negative) ? '-' : (token.plus) ? '+' : (token.space) ? ' ' : 0;
  return s21_apply_width(str, tmp, tmp_len, sign, token, current_len);
}

int s21_get_exp(long double val) {
  int exp = 0;
  if (val > 0.0) {
    while (val >= 10.0) {
      val /= 10.0;
      exp++;
    }
    while (val < 1.0) {
      val *= 10.0;
      exp--;
    }
  }
  return exp;
}

int s21_parse_g(char* str, s21_sprintf_token token, va_list* args,
                int current_len) {
  int written = 0;
  va_list args_copy;
  va_copy(args_copy, *args);
  long double val = 0;
  if (token.length == 'L')
    val = va_arg(args_copy, long double);
  else
    val = va_arg(args_copy, double);
  va_end(args_copy);
  if (val < 0) val = -val;
  int prec = (token.has_precision) ? token.precision : 6;
  if (prec == 0) prec = 1;
  int temp_exp = s21_get_exp(val);
  int round_prec = prec - (temp_exp + 1);
  if (val > 0.0) {
    long double round_offset = 0.5;
    if (round_prec >= 0) {
      for (int i = 0; i < round_prec; i++) round_offset /= 10.0;
    } else {
      for (int i = 0; i < -round_prec; i++) round_offset *= 10.0;
    }
    val += round_offset;
  }
  int exp = s21_get_exp(val);
  if (exp < -4 || exp >= prec) {
    token.specifier = (token.specifier == 'G') ? 'E' : 'e';
    token.precision = prec - 1;
    if (token.precision < 0) token.precision = 0;
    written = s21_parse_exponent(str, token, args, current_len, 1);
  } else {
    token.specifier = 'f';
    token.precision = prec - (exp + 1);
    if (token.precision < 0) token.precision = 0;
    written = s21_parse_float(str, token, args, current_len, 1);
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
      written = s21_parse_float(str, token, args, current_len, 0);
      break;
    case 'x':
    case 'X':
      written = s21_parse_hex(str, token, args, current_len);
      break;
    case 'o':
      written = s21_parse_octal(str, token, args, current_len);
      break;
    case 'p':
      written = s21_parse_pointer(str, token, args, current_len);
      break;
    case 'e':
    case 'E':
      written = s21_parse_exponent(str, token, args, current_len, 0);
      break;
    case 'g':
    case 'G':
      written = s21_parse_g(str, token, args, current_len);
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