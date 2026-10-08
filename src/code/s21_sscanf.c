#include "../s21_string.h"

int sscanf(const char* str, const char* format, ...) {
  va_list args;
  va_start(args, format);

  const char* start_str = str;
  int count = 0;

  while (*format) {
    if (isspace((unsigned char)*format)) {
      while (isspace((unsigned char)*str)) {
        str++;
      }
      format++;
      continue;
    }

    if (*format == '%') {
      format++;
      if (*format == '\0') break;

      if (*format == '%') {
        if (*str == '%') {
          str++;
          format++;
          continue;
        } else
          break;
      }

      int skip = 0;
      if (*format == '*') {
        skip = 1;
        format++;
      }

      int width = -1;
      if (isdigit((unsigned char)*format)) {
        width = 0;
        while (isdigit((unsigned char)*format)) {
          width = width * 10 + (*format - '0');
          format++;
        }
      }

      char length = '\0';
      if (*format == 'h' || *format == 'l' || *format == 'L') {
        length = *format;
        format++;
      }

      char spec = *format;
      if (spec == '\0') break;

      if (spec == 'n') {
        if (!skip) {
          int* pn = va_arg(args, int*);
          *pn = (int)(str - start_str);
        }
        format++;
        continue;
      }

      if (spec != 'c') {
        while (isspace((unsigned char)*str)) {
          str++;
        }
      }

      if (*str == '\0') break;
      if (width == 0) break;

      if (spec == 'c') {
        int read_len = (width <= 0) ? 1 : width;
        char* c_dest = skip ? NULL : va_arg(args, char*);
        int i = 0;

        while (i < read_len && *str != '\0') {
          if (!skip) c_dest[i] = *str;
          str++;
          i++;
        }
        if (i == 0) break;
        if (!skip) count++;
      } else if (spec == 's') {
        char* s_dest = skip ? NULL : va_arg(args, char*);
        int i = 0;

        while (*str != '\0' && !isspace((unsigned char)*str) &&
               (width < 0 || i < width)) {
          if (!skip) s_dest[i] = *str;
          str++;
          i++;
        }
        if (i == 0) break;
        if (!skip) {
          s_dest[i] = '\0';
          count++;
        }
      } else if (spec == 'd' || spec == 'i' || spec == 'u' || spec == 'o' ||
                 spec == 'x' || spec == 'X' || spec == 'p') {
        int sign = 1;
        int base = 10;
        int w_count = 0;

        if ((width < 0 || w_count < width) && (*str == '-' || *str == '+')) {
          if (*str == '-') sign = -1;
          str++;
          w_count++;
        }

        if (spec == 'x' || spec == 'X' || spec == 'p' || spec == 'i') {
          if ((width < 0 || w_count + 2 <= width) && *str == '0' &&
              (tolower((unsigned char)*(str + 1)) == 'x')) {
            base = 16;
            str += 2;
            w_count += 2;
          } else if (spec == 'x' || spec == 'X' || spec == 'p') {
            base = 16;
          } else if (spec == 'i' && (width < 0 || w_count < width) &&
                     *str == '0') {
            base = 8;
          }
        } else if (spec == 'o') {
          base = 8;
        }

        unsigned long long raw_num = 0;
        int has_digit = 0;

        while (*str != '\0' && (width < 0 || w_count < width)) {
          char c = *str;
          int val = -1;

          if (isdigit((unsigned char)c))
            val = c - '0';
          else if (isxdigit((unsigned char)c))
            val = tolower((unsigned char)c) - 'a' + 10;

          if (val < 0 || val >= base) break;

          raw_num = raw_num * base + val;
          has_digit = 1;
          str++;
          w_count++;
        }

        if (!has_digit) break;

        if (!skip) {
          if (spec == 'd' || spec == 'i') {
            long long final_num = (long long)raw_num * sign;
            if (length == 'h')
              *(va_arg(args, short*)) = (short)final_num;
            else if (length == 'l')
              *(va_arg(args, long*)) = (long)final_num;
            else
              *(va_arg(args, int*)) = (int)final_num;
          } else if (spec == 'p') {
            *(va_arg(args, void**)) = (void*)(long long)raw_num;
          } else {
            if (length == 'h')
              *(va_arg(args, unsigned short*)) = (unsigned short)raw_num;
            else if (length == 'l')
              *(va_arg(args, unsigned long*)) = (unsigned long)raw_num;
            else
              *(va_arg(args, unsigned int*)) = (unsigned int)raw_num;
          }
          count++;
        }
      } else if (spec == 'f' || spec == 'e' || spec == 'E' || spec == 'g' ||
                 spec == 'G') {
        int w_count = 0;
        double sign = 1.0;

        if ((width < 0 || w_count < width) && (*str == '-' || *str == '+')) {
          if (*str == '-') sign = -1.0;
          str++;
          w_count++;
        }

        double value = 0.0;
        int has_digit = 0;

        while (*str != '\0' && isdigit((unsigned char)*str) &&
               (width < 0 || w_count < width)) {
          value = value * 10.0 + (*str - '0');
          has_digit = 1;
          str++;
          w_count++;
        }

        if ((width < 0 || w_count < width) && *str == '.') {
          str++;
          w_count++;
          double weight = 0.1;
          while (*str != '\0' && isdigit((unsigned char)*str) &&
                 (width < 0 || w_count < width)) {
            value += (*str - '0') * weight;
            weight *= 0.1;
            has_digit = 1;
            str++;
            w_count++;
          }
        }

        if (!has_digit) break;

        if ((width < 0 || w_count < width) &&
            (tolower((unsigned char)*str) == 'e')) {
          const char* backup_str = str;
          int backup_w = w_count;
          str++;
          w_count++;

          int exp_sign = 1;
          if ((width < 0 || w_count < width) && (*str == '-' || *str == '+')) {
            if (*str == '-') exp_sign = -1;
            str++;
            w_count++;
          }

          int exp_val = 0;
          int has_exp_digit = 0;
          while (*str != '\0' && isdigit((unsigned char)*str) &&
                 (width < 0 || w_count < width)) {
            exp_val = exp_val * 10 + (*str - '0');
            has_exp_digit = 1;
            str++;
            w_count++;
          }

          if (has_exp_digit) {
            double factor = 1.0;
            for (int k = 0; k < exp_val; k++) factor *= 10.0;
            if (exp_sign == 1)
              value *= factor;
            else
              value /= factor;
          } else {
            str = backup_str;
            w_count = backup_w;
          }
        }

        value *= sign;
        if (!skip) {
          if (length == 'L')
            *(va_arg(args, long double*)) = (long double)value;
          else if (length == 'l')
            *(va_arg(args, double*)) = (double)value;
          else
            *(va_arg(args, float*)) = (float)value;
          count++;
        }
      }

      format++;
    } else {
      if (*str == *format) {
        str++;
        format++;
      } else {
        break;
      }
    }
  }

  va_end(args);
  return count;
}