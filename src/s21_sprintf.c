#include "s21_sprintf.h"

#include "s21_string.h"

int s21_sprintf(char *str, const char *format, ...) {
  int chr_count = 0;
  int err = 0;
  va_list args;
  va_start(args, format);
  for (int c = 0; format[c] != '\0' && (err == 0); c++) {
    if (format[c] == '%' && format[c + 1] != '%') {
      c++;
      err += read_format(str, &chr_count, format, &c, args);
    } else if (format[c] == '%' && format[c + 1] == '%') {
      c++;
      str[chr_count++] = '%';
    } else {
      str[chr_count++] = format[c];
    }
  }
  va_end(args);
  str[chr_count] = '\0';
  if (err > 0) {
    s21_strcpy(str, "Error Â¯\\_(*_*)_/Â¯");
    chr_count = -1;
  }
  return chr_count;
}

int read_format(char *str, int *chr_count, const char *format, int *c,
                va_list args) {
  Flags flags;
  char width[100] = "\0";
  char precision[100] = "\0";
  int err = 0;
  char len = '\0';
  if (correct_flag(format[*c])) {
    flags_pars(&flags, format[*c]);
    (*c)++;
  } else
    flags_pars(&flags, '\0');
  if (format[*c] != '*')
    add_width_prec(width, format, c);
  else {
    append_chr(width, '*');
    (*c)++;
  }
  if (format[*c] == '.') {
    (*c)++;
    if (format[*c] == '*') {
      append_chr(precision, '*');
      (*c)++;
    } else {
      if (correct_len(format[*c]) || correct_spec(format[*c]))
        append_chr(precision, '0');
      else
        add_width_prec(precision, format, c);
    }
  }
  if (correct_len(format[*c])) {
    len = format[*c];
    (*c)++;
  }
  if (correct_spec(format[*c]) && correct_len_with_spec(len, format[*c])) {
    err = read_spec(str, chr_count, args, format[*c], flags, width, precision,
                    len);
  } else {
    err++;
  }
  return err;
}

int read_spec(char *str, int *chr_count, va_list args, char spec, Flags flags,
              char *width, char *precision, char len) {
  int width_flag = (width[0] != '\0');
  int width_value = 0;
  int prec_flag = (precision[0] != '\0');
  int prec_value = 6;
  if (width_flag)
    width_value =
        (width[0] != '*' ? from_str_to_int(width) : va_arg(args, int));
  if (prec_flag)
    prec_value =
        (precision[0] != '*' ? from_str_to_int(precision) : va_arg(args, int));
  char *spec_str = add_str_spec(args, spec, len);
  if (flags.space && spec_str[0] != '-') prepend_char(spec_str, ' ');
  if (flags.sharp && (spec == 'x' || spec == 'X')) prepend_char(spec_str, spec);
  if (flags.sharp && (spec != 'f')) prepend_char(spec_str, '0');
  if (flags.plus && spec_str[0] != '-') prepend_char(spec_str, '+');
  char new_str[width_value + 1];
  if (spec == 'e' || spec == 'E') {
    char *str_e = scientific_notation(spec_str, prec_value, spec);
    s21_strcpy(spec_str, str_e);
  }
  if (spec == 'f' || spec == 'g' || spec == 'G') {
    float_round(spec_str, prec_value);
    if (!prec_flag && !(spec == 'f')) {
      spec_str[7] = '\0';
      del_zero(spec_str);
    } else if (prec_flag && !(spec == 'f'))
      spec_str[prec_value + 1] = '\0';
    if (spec_str[s21_strlen(spec_str) - 1] == '.' && !flags.sharp)
      spec_str[s21_strlen(spec_str) - 1] = '\0';
  }
  if (width_value > (int)s21_strlen(spec_str)) {
    for (int i = 0; i <= width_value; i++) {
      new_str[i] = (flags.zero ? '0' : ' ');
    }
    new_str[width_value] = '\0';
    if (flags.zero && spec_str[0] == '-') {
      shift_left(spec_str, 1);
      new_str[0] = '-';
    }
    if (flags.minus) {
      for (s21_size_t i = 0; i < s21_strlen(spec_str); i++) {
        new_str[i] = spec_str[i];
      }
    } else {
      s21_size_t j = s21_strlen(spec_str);
      for (int i = width_value - 1; j > 0; i--) {
        new_str[i] = spec_str[--j];
      }
    }
    s21_strcpy(spec_str, new_str);
  }
  append_string(str, chr_count, spec_str);
  return 0;
}

char *add_str_spec(va_list args, char spec, char len) {
  static char add_str[100];
  unsigned long int uns_value;
  if (is_chr_in_str("uxXo", spec)) {
    switch (len) {
      case '\0':
        uns_value = (unsigned int)va_arg(args, unsigned int);
        break;
      case 'h':
        uns_value = (unsigned short int)va_arg(args, unsigned int);
        break;
      case 'l':
        uns_value = (unsigned long int)va_arg(args, unsigned long int);
        break;
    }
  }
  switch (spec) {
    case 'c':
      char ch = va_arg(args, int);
      append_chr(add_str, ch);
      break;
    case 'd':
      long int d;
      if (len == 'h')
        d = (short int)va_arg(args, int);
      else if (len == '\0')
        d = va_arg(args, int);
      else
        d = (long int)va_arg(args, long int);
      s21_strcpy(add_str, from_int_to_str(d));
      break;
    case 's':
      char *s = va_arg(args, char *);
      s21_strcpy(add_str, s);
      break;
    case 'e':
    case 'E':
    case 'g':
    case 'G':
    case 'f':
      double f = va_arg(args, double);
      s21_strcpy(add_str, from_float_to_str(f));
      break;
    case 'u':
      s21_strcpy(add_str, from_uns_int_to_str(uns_value));
      break;
    case 'o':
      s21_strcpy(add_str, to_oct_decimal(uns_value));
      break;
    case 'x':
    case 'X':
      s21_strcpy(add_str, to_hex(uns_value, spec));
      break;
    case 'p':
      void *arg = va_arg(args, void *);
      s21_strcpy(add_str, ptr_to_str(arg));
      break;
  }
  return add_str;
}

void s21_strcpy(char *dest, char *src) {
  int i = 0;
  for (i = 0; src[i] != '\0'; i++) {
    dest[i] = src[i];
  }
  dest[i] = '\0';
}

int is_chr_in_str(char *str, char c) {
  int res = 0;
  for (s21_size_t i = 0; i < s21_strlen(str); i++) {
    if (str[i] == c) res = 1;
  }
  return res;
}

char *from_int_to_str(long int num) {
  static char str[100];
  char re_str[100];
  int len = 0;
  int negative_num_check = 0;
  if (num < 0) {
    num *= -1;
    str[0] = '-';
    negative_num_check++;
  }
  for (len = 0; num > 0; len++) {
    re_str[len] = num % 10 + '0';
    num /= 10;
  }
  for (int i = 0; i < len; i++) {
    str[i + negative_num_check] = re_str[len - i - 1];
  }
  str[len + negative_num_check] = '\0';
  return str;
}

char *from_uns_int_to_str(unsigned int num) {
  static char str[100];
  char re_str[100];
  int len = 0;
  for (len = 0; num > 0; len++) {
    re_str[len] = num % 10 + '0';
    num /= 10;
  }
  for (int i = 0; i < len; i++) {
    str[i] = re_str[len - i - 1];
  }
  str[len] = '\0';
  return str;
}

int from_str_to_int(char *str) {
  int res = 0;
  int negative_num = 0;
  if (str[0] == '-') negative_num++;
  for (s21_size_t i = negative_num; i < s21_strlen(str); i++) {
    if (str[i] != '.') res = res * 10 + str[i] - '0';
  }
  if (negative_num) res *= -1;
  return res;
}

char *from_float_to_str(double num) {
  static char str[100];
  int negative_num_check = 0;
  int first_zero_flag = 0;
  if (num < 0) {
    str[0] = '-';
    num *= -1;
    negative_num_check++;
  }
  if ((int)num == 0) {
    first_zero_flag++;
    str[negative_num_check] = '0';
  }
  char *int_part = from_int_to_str((int)num);
  double fractional_part = num - (int)num;
  s21_size_t i = 0;
  for (i = first_zero_flag; i < s21_strlen(int_part); i++) {
    str[i + negative_num_check] = int_part[i];
  }
  str[i + negative_num_check] = '.';
  fractional_part *= 10;
  for (int j = 0; j < 20; j++) {
    int frac_int = (int)fractional_part;
    str[++i + negative_num_check] = frac_int + '0';
    fractional_part -= frac_int;
    fractional_part *= 10;
  }
  str[s21_strlen(str) + negative_num_check] = '\0';
  return str;
}

char *scientific_notation(char *str_double, int prec_value, char spec) {
  static char scienc_not[100];
  s21_strcpy(scienc_not, str_double);
  int negative_num_flag = (scienc_not[0] == '-');
  if (negative_num_flag) shift_left(scienc_not, 1);
  int point_index = point_position(scienc_not);
  int nums_after_point = 0;
  if (point_position(scienc_not) == 1 && scienc_not[0] != '0') {
    append_chr(scienc_not, 'e');
    append_chr(scienc_not, '+');
    append_chr(scienc_not, '0');
    append_chr(scienc_not, '0');
  } else if (point_position(scienc_not) == 1 && scienc_not[0] == '0') {
    scienc_not[1] = '0';
    while (scienc_not[0] == '0') {
      nums_after_point++;
      shift_left(scienc_not, 1);
    }
    char first_char = scienc_not[0];
    shift_left(scienc_not, 1);
    prepend_char(scienc_not, '.');
    prepend_char(scienc_not, first_char);
  } else if (point_position(scienc_not) > 1) {
    for (int i = point_position(scienc_not); i > 1; i--) {
      scienc_not[i] = scienc_not[i - 1];
    }
    scienc_not[1] = '.';
  }
  float_round(scienc_not, prec_value);
  scienc_not[prec_value + 2] = '\0';
  append_chr(scienc_not, spec);
  scienc_not[prec_value + 3] =
      (point_index > 0 && nums_after_point == 0 ? '+' : '-');
  scienc_not[prec_value + 4] = '0';
  if (point_index > 1)
    scienc_not[prec_value + 5] = from_int_to_str(--point_index)[0];
  else if (point_index == 1 && nums_after_point == 0)
    scienc_not[prec_value + 5] = '0';
  else
    scienc_not[prec_value + 5] = from_int_to_str(--nums_after_point)[0];
  scienc_not[prec_value + 6] = '\0';
  if (negative_num_flag) prepend_char(scienc_not, '-');
  return scienc_not;
}

char *to_oct_decimal(unsigned int num) {
  static char str[100];
  if (num == 0) {
    str[0] = '0';
    str[1] = '\0';
  } else {
    char re_str[100];
    int len = 0;
    for (len = 0; num > 0; len++) {
      re_str[len] = num % 8 + '0';
      num /= 8;
    }
    for (int i = 0; i < len; i++) {
      str[i] = re_str[len - i - 1];
    }
    str[len] = '\0';
  }
  return str;
}

char *to_hex(unsigned int num, char spec) {
  static char str[100];
  if (num == 0) {
    str[0] = '0';
    str[1] = '\0';
  } else {
    char re_str[100];
    int X_flag = (spec == 'X' ? 32 : 0);
    char hex_nums[] = "abcdef";
    int len = 0;
    for (len = 0; num > 0; len++) {
      if (num % 16 <= 9)
        re_str[len] = num % 16 + '0';
      else
        re_str[len] = hex_nums[num % 16 - 10] - X_flag;
      num /= 16;
    }
    for (int i = 0; i < len; i++) {
      str[i] = re_str[len - i - 1];
    }
    str[len] = '\0';
  }
  return str;
}

char *ptr_to_str(void *address) {
  static char str[16];
  unsigned long int addr = (unsigned long int)address;
  char hex_nums[] = "0123456789abcdef";
  int first_not_zero = 0;
  for (int i = 0; i < 16; i++) {
    str[15 - i] = hex_nums[addr % 16];
    addr /= 16;
  }
  str[16] = '\0';
  for (int i = 0; i < 16 && first_not_zero == 0; i++) {
    if (str[i] != 0) first_not_zero = i;
  }
  shift_left(str, first_not_zero + 1);
  str[1] = 'x';
  return str;
}

void shift_left(char *str, int n) {
  int len = s21_strlen(str);
  for (int i = 0; i < len - n; i++) {
    str[i] = str[i + n];
  }
  str[len - n] = '\0';
}

void del_zero(char *str) {
  int flag = 1;
  for (int i = 6; i >= 0 && flag; i--) {
    if ('1' <= str[i] && str[i] <= '9') {
      flag = 0;
      str[i + 1] = '\0';
    }
  }
}

int point_position(char *str) {
  int res = 0;
  for (s21_size_t i = 0; i < s21_strlen(str) && res == 0; i++) {
    if (str[i] == '.') res = i;
  }
  return res;
}

void append_string(char *str, int *chr_count, char *s) {
  for (s21_size_t i = 0; i < s21_strlen(s); i++) {
    str[(*chr_count)++] = s[i];
  }
}

void append_chr(char *str, char c) {
  s21_size_t len = s21_strlen(str);
  str[len] = c;
  str[len + 1] = '\0';
}

void prepend_char(char *str, char c) {
  int length = s21_strlen(str);
  for (int i = length; i >= 0; i--) {
    str[i + 1] = str[i];
  }
  str[0] = c;
}

int correct_flag(char c) {
  char flags[] = "+- #0";
  int res = 0;
  for (s21_size_t i = 0; i < s21_strlen(flags); i++) {
    if (flags[i] == c) res++;
  }
  return res;
}

void flags_pars(Flags *flags, char c) {
  flags->minus = (c == '-');
  flags->plus = (c == '+');
  flags->space = (c == ' ');
  flags->sharp = (c == '#');
  flags->zero = (c == '0');
}

int correct_spec(char c) {
  char specs[] = "cdfsugGeExXop";
  int res = 0;
  for (s21_size_t i = 0; i < s21_strlen(specs); i++) {
    if (specs[i] == c) res++;
  }
  return res;
}

int correct_len(char c) {
  char lens[] = "hlL";
  int res = 0;
  for (s21_size_t i = 0; i < s21_strlen(lens); i++) {
    if (lens[i] == c) res++;
  }
  return res;
}

int correct_len_with_spec(char len, char spec) {
  int res = 0;
  if (len == '\0')
    res = 1;
  else if (is_chr_in_str("idouxX", spec) && (len == 'h'))
    res = 1;
  else if (is_chr_in_str("idouxXcs", spec) && (len == 'l'))
    res = 1;
  else if (is_chr_in_str("eEfgG", spec) && (len == 'L'))
    res = 1;
  return res;
}

void add_width_prec(char *str, const char *format, int *c) {
  while (('0' <= format[*c] && format[*c] <= '9')) {
    append_chr(str, format[*c]);
    (*c)++;
  }
}

void float_round(char *src_float, int prec_value) {
  int point_index = point_position(src_float);
  char last_num = src_float[point_index + prec_value + 1];
  if ('0' <= last_num && last_num <= '4') {
    src_float[point_index + prec_value + 1] = '\0';
  } else {
    if (src_float[0] == '-') {
      shift_left(src_float, 1);
      prepend_char(src_float, '0');
      prepend_char(src_float, '-');
    } else
      prepend_char(src_float, '0');
    point_index++;
    int flag = 1;
    for (int i = point_index + prec_value; i >= 0 && flag; i--) {
      if (src_float[i] == '.') i--;
      if (src_float[i] < '9') {
        src_float[i]++;
        flag = 0;
      } else
        src_float[i] = '0';
    }
    if (src_float[0] == '0') {
      shift_left(src_float, 1);
      point_index--;
    } else if (src_float[0] == '-' && src_float[1] == '0') {
      shift_left(src_float, 2);
      prepend_char(src_float, '-');
      point_index--;
    }
    src_float[point_index + prec_value + 1] = '\0';
  }
}
