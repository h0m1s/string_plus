#include "s21_string.h"

void* s21_insert(const char* src, const char* str, s21_size_t start_index) {
  s21_size_t len_src = s21_strlen(src);
  s21_size_t len_str = s21_strlen(str);
  s21_size_t length = len_src + len_str;

  if (start_index > len_src) {
    return s21_NULL;
  }

  char* new_str = (char*)malloc((length + 1) * sizeof(char));
  if (new_str == s21_NULL) {
    return s21_NULL;
  }

  s21_size_t i = 0;
  for (; i < start_index; i++) {
    new_str[i] = src[i];
  }

  for (s21_size_t j = 0; j < len_str; j++, i++) {
    new_str[i] = str[j];
  }

  for (s21_size_t k = start_index; k < len_src; k++, i++) {
    new_str[i] = src[k];
  }

  new_str[length] = '\0';
  return (void*)new_str;
}