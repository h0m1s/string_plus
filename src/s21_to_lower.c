#include "s21_string.h"

void* s21_to_lower(const char* str) {
  s21_size_t length = s21_strlen(str);

  char* lower_str = (char*)malloc((length + 1) * sizeof(char));

  if (lower_str == s21_NULL) return s21_NULL;

  for (s21_size_t i = 0; i < length; i++) {
    if (str[i] >= 'A' && str[i] <= 'Z') {
      lower_str[i] = str[i] + 32;
    } else {
      lower_str[i] = str[i];
    }
  }
  lower_str[length] = '\0';
  return (void*)lower_str;
}