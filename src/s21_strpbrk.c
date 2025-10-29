#include "s21_string.h"

char *s21_strpbrk(const char *str1, const char *str2) {
  char *res = s21_NULL;
  int flag = 1;
  for (int i = 0; str1[i] != '\0' && flag; i++) {
    for (int j = 0; str2[j] != '\0' && flag; j++) {
      if (str1[i] == str2[j]) {
        res = (char *)str1 + i;
        flag = 0;
      }
    }
  }
  return res;
}