#include "s21_string.h"

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  char *dest_start = dest;
  for (; *src && n; dest++, src++, n--) {
    *dest = *src;
  }
  while (n--) {
    *dest++ = '\0';
  }
  return dest_start;
}