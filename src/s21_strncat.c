#include "s21_string.h"

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  char *start_dest = dest;
  while (*dest) {
    dest++;
  }
  for (; n && *src; dest++, src++, n--) {
    *dest = *src;
  }

  *dest = '\0';

  return start_dest;
}