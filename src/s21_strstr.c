#include "s21_string.h"

char *s21_strstr(const char *haystack, const char *needle) {
  if (needle == s21_NULL) return s21_NULL;
  if (*needle == '\0') return (char *)haystack;
  s21_size_t needle_len = s21_strlen(needle);
  while (*haystack != '\0') {
    if (s21_memcmp(haystack, needle, needle_len) == 0) {
      return (char *)haystack;
    }
    haystack++;
  }
  return s21_NULL;
}
