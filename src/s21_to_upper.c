#include "s21_string.h"

void* s21_to_upper(const char* str) {
  if (str == s21_NULL) {
    return s21_NULL;
  }

  s21_size_t length = s21_strlen(str);

  char* upper_str = (char*)malloc((length + 1) * sizeof(char));

  for (s21_size_t i = 0; i < length; i++) {
    if (str[i] >= 'a' && str[i] <= 'z') {
      upper_str[i] = str[i] - 32;
    } else {
      upper_str[i] = str[i];
    }
  }
  upper_str[length] = '\0';

  return (void*)upper_str;
}