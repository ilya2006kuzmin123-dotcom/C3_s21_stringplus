#include "../s21_string.h"

void* s21_insert(const char* src, const char* str, s21_size start_index) {
    void* new_str = S21_NULL;
    s21_size src_len = (src != S21_NULL) ? s21_strlen(src) : 0;
    s21_size str_len = (str != S21_NULL) ? s21_strlen(str) : 0;
    if((src != S21_NULL && str != S21_NULL) && start_index <= src_len) {
        new_str = malloc(src_len + str_len + 1);
        if(new_str != S21_NULL) {
            char *res = (char *)new_str; 
            s21_memcpy(res, src, start_index);
            s21_memcpy(res + start_index, str, str_len);
            s21_memcpy(res + start_index + str_len, src + start_index, src_len - start_index);
            res[src_len + str_len] = '\0';
        }
    }
    return new_str;
}