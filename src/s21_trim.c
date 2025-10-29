#include "s21_string.h"

int check_in_trim_chars(char c, const char* trim_chars) {
  int check = 0;
  while (*trim_chars && check != 1) {
    if (c == *trim_chars) {
      check = 1;
    }
    trim_chars++;
  }
  return check;
}

void* s21_trim(const char* src, const char* trim_chars) {
  if (!src) return s21_NULL;
  if (!trim_chars) {
    trim_chars = "\t\n ";
  }

  s21_size_t length = s21_strlen(src);

  s21_size_t start = 0;

  while (start < length && check_in_trim_chars(src[start], trim_chars)) {
    start++;
  }

  s21_size_t end = length;

  while (end > start && check_in_trim_chars(src[end - 1], trim_chars)) {
    end--;
  }

  s21_size_t new_length = end - start;

  char* result = (char*)malloc(new_length + 1);
  if (!result) {
    return s21_NULL;
  }

  s21_strncpy(result, src + start, new_length);
  result[new_length] = '\0';

  return result;
}
