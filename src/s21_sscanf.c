#include "s21_sscanf.h"

#include "s21_string.h"
int s21_sscanf(const char *str, const char *format, ...) {
  int successfully_read = -1, error = 0;
  options options = {0};
  const char *str_start = str, *ptr = format;
  va_list args;
  va_start(args, format);
  while (*ptr && error == 0) {
    if (s21_isspace(*ptr)) {
      while (s21_isspace(*ptr)) ptr++;
      while (s21_isspace(*str)) str++;
    } else if (*ptr == '%') {
      ptr++;
      parse_options(&ptr, &options);
      if (*ptr == '%') {
        str++;
      } else if (*ptr == 'd') {
        handle_integer(&str, args, options);
        increment_successfull_reads(&successfully_read);
      } else if (*ptr == 'c') {
        handle_character(&str, args, &successfully_read, options);
      } else if (*ptr == 's') {
        handle_string(&str, args, options);
        increment_successfull_reads(&successfully_read);
      } else if (*ptr == 'p') {
        handle_pointer(&str, args, &successfully_read, options);
      } else if (*ptr == 'x' || *ptr == 'X') {
        handle_hex(&str, args, &successfully_read, options);
      } else if (*ptr == 'n') {
        handle_n(str, args, str_start);
      } else if (*ptr == 'o') {
        handle_octal(&str, args, options);
        increment_successfull_reads(&successfully_read);
      } else if (*ptr == 'f' || *ptr == 'e' || *ptr == 'E' || *ptr == 'g' ||
                 *ptr == 'G') {
        handle_floats(&str, args, &successfully_read, options);
      } else if (*ptr == 'u') {
        handle_unsigned_integer(&str, args, options);
        increment_successfull_reads(&successfully_read);
      } else if (*ptr == 'i') {
        handle_hex_octal_normal_integer(&str, args, options);
        increment_successfull_reads(&successfully_read);
      } else {
        perror("Error Â¯\\_(*_*)_/Â¯");
        error = 1;
      }
      ptr++;
    }
  }
  va_end(args);
  return successfully_read;
}

void parse_options(const char **ptr, options *options) {
  if (s21_isdigit(**ptr)) {
    long value = 0;
    while (s21_isdigit(**ptr)) {
      value = char_to_int(**ptr, &value);
      (*ptr)++;
    }
    options->width = value;
  }
  if (**ptr == 'l' || **ptr == 'h' || **ptr == 'L') {
    options->length = **ptr;
    (*ptr)++;
  }
}

void handle_integer(const char **str, va_list args, options options) {
  int sign = 1;
  long int value;
  change_sign(str, &sign);
  if (options.length == 'l') {
    long int *d = va_arg(args, long int *);
    value = read_number_from_str(str, options);
    *d = sign * value;
  } else if (options.length == 'h') {
    short int *d = va_arg(args, short int *);
    value = read_number_from_str(str, options);
    *d = sign * value;
  } else {
    int *d = va_arg(args, int *);
    value = read_number_from_str(str, options);
    *d = sign * value;
  }
}

void handle_character(const char **str, va_list args, int *successfully_read,
                      options options) {
  char *c = va_arg(args, char *);
  if (options.width > 0) {
    while (options.width--) {
      *c = **str;
      (*str)++;
      c++;
    }
  } else if (**str) {
    *c = **str;
    (*str)++;
    increment_successfull_reads(successfully_read);
  }
}

void handle_string(const char **str, va_list args, options options) {
  char *s = va_arg(args, char *);
  while (s21_isspace(**str)) {
    str++;
  }
  if (options.width > 0) {
    while (options.width-- && !s21_isspace(**str)) {
      *s = **str;
      (*str)++;
      s++;
    }
  } else {
    while (!s21_isspace(**str)) {
      *s = **str;
      (*str)++;
      s++;
    }
  }

  *s = '\0';
}

void handle_pointer(const char **str, va_list args, int *successfully_read,
                    options options) {
  void **p = va_arg(args, void **);
  char *str_end;
  if (options.width > 0 && options.width <= 2 &&
      s21_strncmp(*str, "0x", 2) == 0) {
    *p = s21_NULL;
  } else if (options.width > 2 && s21_strncmp(*str, "0x", 2) == 0) {
    (*str) += 2;
    options.width -= 2;
    unsigned long address = hex_to_decimal(*str, &str_end, options.width);
    if (str_end != *str) {
      *p = (void *)address;
      (*str) = str_end;
      increment_successfull_reads(successfully_read);
    }
  } else {
    if (s21_strncmp(*str, "0x", 2) == 0) {
      (*str) += 2;
    }
    unsigned long address = hex_to_decimal(*str, &str_end, options.width);
    if (str_end != *str) {
      *p = (void *)address;
      (*str) = str_end;
      increment_successfull_reads(successfully_read);
    }
  }
}

void handle_hex(const char **str, va_list args, int *successfully_read,
                options options) {
  long value;
  if (options.length == 'l') {
    long int *x = va_arg(args, long int *);
    value = read_hex_number_from_str(str, options, &successfully_read);
    *x = value;
  } else if (options.length == 'h') {
    short int *x = va_arg(args, short int *);
    value = read_hex_number_from_str(str, options, &successfully_read);
    *x = value;
  } else {
    int *x = va_arg(args, int *);
    value = read_hex_number_from_str(str, options, &successfully_read);
    *x = value;
  }
}

void handle_n(const char *str, va_list args, const char *str_start) {
  s21_size_t *n = va_arg(args, s21_size_t *);
  *n = (s21_size_t)(str - str_start);
}

void handle_octal(const char **str, va_list args, options options) {
  long value;
  if (options.length == 'l') {
    long int *o = va_arg(args, long int *);
    value = read_octal_number_from_str(str, options);
    *o = value;
  } else if (options.length == 'h') {
    short int *o = va_arg(args, short int *);
    value = read_octal_number_from_str(str, options);
    *o = value;
  } else {
    int *o = va_arg(args, int *);
    value = read_octal_number_from_str(str, options);
    *o = value;
  }
}

void handle_floats(const char **str, va_list args, int *successfully_read,
                   options options) {
  if (options.length == 'L') {
    double *dbl = va_arg(args, double *);
    *dbl = read_float_from_str(str, options, successfully_read);
  } else {
    float *dbl = va_arg(args, float *);
    *dbl = read_float_from_str(str, options, successfully_read);
  }
}

void handle_unsigned_integer(const char **str, va_list args, options options) {
  unsigned long int value = 0;
  if (options.length == 'l') {
    unsigned long int *u = va_arg(args, unsigned long int *);
    value = read_number_from_str(str, options);
    *u = value;
  } else if (options.length == 'h') {
    unsigned short int *u = va_arg(args, unsigned short int *);
    value = read_number_from_str(str, options);
    *u = value;
  } else {
    unsigned int *u = va_arg(args, unsigned int *);
    value = read_number_from_str(str, options);
    *u = value;
  }
}

void handle_hex_octal_normal_integer(const char **str, va_list args,
                                     options options) {
  long int value;
  if (options.length == 'l') {
    long int *d = va_arg(args, long int *);
    value = read_hex_octal_normal_from_str(str, options);
    *d = value;
  } else if (options.length == 'h') {
    short int *d = va_arg(args, short int *);
    value = read_hex_octal_normal_from_str(str, options);
    *d = value;
  } else {
    int *d = va_arg(args, int *);
    value = read_hex_octal_normal_from_str(str, options);
    *d = value;
  }
}

long read_number_from_str(const char **str, options options) {
  long value = 0;
  if (options.width > 0) {
    while (s21_isdigit(**str) && options.width--) {
      value = char_to_int(**str, &value);
      (*str)++;
    }
  } else {
    while (s21_isdigit(**str)) {
      value = char_to_int(**str, &value);
      (*str)++;
    }
  }
  return value;
}

double read_float_from_str(const char **str, options options,
                           int *successfully_read) {
  double dbl = 0;
  char *str_end;
  while (s21_isspace((unsigned char)**str) && (options.width == 0)) {
    (*str)++;
  }
  dbl = str_to_double(*str, &str_end, options);
  if (str_end != *str) {
    *str = str_end;
    increment_successfull_reads(successfully_read);
  }
  return dbl;
}

long read_hex_number_from_str(const char **str, options options,
                              int **successfully_read) {
  char *str_end;
  long int value = 0;
  int sign = 1;
  change_sign(str, &sign);
  if (options.width > 0) {
    if (s21_strncmp(*str, "0x", 2) == 0) {
      (*str) += 2;
      options.width -= 2;
    }
    long res = hex_to_decimal(*str, &str_end, options.width);
    if (str_end != *str) {
      if (options.width <= 0) {
        value = 0;
      } else {
        value = sign * res;
      }
      *str = str_end;
      increment_successfull_reads(*successfully_read);
    }
  } else {
    if (s21_strncmp(*str, "0x", 2) == 0) {
      (*str) += 2;
    }
    long res = hex_to_decimal(*str, &str_end, options.width);
    if (str_end != *str) {
      value = sign * res;
      *str = str_end;
      increment_successfull_reads(*successfully_read);
    }
  }
  return value;
}

long read_octal_number_from_str(const char **str, options options) {
  long int value = 0;
  int sign = 1;
  change_sign(str, &sign);
  if (options.width > 0) {
    while (s21_is_octal_digit(**str) && options.width--) {
      value = value * 8 + (**str - '0');
      (*str)++;
    }
  } else {
    while (s21_is_octal_digit(**str)) {
      value = value * 8 + (**str - '0');
      (*str)++;
    }
  }

  return value * sign;
}

long read_hex_octal_normal_from_str(const char **str, options options) {
  int sign = 1;
  long int value = 0;
  change_sign(str, &sign);
  if (s21_strncmp(*str, "0x", 2) == 0) {
    *str += 2;
    options.width -= 2;
    if (options.width <= 0) {
      while (s21_is_hex_digit(**str)) {
        value = value * 16 + hex_char_to_number(**str);
        (*str)++;
      }
    } else {
      while (s21_is_hex_digit(**str) && options.width--) {
        value = value * 16 + hex_char_to_number(**str);
        (*str)++;
      }
    }
  } else if (**str == '0') {
    (*str)++;
    if (options.width <= 0) {
      while (s21_is_octal_digit(**str)) {
        value = value * 8 + (**str - '0');
        (*str)++;
      }
    } else {
      while (s21_is_octal_digit(**str) && options.width--) {
        value = value * 8 + (**str - '0');
        (*str)++;
      }
    }
  } else {
    if (options.width <= 0) {
      while (s21_isdigit(**str)) {
        value = value * 10 + (**str - '0');
        (*str)++;
      }
    } else {
      while (s21_isdigit(**str) && options.width--) {
        value = value * 10 + (**str - '0');
        (*str)++;
      }
    }
  }
  return value * sign;
}
int hex_char_to_number(char c) {
  int number = -1;
  if (c >= '0' && c <= '9') number = c - '0';
  if (c >= 'a' && c <= 'f') number = c - 'a' + 10;
  if (c >= 'A' && c <= 'F') number = c - 'A' + 10;
  return number;
}

int s21_isspace(char c) {
  return c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' ||
         c == '\r';
}

int s21_isdigit(char c) { return c >= '0' && c <= '9'; }

int s21_is_octal_digit(char c) { return c >= '0' && c <= '7'; }

void change_sign(const char **str, int *sign) {
  if (**str == '-') {
    *sign = -1;
    (*str)++;
  } else if (**str == '+') {
    (*str)++;
  }
}

int s21_is_hex_digit(char c) {
  return s21_isdigit(c) || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F');
}
void increment_successfull_reads(int *successfully_read) {
  if (*successfully_read == -1) {
    (*successfully_read) += 2;
  } else {
    (*successfully_read)++;
  }
}
unsigned long hex_to_decimal(const char *str, char **str_end, int width) {
  const char *s = str;
  unsigned long int result = 0;
  int is_invalid_character = 0;
  if (width <= 0) {
    while (*s && !is_invalid_character) {
      int digit = hex_char_to_number(*s);
      if (digit == -1) {
        is_invalid_character++;
      }
      if (!is_invalid_character) {
        result = result * 16 + digit;
        s++;
      }
    }
  } else {
    while (*s && !is_invalid_character && width--) {
      int digit = hex_char_to_number(*s);
      if (digit == -1) {
        is_invalid_character++;
      }
      if (!is_invalid_character) {
        result = result * 16 + digit;
        s++;
      }
    }
  }

  *str_end = (char *)s;

  return result;
}

double str_to_double(const char *str, char **str_end, options options) {
  double result = 0.0;
  int sign = 1;
  change_sign(&str, &sign);
  if (options.width <= 0) {
    result = read_from_str_to_double(&str);
  } else {
    int exponent = 0;
    while (s21_isdigit((unsigned char)*str) && options.width--) {
      result = result * 10 + (*str - '0');
      ;
      str++;
    }

    if (*str == '.') {
      str++;
      options.width--;
      double fraction = 1.0;
      while (s21_isdigit((unsigned char)*str) && options.width--) {
        fraction *= 0.1;
        result += fraction * (*str - '0');
        str++;
      }
    }

    if (*str == 'e' || *str == 'E') {
      str++;
      options.width--;
      int exp_sign = 1;
      change_sign(&str, &exp_sign);
      while (s21_isdigit((unsigned char)*str) && options.width--) {
        exponent = exponent * 10 + (*str - '0');
        str++;
      }
      exponent *= exp_sign;
    }

    if (exponent > 0) {
      while (exponent--) {
        result *= 10.0;
      }
    } else {
      while (exponent++) {
        result *= 0.1;
      }
    }
  }
  *str_end = (char *)str;
  return sign * result;
}

double read_from_str_to_double(const char **str) {
  double result = 0.0;
  int exponent = 0;
  while (s21_isdigit((unsigned char)**str)) {
    result = result * 10.0 + (**str - '0');
    (*str)++;
  }

  if (**str == '.') {
    (*str)++;
    double fraction = 1.0;
    while (s21_isdigit((unsigned char)**str)) {
      fraction *= 0.1;
      result += fraction * (**str - '0');
      (*str)++;
    }
  }

  if (**str == 'e' || **str == 'E') {
    (*str)++;
    int exp_sign = 1;
    change_sign(str, &exp_sign);
    while (s21_isdigit((unsigned char)**str)) {
      exponent = exponent * 10 + (**str - '0');
      (*str)++;
    }
    exponent *= exp_sign;
  }

  if (exponent > 0) {
    while (exponent--) {
      result *= 10.0;
    }
  } else {
    while (exponent++) {
      result *= 0.1;
    }
  }

  return result;
}
long char_to_int(char c, const long *result) {
  long value = *result;
  value = value * 10 + (c - '0');
  return value;
}
