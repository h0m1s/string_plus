#ifndef S21_SPRINTF_H
#define S21_SPRINTF_H

#include <stdarg.h>

#include "s21_string.h"

typedef struct flags {
  int minus;
  int plus;
  int space;
  int sharp;
  int zero;
} Flags;

void s21_strcpy(char *dest, char *src);
int is_chr_in_str(char *str, char c);
char *from_int_to_str(long int num);
char *from_uns_int_to_str(unsigned int num);
int from_str_to_int(char *str);
char *from_float_to_str(double num);
char *scientific_notation(char *str_double, int prec_value, char spec);
char *to_oct_decimal(unsigned int num);
char *to_hex(unsigned int num, char spec);
char *ptr_to_str(void *address);
void shift_left(char *str, int n);
void del_zero(char *str);
void add_width_prec(char *str, const char *format, int *c);
int point_position(char *str);
void append_string(char *str, int *chr_count, char *s);
void append_chr(char *str, char c);
void prepend_char(char *str, char c);
int correct_flag(char c);
void flags_pars(Flags *flags, char c);
int correct_spec(char c);
int correct_len(char c);
int correct_len_with_spec(char len, char spec);
char *add_str_spec(va_list args, char spec, char len);
void float_round(char *src_float, int prec_value);
int read_spec(char *str, int *chr_count, va_list args, char spec, Flags flags,
              char *width, char *precision, char len);
int read_format(char *str, int *chr_count, const char *format, int *c,
                va_list args);
int s21_sprintf(char *str, const char *format, ...);
#endif