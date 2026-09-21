#ifndef S21_STRING_H
#define S21_STRING_H

#include <stdio.h>

#define S21_NULL (void*)0
typedef long unsigned s21_size;

void* s21_insert(const char* src, const char* str, s21_size start_index);
void* s21_memchr(const void* str, int c, s21_size n);
int s21_memcmp(const void* str1, const void* str2, s21_size n);
void* s21_memcpy(void* dest, const void* src, s21_size n);
void* s21_memset(void* str, int c, s21_size n);
char* s21_strchr(const char* str, int c);
s21_size s21_strcspn(const char* str1, const char* str2);
char* s21_strerror(int errnum);
s21_size s21_strlen(const char* str);
char* s21_strncat(char* dest, const char* src, s21_size n);

#endif