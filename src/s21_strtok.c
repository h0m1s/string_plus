#include "s21_string.h"

char* s21_strtok(char* str, const char* delim) {
  static char* last = s21_NULL;
  if (str != s21_NULL) {
    last = str;
  } else if (last == s21_NULL) {
    return s21_NULL;
  }
  if (*delim == '\0') {
    char* token = last;
    last = last + s21_strlen(last);
    return token;
  }
  while (*last && s21_strchr(delim, *last) != s21_NULL) {
    last++;
  }
  if (*last == '\0') {
    last = s21_NULL;
    return s21_NULL;
  }
  char* token = last;
  while (*last && s21_strchr(delim, *last) == s21_NULL) {
    last++;
  }
  if (*last) {
    *last = '\0';
    last++;
  } else {
    last = s21_NULL;
  }
  return token;
}
