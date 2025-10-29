#include "s21_string.h"

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int difference = 0;

  for (; *str1 && n; str1++, str2++, n--) {
    if (*str1 != *str2) {
      difference = *str1 - *str2;
      n = 0;
    }
  }

  return difference;
}