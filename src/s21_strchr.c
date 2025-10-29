#include "s21_string.h"

char *s21_strchr(const char *str, int c) {
  char *match = s21_NULL;
  int is_found = 0;

  while (*str && !is_found) {
    if ((unsigned char)c == *str) {
      match = (char *)str;
      is_found = 1;
    } else {
      str++;
    }
  }

  if (c == '\0') match = (char *)str;
  return match;
}