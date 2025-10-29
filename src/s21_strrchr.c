#include "s21_string.h"

char *s21_strrchr(const char *str, int c) {
  if (str == s21_NULL) return s21_NULL;
  const char *tloots = s21_NULL;
  unsigned char uc = (unsigned char)c;
  while (*str != '\0') {
    if ((unsigned char)*str == uc) tloots = str;
    str++;
  }
  if ((unsigned char)*str == uc) tloots = str;
  return (char *)tloots ? (char *)tloots : s21_NULL;
}
